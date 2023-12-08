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

class SwipeShell
{
private:
    float m_radius = 1;
    float m_target_radius = 1;
    int m_max_radius;
    float m_growth;
    float m_target_growth = 5;
    Point m_location;
    Point m_location_end;
    CircleShape m_bubble;
    CircleShape m_target_bubble;

public:
    bool active = false;

    SwipeShell() : m_location(500, 500), m_location_end(600, 600), m_growth(0.005), m_max_radius(250), m_bubble(m_max_radius, 80), m_target_bubble(m_radius, 80)
    {
        m_bubble.setTexture(&particles[3]);
        m_target_bubble.setTexture(&particles[4]);
    }

    SwipeShell(int max_radius, float growth) : m_max_radius(max_radius), m_growth(growth), m_bubble(max_radius, 80), m_target_bubble(m_radius, 80)
    {
        m_location.setPoint(getRandomNumber(m_max_radius - m_radius, g_screen_width - m_max_radius - m_radius + 10), getRandomNumber(m_max_radius - m_radius + 30, g_screen_height - m_max_radius - m_radius));
        m_location_end.setPoint(getRandomNumber(m_max_radius - m_radius , g_screen_width - m_max_radius - m_radius), getRandomNumber(m_max_radius - m_radius + 30, g_screen_height - m_max_radius - m_radius));

        m_bubble.setTexture(&particles[3]);
        m_bubble.setPosition(m_location.getX(), m_location.getY());

        m_target_bubble.setTexture(&particles[4]);
        m_target_bubble.setPosition(m_location_end.getX(), m_location_end.getY());
        m_target_bubble.setRadius(m_max_radius);
    }

    void increase(vector <SwipeShell>& swipeShells, int idx)
    {
        if (m_radius <= (m_max_radius - 10))
        {
            m_radius += m_growth;
            m_bubble.setRadius(m_radius);

            m_location.setPoint(m_location.getX() - m_growth, m_location.getY() - m_growth);
            m_bubble.setPosition(m_location.getX(), m_location.getY());
        }

        else {
            hp.damage();
            swipeShells.erase(swipeShells.begin() + idx);
        }

        if (m_target_radius <= (m_max_radius))
        {
            m_target_radius += m_target_growth;
            m_target_bubble.setRadius(m_target_radius);

            m_location_end.setPoint(m_location_end.getX() - m_target_growth, m_location_end.getY() - m_target_growth);
            m_target_bubble.setPosition(m_location_end.getX(), m_location_end.getY());
        }

    };

    void follow(Point mouse)
    {
        m_location.setPoint(mouse.getX() - m_radius, mouse.getY() - m_radius);
    }

    bool inclusion(Point mouse)
    {
        return pow(mouse.getX() - (m_location.getX() + m_radius), 2) + pow(mouse.getY() - (m_location.getY() + m_radius), 2) <= pow(m_radius, 2);
    }

    bool inclusion_end(Point mouse)
    {
        return pow(mouse.getX() - (m_location_end.getX() + m_max_radius), 2) + pow(mouse.getY() - (m_location_end.getY() + m_max_radius), 2) <= pow(m_max_radius + 10, 2);
    }

    void draw(RenderWindow& window)
    {
        window.draw(m_target_bubble);
        window.draw(m_bubble);
    }
};