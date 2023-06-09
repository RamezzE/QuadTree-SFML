#include "TextBox.hpp"
#include "Common.hpp"

TextBox::TextBox(sf::Font &font)
{
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(2);
    border.setSize(sf::Vector2f(100, text.getCharacterSize()));

    borderColor = sf::Color::White;
    borderHoverColor = sf::Color::Green;
    borderSelectedColor = sf::Color::Red;

    border.setOutlineColor(borderColor);
    selected = hover = false;
    textLimit = 15;
}

void TextBox::handleInput(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        switch (event.mouseButton.button)
        {
        case sf::Mouse::Left:
            if (hover)
                selected = true;
            else
                selected = false;
            break;
        }
    }
    else if (event.type == sf::Event::TextEntered)
    {
        if (!selected)
            return;

        ushort inputCode = event.text.unicode;

        if (inputCode == BACKSPACE && inputString.length() > 0)
            inputString.erase(inputString.length() - 1, inputString.length());

        if (inputString.length() >= textLimit)
            return;

        if (typeAllowed == NUMBER_ONLY || typeAllowed == ALPHA_NUMERIC)
        {
            if (inputCode >= sf::Keyboard::Numpad0 && inputCode <= sf::Keyboard::Numpad9)
                inputString += static_cast<char>(inputCode - sf::Keyboard::Numpad0 + '0');

            else if (inputCode >= ZERO && inputCode <= NINE || inputCode == PERIOD)
                inputString += static_cast<char>(inputCode);
        }

        if (typeAllowed == ALPHA_ONLY || typeAllowed == ALPHA_NUMERIC)
        {
            if ((inputCode >= A && inputCode <= Z) || (inputCode >= A_CAPS && inputCode <= Z_CAPS))
                inputString += static_cast<char>(inputCode);
        }

        text.setString(inputString);
    }
}

void TextBox::update(sf::RenderWindow *window)
{
    if (Input::isMouseOver(*this, window))
    {
        hover = true;
        border.setOutlineColor(borderHoverColor);
        return;
    }

    hover = false;
    border.setOutlineColor(borderColor);

    if (selected)
        border.setOutlineColor(borderSelectedColor);
}

void TextBox::draw(sf::RenderWindow(*window))
{
    window->draw(border);
    window->draw(text);
}

void TextBox::setSize(sf::Vector2f size)
{
    border.setSize(size);
}

void TextBox::setPosition(sf::Vector2f position)
{
    this->position = position;
    border.setPosition(position);
    border.move(-2, text.getCharacterSize() * 0.1f);
    text.setPosition(position);
}

void TextBox::setOrigin(sf::Vector2f origin)
{
    this->origin = origin;
    border.setOrigin(origin);
    text.setOrigin(origin);
}

void TextBox::setBorder(float thickness, sf::Color color, sf::Color hoverColor, sf::Color selectedColor)
{
    border.setOutlineColor(color);
    borderHoverColor = hoverColor;
    borderSelectedColor = selectedColor;
    border.setOutlineThickness(thickness);
}

void TextBox::setString(std::string str)
{
    inputString = str;
    text.setString(inputString);
}

void TextBox::setTextFormat(sf::Color color, ushort size)
{
    text.setFillColor(color);
    text.setCharacterSize(size);
}

void TextBox::setTextLimit(int limit)
{
    this->textLimit = limit;
}

void TextBox::setSelected(bool selected)
{
    this->selected = selected;
}

void TextBox::allowAlphaOnly()
{
    typeAllowed = ALPHA_ONLY;
}

void TextBox::allowNumberOnly()
{
    typeAllowed = NUMBER_ONLY;
}

void TextBox::allowAlphaNumeric()
{
    typeAllowed = ALPHA_NUMERIC;
}

int TextBox::getCharacterSize()
{
    return text.getCharacterSize();
}

sf::Vector2f TextBox::getPostion()
{
    return position;
}

sf::FloatRect TextBox::getGlobalBounds()
{
    return border.getGlobalBounds();
}

bool TextBox::isHovered()
{
    return hover;
}

bool TextBox::isSelected()
{
    return selected;
}

std::string TextBox::getString()
{
    return inputString;
}
