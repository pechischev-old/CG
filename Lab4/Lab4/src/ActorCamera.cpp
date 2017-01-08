#include "libutil_private.h"
#include "ActorCamera.h"
#include "Transform3D.h"


namespace
{
	const float ROTATION_SPEED_RADIANS = 3.f;
	const float LINEAR_MOVE_SPEED = 100.f;
	const float MIN_SPEED = -1000.f;
	const float MAX_SPEED = 1000.f;

	bool ShouldTrackKeyPressed(const SDL_Keysym &key)
	{
		switch (key.sym)
		{
		case SDLK_UP:
		case SDLK_DOWN:
		case SDLK_SPACE:
		case SDLK_w:
		case SDLK_a:
		case SDLK_s:
		case SDLK_d:
		case SDLK_q:
		case SDLK_e:
			return true;
		}
		return false;
	}

	float GetThrottleChangeSpeed(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_UP))
		{
			return -LINEAR_MOVE_SPEED;
		}
		if (keysPressed.count(SDLK_DOWN))
		{
			return +LINEAR_MOVE_SPEED;
		}
		return 0;
	}

	bool GetBrakesEnabled(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_SPACE))
		{
			return true;
		}
		return false;
	}

	float GetYawRotationSpeedRadians(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_d))
		{
			return +ROTATION_SPEED_RADIANS;
		}
		if (keysPressed.count(SDLK_a))
		{
			return -ROTATION_SPEED_RADIANS;
		}
		return 0;
	}

	float GetPitchRotationSpeedRadians(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_w))
		{
			return +ROTATION_SPEED_RADIANS;
		}
		if (keysPressed.count(SDLK_s))
		{
			return -ROTATION_SPEED_RADIANS;
		}
		return 0;
	}

	float GetRollRotationSpeedRadians(std::set<unsigned> & keysPressed)
	{
		if (keysPressed.count(SDLK_e))
		{
			return +ROTATION_SPEED_RADIANS;
		}
		if (keysPressed.count(SDLK_q))
		{
			return -ROTATION_SPEED_RADIANS;
		}
		return 0;
	}
}


CCamera::CCamera(glm::vec3 const & position, glm::vec3 const & direction)
	: m_position(position)
	, m_direction(glm::quat_cast(glm::yawPitchRoll(direction.x, direction.y, direction.z)))
{
}

void CCamera::Update(float deltaSec)
{
	const float yaw = deltaSec * GetYawRotationSpeedRadians(m_keysPressed);
	const float pitch = deltaSec * GetPitchRotationSpeedRadians(m_keysPressed);
	const float roll = deltaSec * GetRollRotationSpeedRadians(m_keysPressed);

	const glm::quat rotation = glm::quat_cast(glm::yawPitchRoll(yaw, pitch, roll));
	m_direction = rotation * m_direction;

	if (roll == 0)
	{
		const glm::vec3 axis = glm::axis(m_direction);
		const float angle = glm::angle(m_direction);
		if (angle != 0)
		{
			const float autoRollAngle = ROTATION_SPEED_RADIANS * deltaSec * 0.1;
			const float newAngle = std::fminf(std::fabsf(angle), autoRollAngle) * ((angle < 0) ? 1 : -1);
			m_direction = glm::angleAxis(angle, axis);
		}
	}
	m_direction = glm::normalize(m_direction);

	m_speed += deltaSec * GetThrottleChangeSpeed(m_keysPressed);
	if (GetBrakesEnabled(m_keysPressed))
	{
		m_speed = 0;
	}
	else
	{
		m_speed = (m_speed > MAX_SPEED) ? MAX_SPEED : m_speed;
		m_speed = (m_speed < MIN_SPEED) ? MIN_SPEED : m_speed;
	}

	const float distance = deltaSec * m_speed;
	glm::vec3 translate = glm::vec3({ 0.f, 0.f, distance }) * m_direction;
	m_position += translate;
}

bool CCamera::OnKeyDown(const SDL_KeyboardEvent &event)
{
	if (ShouldTrackKeyPressed(event.keysym))
	{
		m_keysPressed.insert(unsigned(event.keysym.sym));
		return true;
	}
	return false;
}

bool CCamera::OnKeyUp(const SDL_KeyboardEvent &event)
{
	if (ShouldTrackKeyPressed(event.keysym))
	{
		m_keysPressed.erase(unsigned(event.keysym.sym));
		return true;
	}
	return false;
}

glm::mat4 CCamera::GetViewTransform() const
{
	CTransform3D transform;
	transform.m_position = m_position * -1.f;
	transform.m_orientation = m_direction * -1.f;
	return transform.ToMat4ForCamera();
}


glm::vec3 CCamera::GetPosition() const
{
	return m_position;
}


glm::quat CCamera::GetDirection() const
{
	return m_direction;
}