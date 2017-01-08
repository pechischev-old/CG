﻿#pragma once
#include <memory>
#include <chrono>
#include <glm/fwd.hpp>
#include <SDL2/SDL_video.h>

// Did you install SDL_ttf development files?
// see http://www.libsdl.org/projects/SDL_ttf/
#include <SDL2/SDL_ttf.h>

namespace detail
{
struct SDLWindowDeleter
{
	void operator()(SDL_Window *ptr)
	{
		SDL_DestroyWindow(ptr);
	}
};
struct SDLGLContextDeleter
{
	void operator()(SDL_GLContext ptr)
	{
		SDL_GL_DeleteContext(ptr);
	}
};
struct SDLSurfaceDeleter
{
    void operator()(SDL_Surface *ptr)
    {
        SDL_FreeSurface(ptr);
    }
};
struct TtfFontDeleter
{
    void operator ()(TTF_Font *font)
    {
        TTF_CloseFont(font);
    }
};
}

// Используем unique_ptr с явно заданным функтором удаления вместо delete.
using SDLWindowPtr = std::unique_ptr<SDL_Window, detail::SDLWindowDeleter>;
using SDLGLContextPtr = std::unique_ptr<void, detail::SDLGLContextDeleter>;
using SDLSurfacePtr = std::unique_ptr<SDL_Surface, detail::SDLSurfaceDeleter>;
using TTFFontPtr = std::unique_ptr<TTF_Font, detail::TtfFontDeleter>;

class CUtils
{
public:
	CUtils() = delete;

	static void InitOnceSDL2();
	static void InitOnceGLEW();
	static void ValidateSDL2Errors();
	static void ValidateOpenGLErrors();

    static void FlipSurfaceVertically(SDL_Surface &surface);
    static SDLSurfacePtr RenderUtf8Text(TTF_Font & font,
                                        const std::string &text,
                                        const glm::vec3 &color);
};

class CChronometer
{
public:
	CChronometer();
	float GrabDeltaTime();

	void WaitNextFrameTime(const std::chrono::milliseconds &framePeriod);

private:
	std::chrono::system_clock::time_point m_lastTime;
};
