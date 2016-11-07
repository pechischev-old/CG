#include "Window.h"
#include "AbstractWindowClient.h"
#include "Utils.h"
#include "libchapter3_private.h"
#include <SDL2/SDL.h>

namespace
{
glm::vec2 GetMousePosition(const SDL_MouseButtonEvent &event)
{
    return { event.x, event.y };
}

glm::vec2 GetMousePosition(const SDL_MouseMotionEvent &event)
{
    return { event.x, event.y };
}

void DispatchEvent(const SDL_Event &event, IWindowClient &acceptor)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        acceptor.OnKeyDown(event.key);
        break;
    case SDL_KEYUP:
        acceptor.OnKeyUp(event.key);
        break;
    case SDL_MOUSEBUTTONDOWN:
        acceptor.OnDragBegin(GetMousePosition(event.button));
        break;
    case SDL_MOUSEBUTTONUP:
        acceptor.OnDragEnd(GetMousePosition(event.button));
        break;
    case SDL_MOUSEMOTION:
        acceptor.OnDragMotion(GetMousePosition(event.motion));
        break;
    }
}

void SetupProfileAttributes(ContextProfile profile, ContextMode mode)
{
    // Включаем режим сглаживания с помощью субпиксельного рендеринга.
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    // Выбираем версию и параметры совместимости контекста
    bool makeRobust = true;
    switch (profile)
    {
    case ContextProfile::Compatibility:
        makeRobust = false;
        break;
    case ContextProfile::RobustOpenGL_3_1:
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        break;
    case ContextProfile::RobustOpenGL_3_2:
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        break;
    case ContextProfile::RobustOpenGL_4_0:
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        break;
    }

    unsigned flags = 0;
    if (mode == ContextMode::Debug)
    {
        // Включаем поддержку отладочных средств
        //  в создаваемом контексте OpenGL.
        flags |= SDL_GL_CONTEXT_DEBUG_FLAG;
    }
    if (makeRobust)
    {
        // Отключаем поддержку старых средств из старых версий OpenGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        flags |= SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG;
    }
    else
    {
        // Включаем поддержку расширений для обратной совместимости
        // со старыми версиями OpenGL.
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    }
}

void GLAPIENTRY DebugOutputCallback(
	GLenum /*source*/,
	GLenum type,
	GLuint id,
	GLenum /*severity*/,
	GLsizei /*length*/,
	const GLchar* message,
	const void* /*userParam*/)
{
    // Отсекаем все сообщения, кроме ошибок
    if (type != GL_DEBUG_TYPE_ERROR)
    {
        return;
    }
    std::string formatted = "OpenGL error #" + std::to_string(id) + ": " + message;
    std::cerr << formatted << std::endl;
}

void SetupDebugOutputCallback()
{
    if (!GLEW_ARB_debug_output)
    {
        throw std::runtime_error("Cannot use debug output:"
                                 " it isn't supported by videodriver");
    }

    glEnable(GL_DEBUG_OUTPUT);

    // Синхронный режим позволяет узнать в отладчике контекст,
    //  в котором произошла ошибка.
    // Режим может понизить производительность, но на фоне
    //  других потерь Debug-сборки это несущественно.
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

    glDebugMessageCallback(DebugOutputCallback, nullptr);
    // Указываем видеодрайверу выдать только один тип сообщений,
    //  GL_DEBUG_TYPE_ERROR.
    glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, nullptr, GL_TRUE);
}
}

class CWindow::Impl
{
public:
    Impl(ContextProfile profile, ContextMode mode)
        : m_profile(profile)
        , m_contextMode(mode)
    {
    }

    void Show(const std::string &title, const glm::ivec2 &size)
    {
		m_size = size;

		CUtils::InitOnceSDL2();

        // Выбираем версию и параметры совместимости OpenGL.
        SetupProfileAttributes(m_profile, m_contextMode);

        // Специальное значение SDL_WINDOWPOS_CENTERED вместо x и y заставит SDL2
        // разместить окно в центре монитора по осям x и y.
        // Для использования OpenGL вы ДОЛЖНЫ указать флаг SDL_WINDOW_OPENGL.
        m_pWindow.reset(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                         size.x, size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));
        if (!m_pWindow)
        {
            const std::string reason = SDL_GetError();
            throw std::runtime_error("Cannot create window: " + reason);
        }

        // Создаём контекст OpenGL, связанный с окном.
        m_pGLContext.reset(SDL_GL_CreateContext(m_pWindow.get()));
		if (!m_pGLContext)
		{
			CUtils::ValidateSDL2Errors();
		}
        CUtils::InitOnceGLEW();

        // Устанавливаем функцию обработки отладочных сообщений.
        if (m_contextMode == ContextMode::Debug)
        {
            SetupDebugOutputCallback();
        }
    }

    glm::ivec2 GetWindowSize() const
    {
        return m_size;
    }

    void SetClient(IWindowClient *pClient)
    {
        m_pClient = pClient;
    }

    void DoMainLoop()
    {
		const std::chrono::milliseconds FRAME_PERIOD(16);

        SDL_Event event;
        CChronometer chronometer;
        while (true)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                if (!ConsumeEvent(event) && m_pClient)
                {
                    DispatchEvent(event, *m_pClient);
                }
            }
            if (m_isTerminated)
            {
                break;
            }
            // Обновление сцены.
            if (m_pClient)
            {
                const float deltaSeconds = chronometer.GrabDeltaTime();
                m_pClient->OnUpdateWindow(deltaSeconds);
            }
            // Очистка буфера кадра, обновление и рисование сцены, вывод буфера кадра.
            Clear();
            m_pClient->OnDrawWindow();
			CUtils::ValidateOpenGLErrors();
			SwapBuffers();
			chronometer.WaitNextFrameTime(FRAME_PERIOD);
        }
    }

    void SetBackgroundColor(const glm::vec4 &color)
    {
        m_clearColor = color;
    }

    void Clear()const
    {
        // Заливка кадра цветом фона средствами OpenGL
        glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void SwapBuffers()const
    {
        // Вывод нарисованного кадра в окно на экране.
        // При этом система отдаёт старый буфер для рисования нового кадра.
        // Обмен двух буферов вместо создания новых позволяет не тратить ресурсы впустую.
        SDL_GL_SwapWindow(m_pWindow.get());
    }

    bool ConsumeEvent(const SDL_Event &event)
    {
        bool consumed = false;
        if (event.type == SDL_QUIT)
        {
            m_isTerminated = true;
            consumed = true;
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            OnWindowEvent(event.window);
            consumed = true;
        }
        return consumed;
    }

private:
    void OnWindowEvent(const SDL_WindowEvent &event)
    {
        if (event.event == SDL_WINDOWEVENT_RESIZED)
        {
            m_size = {event.data1, event.data2};
        }
    }

    bool m_isTerminated = false;
    ContextProfile m_profile;
    ContextMode m_contextMode;
    IWindowClient *m_pClient = nullptr;
    SDLWindowPtr m_pWindow;
    SDLGLContextPtr m_pGLContext;
    glm::ivec2 m_size;
    glm::vec4 m_clearColor;
};

CWindow::CWindow(ContextProfile profile, ContextMode mode)
    : m_pImpl(new Impl(profile, mode))
{
}

CWindow::~CWindow()
{
}

void CWindow::Show(const std::string &title, const glm::ivec2 &size)
{
    m_pImpl->Show(title, size);
}

void CWindow::SetBackgroundColor(const glm::vec4 &color)
{
    m_pImpl->SetBackgroundColor(color);
}

void CWindow::SetClient(IWindowClient *pClient)
{
    m_pImpl->SetClient(pClient);
}

glm::ivec2 CWindow::GetWindowSize() const
{
    return m_pImpl->GetWindowSize();
}

void CWindow::DoMainLoop()
{
    m_pImpl->DoMainLoop();
}
