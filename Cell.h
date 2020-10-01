#pragma once

class Cell : public sf::Drawable, public sf::Transformable
{
private:
    sf::VertexArray m_quad;
    sf::Color m_color;

    float m_size;
    float m_padding;
public:
    // Constructer + Destructor
    Cell(float size, float padding, sf::Color color);
    virtual ~Cell();

    // Drawable
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Functions
    void init();
    void appendMe(sf::VertexArray& array);

    // Setter
    void setColor(sf::Color color);

    // Getter
};
