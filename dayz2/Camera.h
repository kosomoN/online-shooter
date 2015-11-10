#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera(int width, int height);
	~Camera();

	void resize(int width, int height);
	void setPosition(const glm::vec2& pos);
	glm::mat4 getCombined() { return m_combined; }
private:
	glm::vec3 m_pos;
	glm::mat4 m_projection, m_translation, m_combined;
};

