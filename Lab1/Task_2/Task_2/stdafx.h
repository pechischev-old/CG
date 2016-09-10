// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL_events.h>

#include <chrono>
#include <type_traits>
#include <iostream>
#include <string>
#include <mutex>
#include <memory>
#include <vector>
#include <cmath>


struct SShape
{
	SShape() = delete;
	SShape(std::string const &type, glm::vec2 const & pos, glm::vec2 const & size, glm::vec3 const & color, float const & angle = 0)
		: type(type)
		, pos(pos)
		, size(size)
		, color(color)
		, angle(angle)
	{}
	std::string type;
	glm::vec2 pos;
	glm::vec3 color;
	glm::vec2 size;
	float angle;
};


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
