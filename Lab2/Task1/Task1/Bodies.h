#pragma once

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>
#include <boost/noncopyable.hpp>

class CIdentityCube
{
public:
    void Update(float deltaTime);
    void Draw()const;
};
