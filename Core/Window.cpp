#include "Window.h"

Window::Window(int argc, char* argv[])
{
    m_title = DEFAULT_TITLE;
    m_width = DEFAULT_WIDTH;
    m_height = DEFAULT_HEIGHT;

    InitWindow(argc, argv);
    glutMainLoop();
}

Window::~Window()
{
    exit(EXIT_SUCCESS);
}

void Window::InitWindow(int argc, char* argv[])
{
    GLenum glewInitResult;
    glewExperimental = GL_TRUE;

    glutInit(&argc, argv);

    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(m_width, m_height);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    m_handle = glutCreateWindow(m_title.c_str());

    if (m_handle < 1) {
        fprintf(
            stderr,
            "ERROR: Could not create a new rendering window.\n"
        );
        exit(EXIT_FAILURE);
    }

    glutReshapeFuncUcall(ResizeFunction, this);
    glutDisplayFuncUcall(RenderFunction, this);

    glutKeyboardFunc(Keyboard::KeyboardDown);
    glutKeyboardUpFunc(Keyboard::KeyboardUp);
    glutIgnoreKeyRepeat(GL_TRUE);

    glewInitResult = glewInit();

    if (GLEW_OK != glewInitResult) {
        fprintf(
            stderr,
            "ERROR: %s\n",
            glewGetErrorString(glewInitResult)
        );
        exit(EXIT_FAILURE);
    }

    fprintf(
        stdout,
        "INFO: OpenGL Version: %s\n",
        glGetString(GL_VERSION)
    );
}

void Window::SetTitle(std::string title)
{
    m_title = title;
    glutSetWindowTitle(m_title.c_str());
}

std::string Window::GetTitle()
{
    return m_title;
}

void Window::SetSize(uint32_t width, uint32_t height)
{
    m_width = width;
    m_height = height;
    glViewport(0, 0, m_width, m_height);
}

uint32_t Window::GetWidth()
{
    return m_height;
}

uint32_t Window::GetHeight()
{
    return m_height;
}

void Window::ResizeFunction(int width, int height, void* data)
{
    Window* sender = (Window*)data;

    sender->SetSize(width, height);
}

void Window::RenderFunction(void* data)
{
    Window* sender = (Window*)data;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rendering object here

    glutSwapBuffers();
}
