#pragma once

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <boost/noncopyable.hpp>
#include <set> 

class CCamera : private boost::noncopyable
{
public:
    CCamera(glm::vec3 const & position, glm::vec3 const & direction);

	void Update(float deltaSec);
	bool OnKeyDown(const SDL_KeyboardEvent &event);
	bool OnKeyUp(const SDL_KeyboardEvent &event);

    glm::mat4 GetViewTransform() const;

	glm::vec3 GetPosition() const;
	glm::quat GetDirection() const;

private:
	glm::vec3 m_position;
	glm::quat m_direction;
	float m_speed;
	float m_roll;

	std::set<unsigned> m_keysPressed;
};
