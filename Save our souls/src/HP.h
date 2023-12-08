#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;
using namespace sf;

extern int g_screen_width;
extern int g_screen_height;

class HP {
private:
    int m_hp;
    int m_count = 2;
    String m_file_hp;
    Texture m_texture_full_hp;
    Texture m_texture_half_hp;
    Texture m_texture_empty_hp;
    Sprite m_sprite_full_hp;
    Sprite m_sprite_half_hp;
    Sprite m_sprite_empty_hp;

public:
    HP() : m_file_hp("particles.png"), m_hp(5)
    {
        m_texture_full_hp.loadFromFile("images/" + m_file_hp, IntRect(0, 20, 15, 20));
        m_texture_half_hp.loadFromFile("images/" + m_file_hp, IntRect(15, 20, 15, 20));
        m_texture_empty_hp.loadFromFile("images/" + m_file_hp, IntRect(0, 33, 15, 20));
        m_texture_full_hp.setRepeated(true);
        m_texture_half_hp.setRepeated(true);
        m_texture_empty_hp.setRepeated(true);
        m_sprite_full_hp.setTextureRect(IntRect(0, 0, m_hp * 15 - 1, 11));
        m_sprite_half_hp.setTextureRect(IntRect(0, 0, m_hp * 15 - 1, 11));
        m_sprite_empty_hp.setTextureRect(IntRect(0, 0, m_hp * 15 - 1, 11));
        m_sprite_full_hp.setTexture(m_texture_full_hp);
        m_sprite_half_hp.setTexture(m_texture_half_hp);
        m_sprite_empty_hp.setTexture(m_texture_empty_hp);
        m_sprite_half_hp.scale(4, 4);
        m_sprite_full_hp.scale(4, 4);
        m_sprite_empty_hp.scale(4, 4);
        m_sprite_full_hp.setPosition(5, 5);
        m_sprite_half_hp.setPosition(5, 5);
        m_sprite_empty_hp.setPosition(5, 5);
    }

    HP(int hp) : m_file_hp("particles.png"), m_hp(hp)
    {
        m_texture_full_hp.loadFromFile("images/" + m_file_hp, IntRect(0, 20, 15, 20));
        m_texture_half_hp.loadFromFile("images/" + m_file_hp, IntRect(15, 20, 15, 20));
        m_texture_empty_hp.loadFromFile("images/" + m_file_hp, IntRect(0, 33, 15, 20));
        m_texture_full_hp.setRepeated(true);
        m_texture_half_hp.setRepeated(true);
        m_texture_empty_hp.setRepeated(true);
        m_sprite_full_hp.setTextureRect(IntRect(0, 0, m_hp * 15 - 1, 11));
        m_sprite_half_hp.setTextureRect(IntRect(0, 0, m_hp * 15 - 1, 11));
        m_sprite_empty_hp.setTextureRect(IntRect(0, 0, m_hp * 15 - 1, 11));
        m_sprite_full_hp.setTexture(m_texture_full_hp);
        m_sprite_half_hp.setTexture(m_texture_half_hp);
        m_sprite_empty_hp.setTexture(m_texture_empty_hp);
        m_sprite_half_hp.scale(4, 4);
        m_sprite_full_hp.scale(4, 4);
        m_sprite_empty_hp.scale(4, 4);
        m_sprite_full_hp.setPosition(5, 5);
        m_sprite_half_hp.setPosition(5, 5);
        m_sprite_empty_hp.setPosition(5, 5);
    }

    void setHP(int hp) {
        m_hp = hp;
    }

    void draw_full_hp(RenderWindow& window)
    {
        window.draw(m_sprite_full_hp);
    }

    void draw_half_hp(RenderWindow& window)
    {
        window.draw(m_sprite_half_hp);
    }

    void draw_empty_hp(RenderWindow& window)
    {
        window.draw(m_sprite_empty_hp);
    }

    int check() {
        return m_hp;
    }

    void damage() {
        --m_count;
        if (m_hp >= 0) {
            if (m_count % 2 == 1 and m_hp > 0) {
                --m_hp;
                m_sprite_full_hp.setTextureRect(IntRect(0, 0, m_hp * 15 - 1, 11));
                //RectangleShape rectangle(Vector2f(g_screen_width, g_screen_height));
                //rectangle.setFillColor(Color(255, 0, 0, 64));
                //window.draw(rectangle);
                //window.display();
            }
            else {
                m_sprite_half_hp.setTextureRect(IntRect(0, 0, m_hp * 15 - 1, 11));
                m_count = 2;
                //RectangleShape rectangle(Vector2f(g_screen_width, g_screen_height));
                //rectangle.setFillColor(Color(255, 0, 0, 64));
                //window.draw(rectangle);
                //window.display();
            }
        }
    }
};