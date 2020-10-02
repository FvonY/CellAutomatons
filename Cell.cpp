#include "stdafx.h"
#include "Cell.h"

// Constructer + Destructor

Cell::Cell(float size, float padding, sf::Color color) :
    m_color(color), m_size(size), m_padding(padding)
{
    init();
}

Cell::~Cell()
{
}

// Drawable

void Cell::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= this->getTransform();
    states.texture = NULL;
    target.draw(m_quad, states);
}

// Functions

void Cell::init()
{
    m_quad.setPrimitiveType(sf::PrimitiveType::Quads);
    m_quad.resize(4);

    m_quad[0] = sf::Vertex(sf::Vector2f(m_padding, m_padding), m_color);
    m_quad[1] = sf::Vertex(sf::Vector2f(m_size - m_padding, m_padding), m_color);
    m_quad[2] = sf::Vertex(sf::Vector2f(m_size - m_padding, m_size - m_padding), m_color);
    m_quad[3] = sf::Vertex(sf::Vector2f(m_padding, m_size - m_padding), m_color);

    this->setPosition(0.f, 0.f);
    std::cout << "Cell is init:" << m_size << "\n";

}

void Cell::appendMe(sf::VertexArray& array)
{
    sf::Vertex temp;
    
    temp = getTransform().transformPoint(m_quad[0].position);
    temp.color = m_color;
    array.append(temp);

    temp = getTransform().transformPoint(m_quad[1].position);
    temp.color = m_color;
    temp.color.a = 70;
    array.append(temp);

    temp = getTransform().transformPoint(m_quad[2].position);
    temp.color = m_color;
    array.append(temp);

    temp = getTransform().transformPoint(m_quad[3].position);
    temp.color = m_color;
    array.append(temp);
}

// Setter

void Cell::setColor(sf::Color color)
{
    m_color = color;

    m_quad[0].color = color;
    m_quad[1].color = color;
    m_quad[2].color = color;
    m_quad[3].color = color;
}
