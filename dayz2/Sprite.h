#pragma once

#include <GL\glew.h>
#include "Vec2.h"

class Sprite 
{
    public:
		Sprite(int width, int height, float u, float v, GLuint texture) 
			: m_width(width), m_height(height), m_u(u), m_v(v), m_texture(texture) {}
        ~Sprite() {}
private:
        Vec2 m_pos;
        float m_rotation;
        float m_u, m_v;
        int m_width, m_height;
        GLuint m_texture;
};