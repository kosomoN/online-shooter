#pragma once

#include <GL\glew.h>
#include <glm\vec2.hpp>
#include <glm\vec4.hpp>
#include <vector>
#include <string>
#include "Animation.h"

class CSprite 
{
    public:
		CSprite(int width, int height, float u1, float v1, float u2, float v2, GLuint texid)
			: m_width(width), m_height(height), m_u1(u1), m_v1(v1), m_u2(u2), m_v2(v2), m_texture(texid){}
		virtual ~CSprite() {}

        glm::vec2 m_pos;
        float m_rotation = 0;
        float m_u1, m_u2, m_v1, m_v2;
        int m_width, m_height;
        GLuint m_texture;
		CAnimation* m_pAnim = nullptr;
		bool m_shouldDraw = true;
		glm::vec2 m_rotPointOffset = glm::vec2(0.5);
private:
};