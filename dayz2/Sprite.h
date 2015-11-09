#pragma once

#include <GL\glew.h>
#include <glm\vec2.hpp>

class Sprite 
{
    public:
		Sprite(int width, int height, float u, float v, GLuint texture) 
			: m_width(width), m_height(height), m_u(u), m_v(v), m_texture(texture) {}
        ~Sprite() {}
private:
        glm::vec2 m_pos;
        float m_rotation;
        float m_u, m_v;
        int m_width, m_height;
        GLuint m_texture;
};