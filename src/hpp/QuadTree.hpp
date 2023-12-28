#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

typedef unsigned short ushort;
template <class DataType>
class QuadTree
{

private:
    class Node
    {
    public:
        Node(sf::FloatRect boundary, ushort capacity)
        {
            NE = NW = SE = SW = nullptr;

            this->boundary = boundary;
            this->capacity = capacity;
            this->divided = false;

            const sf::Vector2f position(boundary.left, boundary.top);
            const sf::Vector2f size(boundary.width, boundary.height);

            this->lines[0] = sf::Vertex(position, sf::Color::Yellow);
            this->lines[1] = sf::Vertex(position + sf::Vector2f(size.x, 0), sf::Color::Yellow);
            this->lines[2] = sf::Vertex(position + size, sf::Color::Yellow);
            this->lines[3] = sf::Vertex(position + sf::Vector2f(0, size.y), sf::Color::Yellow);
            this->lines[4] = sf::Vertex(position, sf::Color::Yellow);
        }

        sf::FloatRect boundary;
        ushort capacity{};
        bool divided{};
        sf::Vertex lines[5];

        std::vector<DataType *> objects{};

        Node *NE;
        Node *NW;
        Node *SE;
        Node *SW;

        // Subdivides the QuadTree into 4 smaller QuadTrees
        void subdivide()
        {
            const float x1 = boundary.left;
            const float y1 = boundary.top;
            const float x2 = boundary.width + x1;
            const float y2 = boundary.height + y1;

            // setting sides for each rectangle appropriately
            const sf::Vector2f size(boundary.width / 2, boundary.height / 2);

            sf::FloatRect ne(sf::Vector2f((x1 + x2) / 2, y1), size);
            sf::FloatRect nw(sf::Vector2f(x1, y1), size);
            sf::FloatRect se(sf::Vector2f((x1 + x2) / 2, (y1 + y2) / 2), size);
            sf::FloatRect sw(sf::Vector2f(x1, (y1 + y2) / 2), size);

            NE = new Node(ne, capacity); // north east
            NW = new Node(nw, capacity); // north west
            SE = new Node(se, capacity); // south east
            SW = new Node(sw, capacity); // south west

            this->divided = true;
        }
        void draw(sf::RenderWindow* window) const {
            window->draw(this->lines, 5, sf::LineStrip);
        }
    };

    typedef Node *NodePtr;

    NodePtr root;

    // helper functions for the public recursive functions

    void insert_helper(DataType *object, NodePtr node);

    void query_helper(sf::FloatRect range, std::vector<DataType *> &objectsFound, NodePtr node);

    bool search_helper(DataType *object, NodePtr node);

    void reset_helper(NodePtr node);

    void draw_helper(sf::RenderWindow *window, NodePtr node);

public:
    // No Argument Constructor
    QuadTree();

    // Destructor
    ~QuadTree();

    // Constructor
    QuadTree(sf::FloatRect boundary, ushort capacity);

    void setData(sf::FloatRect boundary, ushort capacity);

    // Resets the QuadTree (Removes all objects & deletes all nodes)
    void reset();

    // Inserts an object into the QuadTree
    void insert(DataType *object);

    // Returns all objects that are within a given range
    void query(sf::FloatRect range, std::vector<DataType *> &objectsFound);

    // Returns true if the object is in the tree
    bool search(DataType *object);

    // Returns true if the two objects are equal
    bool equals(DataType *A, DataType *B);

    // Draws the QuadTree borders on an sf::RenderWindow
    void draw(sf::RenderWindow *window);
};

template <class DataType>
QuadTree<DataType>::QuadTree()
{
    root = nullptr;
}

template <class DataType>
QuadTree<DataType>::QuadTree(sf::FloatRect boundary, ushort capacity)
{
    setData(boundary, capacity);
}

template <class DataType>
QuadTree<DataType>::~QuadTree()
{
    reset();
}

template <class DataType>
void QuadTree<DataType>::setData(sf::FloatRect boundary, ushort capacity)
{
    root = new Node(boundary, capacity);
}

template <class DataType>
void QuadTree<DataType>::reset()
{
    reset_helper(root);
}

template <class DataType>
void QuadTree<DataType>::reset_helper(NodePtr node)
{
    if (node->divided)
    {
        reset_helper(node->NE);
        reset_helper(node->NW);
        reset_helper(node->SE);
        reset_helper(node->SW);

        node->divided = false;

        delete node->NE;
        delete node->NW;
        delete node->SE;
        delete node->SW;
    }
    node->objects.clear();
}

template <class DataType>
void QuadTree<DataType>::insert(DataType *object)
{
    insert_helper(object, root);
}

template <class DataType>
void QuadTree<DataType>::insert_helper(DataType *object, NodePtr node)
{
    //// the search function considerably slows down the Quad Tree
    //// as it recursively checks the whole quad tree for the object
    //// everytime insert is called, so it is better to not use it
    //// and make sure not to reinsert the object into the tree

    //// if the object is already in the tree, it returns
    // if (search_helper(object, node))
    //     return;

    // if the object is not within the boundary, it returns
    if (!node->boundary.intersects(object->getGlobalBounds()))
        return;

    // adds the object to the if capacity is not reached yet
    if (node->objects.size() < node->capacity)
        node->objects.push_back(object);
    else
    {
        if (!node->divided)
            node->subdivide();

        insert_helper(object, node->NE);
        insert_helper(object, node->NW);
        insert_helper(object, node->SE);
        insert_helper(object, node->SW);
    }
}

template <class DataType>
void QuadTree<DataType>::query(sf::FloatRect range, std::vector<DataType *> &objectsFound)
{
    query_helper(range, objectsFound, root);
}

template <class DataType>
void QuadTree<DataType>::query_helper(sf::FloatRect range, std::vector<DataType *> &objectsFound, NodePtr node)
{
    if (!node->boundary.intersects(range))
        return;
    else
    {
        for (ushort i = 0; i < node->objects.size(); i++)
        {
            if (range.intersects(node->objects[i]->getGlobalBounds()))
            {
                // does not push the object itself back into the set
                if (range == node->objects[i]->getGlobalBounds())
                    continue;

                bool duplicate = false;
                for (ushort j = 0; j < objectsFound.size(); j++)
                {
                    if (equals(node->objects[i], objectsFound[j]))
                    {
                        duplicate = true;
                        break;
                    }
                }
                if (!duplicate)
                    objectsFound.push_back(node->objects[i]);
            }
        }
        if (node->divided)
        { // gets all objects in the sub trees that exist
            query_helper(range, objectsFound, node->NE);
            query_helper(range, objectsFound, node->NW);
            query_helper(range, objectsFound, node->SE);
            query_helper(range, objectsFound, node->SW);
        }
    }
}

template <class DataType>
bool QuadTree<DataType>::search(DataType *object)
{
    return search_helper(object, root);
}

template <class DataType>
bool QuadTree<DataType>::search_helper(DataType *object, NodePtr node)
{
    for (ushort i = 0; i < node->objects.size(); i++)
    {
        if (equals(object, node->objects[i]))
            return true;
    }
    if (node->divided)
    {
        if (search_helper(object, node->NE))
            return true;
        if (search_helper(object, node->NW))
            return true;
        if (search_helper(object, node->SE))
            return true;
        if (search_helper(object, node->SW))
            return true;
    }
    return false;
}

template <class DataType>
void QuadTree<DataType>::draw(sf::RenderWindow *window)
{
    draw_helper(window, root);
}

template <class DataType>
void QuadTree<DataType>::draw_helper(sf::RenderWindow *window, NodePtr node)
{
    node->draw(window);

    if (node->divided)
    {
        draw_helper(window, node->NE);
        draw_helper(window, node->NW);
        draw_helper(window, node->SE);
        draw_helper(window, node->SW);
    }
}

template <class DataType>
inline bool QuadTree<DataType>::equals(DataType *A, DataType *B)
{
    return A->getGlobalBounds() == B->getGlobalBounds() && A->getPosition() == B->getPosition();
}
