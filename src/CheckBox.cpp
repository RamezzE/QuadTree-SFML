#include "CheckBox.hpp"

#include <iostream>

CheckBox::CheckBox()
{
    init();
}

void CheckBox::init()
{
    mouseOver = pressed = checked = disabled = false;
    checkedColor = sf::Color(178, 178, 178);

    border.setFillColor(sf::Color::Transparent);
}

void CheckBox::setDisabled(bool disabled)
{
    this->disabled = disabled;
}

void CheckBox::setSize(sf::Vector2f size) {
    border.setSize(size);
    sf::FloatRect temp = border.getLocalBounds();
    border.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
}

void CheckBox::setPosition(sf::Vector2f position)
{
    sf::FloatRect temp = border.getLocalBounds();
    border.setOrigin(temp.left + temp.width / 2.0f, temp.top + temp.height / 2.0f);
    border.setPosition(position);
}

void CheckBox::setBorder(sf::Color color, int thickness)
{
    border.setOutlineThickness(thickness);
    borderColor = color;
    border.setOutlineColor(color);
}

void CheckBox::setBackgroundColor(sf::Color color)
{
    backgroundColor = color;
    border.setFillColor(color);
}

void CheckBox::setCheckedColor(sf::Color color)
{
    checkedColor = color;
}

void CheckBox::handleInput(sf::Event event)
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
        }
    }

    if (event.type == sf::Event::MouseButtonReleased)
    {
        switch (event.mouseButton.button)
        {
        case sf::Mouse::Left:
            if (mouseOver)
                checked = !checked;
            break;
        }
        pressed = false;
    }
}

void CheckBox::update(sf::RenderWindow *window)
{
    if (disabled) {
        mouseOver = pressed = checked = false;
        return;
    }

    if (isMouseOver(border, window))
        mouseOver = true;
    else
        mouseOver = false;

    if (mouseOver)
        border.setOutlineColor(hoverColor);
    else
        border.setOutlineColor(borderColor);

    if (checked)
        border.setFillColor(checkedColor);
    else
        border.setFillColor(backgroundColor);
}

void CheckBox::render(sf::RenderWindow *window)
{
    if (disabled)
        return;
    
    window->draw(border);

    if (disabled) {
        sf::RectangleShape disabledShade(border);
        disabledShade.setFillColor(sf::Color(0, 0, 0, 150));
        window->draw(disabledShade);
    }
}

sf::FloatRect CheckBox::getGlobalBounds()
{
    return border.getGlobalBounds();
}

sf::FloatRect CheckBox::getLocalBounds()
{
    return border.getLocalBounds();
}

sf::Vector2f CheckBox::getPosition()
{
    return border.getPosition();
}

sf::Vector2f CheckBox::getSize() {
    return border.getSize();
}

bool CheckBox::isChecked()
{
    return checked;
}

bool CheckBox::isMouseOver()
{
    return mouseOver;
}

bool CheckBox::isMouseOver(sf::RectangleShape sprite, sf::RenderWindow *window)
{
    return sprite.getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}