#include "../hpp/TextBox.hpp"

TextBox::TextBox(const sf::Font &font)
{
    text.setFont(font);
    this->font = font;
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineThickness(2);
    border.setSize(sf::Vector2f(100, text.getCharacterSize()));

    borderColor = sf::Color::White;
    borderHoverColor = sf::Color::Green;
    borderSelectedColor = sf::Color::Red;

    border.setOutlineColor(borderColor);
    selected = hover = validTextEntered = false;
    textLimit = 15;
    subsetCounter = 0;
    maxCharactersDisplayed = 99999;
}

void TextBox::handleInput(const sf::Event& event)
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
        default:
            break;
        }

    }
    else if (event.type == sf::Event::TextEntered)
    {
        const std::string tempString = inputString;

        if (!selected)
            return;

        const float inputCode = event.text.unicode;

        if (inputCode == BACKSPACE && !inputString.empty())
        {
            inputString.erase(inputString.length() - 1, inputString.length());
            validTextEntered = true;
        }

        if (inputString.length() >= textLimit)
            return;

        if (typeAllowed == ALPHA_ONLY || typeAllowed == ALPHA_NUMERIC)
        {
            if (!validTextEntered)
            {
                if ((inputCode >= A && inputCode <= Z) || (inputCode >= A_CAPS && inputCode <= Z_CAPS))
                {
                    inputString += static_cast<char>(inputCode);
                    validTextEntered = true;
                }

                if (inputCode == SPACE)
                    inputString += static_cast<char>(inputCode);
            }
        }

        if (typeAllowed == NUMBER_ONLY || typeAllowed == ALPHA_NUMERIC)
        {
            if (!validTextEntered)
            {
                if (inputCode >= sf::Keyboard::Numpad0 && inputCode <= sf::Keyboard::Numpad9)
                    inputString += static_cast<char>(inputCode - sf::Keyboard::Numpad0 + '0');

                else if (inputCode >= ZERO && inputCode <= NINE || inputCode == PERIOD)
                    inputString += static_cast<char>(inputCode);
            }
        }

        if (tempString == inputString)
            return;

        if (tempString.length() > inputString.length())
            subsetCounter--;
        else
            subsetCounter++;

        validTextEntered = true;
        text.setString(inputString);
    }
}

void TextBox::update(const sf::RenderWindow *window)
{
    if (subsetCounter < 0)
        subsetCounter = 0;

    if (validTextEntered)
    {
        if ((text.getGlobalBounds().left + text.getGlobalBounds().width) >= (border.getGlobalBounds().left + border.getGlobalBounds().width * 0.9))
        {
            text.setString(inputString.substr(subsetCounter, inputString.length() - 1));

            while ((text.getGlobalBounds().left + text.getGlobalBounds().width) >= (border.getGlobalBounds().left + border.getGlobalBounds().width * 0.9))
            {
                text.setString(static_cast<std::string>(text.getString()).substr(1));
                subsetCounter++;
            }
        }
        else if (text.getString() == inputString)
        {
            text.setString(inputString);
            subsetCounter = 0;
        }
        validTextEntered = false;
        return;
    }

    if (selected)
        border.setOutlineColor(borderSelectedColor);

    if (isMouseOver(window))
    {
        hover = true;
        if (!selected)
            border.setOutlineColor(borderHoverColor);
        return;
    }

    hover = false;
    if (!selected)
        border.setOutlineColor(borderColor);
}

void TextBox::draw(sf::RenderWindow(*window)) const {
    window->draw(border);
    window->draw(text);
}

void TextBox::setSize(const sf::Vector2f size)
{
    border.setSize(size);
    calculateMaxCharactersDisplayed();
}

void TextBox::setPosition(const sf::Vector2f position)
{
    this->position = position;
    border.setPosition(position);
    border.move(-2, text.getCharacterSize() * 0.1f);
    text.setPosition(position);
}

void TextBox::setOrigin(const sf::Vector2f origin)
{
    this->origin = origin;
    border.setOrigin(origin);
    text.setOrigin(origin);
}

void TextBox::setBorder(const float thickness, const sf::Color color, const sf::Color hoverColor, const sf::Color selectedColor)
{
    border.setOutlineColor(color);
    borderColor = color;
    borderHoverColor = hoverColor;
    borderSelectedColor = selectedColor;
    border.setOutlineThickness(thickness);
}

void TextBox::setString(const std::string& str)
{
    inputString = str;
    text.setString(inputString);
}

void TextBox::setTextFormat(const sf::Color color, const float size)
{
    text.setFillColor(color);
    text.setCharacterSize(size);
    calculateMaxCharactersDisplayed();
}

void TextBox::setTextColor(sf::Color color)
{
    text.setFillColor(color);
}

void TextBox::setTextLimit(const int limit)
{
    this->textLimit = limit;
}

void TextBox::setBackgroundColor(const sf::Color color)
{
    border.setFillColor(color);
}

void TextBox::setSelected(const bool selected)
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

int TextBox::getCharacterSize() const
{
    return text.getCharacterSize();
}

sf::Vector2f TextBox::getPosition() const
{
    return position;
}

sf::FloatRect TextBox::getGlobalBounds() const
{
    return border.getGlobalBounds();
}

sf::FloatRect TextBox::getLocalBounds() const
{
    return border.getLocalBounds();
}

bool TextBox::isHovered() const
{
    return hover;
}

bool TextBox::isSelected() const
{
    return selected;
}

std::string TextBox::getString() const
{
    return inputString;
}

bool TextBox::isMouseOver(const sf::RenderWindow *window) const
{
    return getGlobalBounds().contains(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
}

float TextBox::getCharacterWidth() const
{
    char c = 'A';
    const sf::Glyph glyph = font.getGlyph(c, getCharacterSize(), false);

    return glyph.advance;
}

int TextBox::calculateMaxCharactersDisplayed()
{
    const sf::FloatRect textBoxBounds = border.getGlobalBounds();
    const int maxChars = static_cast<int>(textBoxBounds.width / getCharacterWidth());
    maxCharactersDisplayed = maxChars;
    return maxChars;
}

bool TextBox::empty() const {
    return inputString.empty();
}
