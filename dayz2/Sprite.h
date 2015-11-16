#pragma once

#include <GL\glew.h>
#include <glm\vec2.hpp>

class CSprite 
{
    public:
		CSprite(int width, int height, float u1, float v1, float u2, float v2, GLuint texture) 
			: m_width(width), m_height(height), m_u1(u1), m_v1(v1), m_u2(u2), m_v2(v2), m_texture(texture) {}
        ~CSprite() {}

        glm::vec2 m_pos;
        float m_rotation;
        float m_u1, m_u2, m_v1, m_v2;
        int m_width, m_height;
        GLuint m_texture;
};