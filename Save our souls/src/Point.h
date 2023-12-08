#pragma once

class Point
{
private:
    float m_x;
    float m_y;

public:
    // ����������� �� ���������
    Point()
        : m_x(0.0), m_y(0.0)
    {
    }

    // ������������� �����������
    Point(float x, float y)
        : m_x(x), m_y(y)
    {
    }

    // �������� X � Y
    void setPoint(float x, float y)
    {
        m_x = x;
        m_y = y;
    }

    // �������� X
    float getX() const
    {
        return m_x;
    }

    // �������� Y
    float getY() const
    {
        return m_y;
    }
};