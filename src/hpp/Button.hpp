#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button
{
public:
    Button();
    Button(sf::Font &font);
    
    void handleInput(sf::Event event);
    void update(sf::RenderWindow *window);
    void render(sf::RenderWindow *window);

    void setPosition(sf::Vector2f position);
    void setDisabled(bool disabled);

    void setFont(sf::Font &font);
    void setBorder(sf::Color color, int thickness);
    void setText(std::string text,sf::Color color);
    void setString(std::string text);
    void setCharacterSize(int size);
    void setTextColor(sf::Color color);
    void setBackgroundColor(sf::Color color);
    void setBackground(sf::Texture &texture);

    void setOnAction(std::function<void()> onAction);

    bool isMouseOver();

    sf::FloatRect getGlobalBounds();
    sf::FloatRect getLocalBounds();
    sf::Vector2f getPosition();
    sf::Color getTextColor();
    std::function<void()> getOnAction();

private:
    void init();

    bool isMouseOver(sf::RectangleShape sprite, sf::RenderWindow *window);

    sf::RectangleShape border;
    sf::Font font;
    sf::Text text;

    bool mouseOver, pressed, disabled;

    sf::Color backgroundColor, borderColor, textColor, hoverColor;

    std::function<void()> onAction;
};