#pragma once

#include "Point.h"
#include "HP.h"
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

extern int g_screen_width;
extern int g_screen_height;
extern HP hp;

extern array <Texture, 8> particles;

int getRandomNumber(int min, int max);

class Shell
{
private:
    float m_radius = 1;
    int m_max_radius;
    int m_hp;
    float m_growth;
    Point m_location;
    CircleShape m_bubble;

public:
    Shell() : m_hp(1), m_location(500, 500), m_growth(0.7), m_max_radius(50), m_bubble(m_radius, 80)
    {
        m_bubble.setTexture(&particles[(m_hp - 1)]);
    }

    Shell(int max_radius, float growth) : m_max_radius(max_radius), m_growth(growth), m_bubble(m_radius, 80)
    {
        m_location.setPoint(getRandomNumber(m_max_radius - m_radius, g_screen_width - m_max_radius - m_radius), getRandomNumber(m_max_radius - m_radius + 30, g_screen_height - m_max_radius - m_radius));

        int received = getRandomNumber(0, 7);
        if (received <= 4)
        {
            m_hp = 1;
        }
        else if (received <= 6)
        {
            m_hp = 2;
        }
        else
        {
            m_hp = 3;
        }
        m_bubble.setTexture(&particles[(m_hp - 1)]);
    }

    void increase(vector <Shell>& shells, int idx)
    {
        if (m_radius <= (m_max_radius))
        {
            m_radius += m_growth;
            m_location.setPoint(m_location.getX() - m_growth, m_location.getY() - m_growth);
            m_bubble.setPosition(m_location.getX(), m_location.getY());
            m_bubble.setRadius(m_radius);
        }
        else {
            hp.damage();
            shells.erase(shells.begin() + idx);
        }
    }

    bool inclusion(Point mouse) const
    {
        return  pow(mouse.getX() - (m_location.getX() + m_radius), 2) + pow(mouse.getY() - (m_location.getY() + m_radius), 2) <= pow(m_radius, 2);
    }

    int getHp() const
    {
        return m_hp;
    }

    void decreaseHp()
    {
        --m_hp;
        m_bubble.setTexture(&particles[(m_hp - 1)]);
    }

    void draw(RenderWindow& window)
    {
        window.draw(m_bubble);
    }
};