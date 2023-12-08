#pragma once

class Point
{
private:
    float m_x;
    float m_y;

public:
    // Конструктор по умолчанию
    Point()
        : m_x(0.0), m_y(0.0)
    {
    }

    // Специфический конструктор
    Point(float x, float y)
        : m_x(x), m_y(y)
    {
    }

    // Изменяем X и Y
    void setPoint(float x, float y)
    {
        m_x = x;
        m_y = y;
    }

    // получаем X
    float getX() const
    {
        return m_x;
    }

    // получаем Y
    float getY() const
    {
        return m_y;
    }
};