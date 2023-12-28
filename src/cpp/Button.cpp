#include "../hpp/Button.hpp"

Button::Button()
{
    init();
}

Button::Button(const sf::Font &font)
{
    this->font = font;
    init();
}

void Button::init()
{
    mouseOver = pressed  = disabled = false;

    border.setFillColor(sf::Color::Transparent);

    text.setString("Button");
    onAction = []() {};
}

void Button::setDisabled(bool disabled)
{
    this->disabled = disabled;
}

void Button::setFont(const sf::Font& font)
{
    this->font = font;
    text.setFont(font);
}

void Button::setCharacterSize(const int size)
{
    text.setCharacterSize(size);
    border.setSize(sf::Vector2f(text.getGlobalBounds().width * 1.1, text.getGlobalBounds().height * 1.2));
    sf::FloatRect temp = text.getGlobalBounds();
    text.setOrigin(temp.left + temp.width / 2, temp.top + temp.height / 2);
}

void Button::setPosition(const sf::Vector2f position)
{
    text.setPosition(position);

    sf::FloatRect temp = text.getLocalBounds();
    text.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);

    temp = border.getLocalBounds();
    border.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    border.setPosition(position);
}

void Button::setText(const std::string& text, const sf::Color color)
{
    this->text.setString(text);
    this->text.setFillColor(color);
    textColor = color;
    hoverColor = color;

    border.setSize(sf::Vector2f(this->text.getGlobalBounds().width * 1.1, this->text.getGlobalBounds().height*1.35));
    setPosition(border.getPosition());
}

void Button::setString(const std::string& text)
{
    this->text.setString(text);
    border.setSize(sf::Vector2f(this->text.getGlobalBounds().width * 1.1, this->text.getGlobalBounds().height*1.35));
    setPosition(border.getPosition());
}

void Button::setBorder(const sf::Color color, const int thickness)
{
    border.setOutlineThickness(thickness);
    borderColor = color;
    border.setOutlineColor(color);
}

void Button::setBackgroundColor(const sf::Color color)
{
    backgroundColor = color;
    border.setFillColor(color);
}

void Button::setOnAction(const std::function<void()>& onAction)
{
    this->onAction = onAction;
}

std::function<void()> Button::getOnAction() const
{
    return onAction;
}

void Button::handleInput(sf::Event event)
{
    if (disabled)
        return;

    if (event.type == sf::Event::MouseButtonPressed)
    {
        switch (event.mouseButton.button)
        {
        case sf::Mouse::Left:
            if (mouseOver)
                pressed = true;
            break;
        default: ;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        switch (event.mouseButton.button)
        {
        case sf::Mouse::Left:
            if (mouseOver)
                onAction();
            break;
        }
        pressed = false;
    }
}

void Button::update(const sf::RenderWindow *window)
{

    if (disabled)
        return;

    if (isMouseOver(border, window))
        mouseOver = true;
    else
        mouseOver = false;

    if (mouseOver)
    {
        border.setOutlineColor(hoverColor);
        border.setFillColor(sf::Color::Transparent);
    }
    else
    {
        border.setOutlineColor(borderColor);
        border.setFillColor(backgroundColor);
    }

    if (pressed)
    {
        text.setFillColor(backgroundColor);
        border.setFillColor(textColor);
    }
    else
    {
        text.setFillColor(textColor);
        border.setFillColor(backgroundColor);
    }
}

void Button::render(sf::RenderWindow *window) const {
    window->draw(border);
    window->draw(text);

    if (disabled)
    {
        sf::RectangleShape disabledShade(border);
        disabledShade.setFillColor(sf::Color(0, 0, 0, 150));
        window->draw(disabledShade);
    }
}

sf::FloatRect Button::getGlobalBounds() const
{
    return border.getGlobalBounds();
}

sf::FloatRect Button::getLocalBounds() const
{
    return border.getLocalBounds();
}

sf::Vector2f Button::getPosition() const
{
    return border.getPosition();
}

void Button::setTextColor(sf::Color color)
{
    text.setFillColor(color);
    textColor = color;
    hoverColor = color;
}

sf::Color Button::getTextColor() const
{
    return textColor;
}

bool Button::isMouseOver() const
{
    return mouseOver;
}

bool Button::isMouseOver(const sf::RectangleShape& sprite, const sf::RenderWindow *window) const
{
    return sprite.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}