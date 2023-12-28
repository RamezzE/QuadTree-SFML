#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

class Button
{
public:
    Button();
    explicit Button(const sf::Font &font);
    
    void handleInput(sf::Event event);
    void update(const sf::RenderWindow *window);
    void render(sf::RenderWindow *window) const;

    void setOrigin(sf::Vector2f origin);
    void setPosition(sf::Vector2f position);
    void setDisabled(bool disabled);
    void setPadding(float padding);

    void setFont(const sf::Font &font);
    void setBorder(sf::Color color, int thickness);
    void setText(const std::string& text,sf::Color color);
    void setString(const std::string& text);
    void setCharacterSize(int size);
    void setTextColor(sf::Color color);
    void setBackgroundColor(sf::Color color);
    void setBackground(sf::Texture &texture);

    void setOnAction(const std::function<void()>& onAction);

    bool isMouseOver() const;

    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;
    sf::Vector2f getPosition() const;
    sf::Color getTextColor() const;
    std::function<void()> getOnAction() const;

private:
    void init();

    bool isMouseOver(const sf::RectangleShape& sprite, const sf::RenderWindow *window) const;
    void resize();

    sf::RectangleShape border;
    sf::Font font;
    sf::Text text;

    bool mouseOver, pressed, disabled;
    float padding;

    sf::Color backgroundColor, borderColor, textColor, hoverColor;

    std::function<void()> onAction;
};