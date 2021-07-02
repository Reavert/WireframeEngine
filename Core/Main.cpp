#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "glew.h"
#include "freeglut.h"
#include "WireframeObject.h"
#include "ObjectLoader.h"
#include "Keyboard.h"
#include "Camera.h"
#include "fmod.hpp"
#define WINDOW_TITLE_PREFIX "Application"

FMOD::System* audioSystem;

int
CurrentWidth = 800,
CurrentHeight = 600,
WindowHandle = 0;

unsigned FrameCount = 0;

unsigned char keys[256];

GLfloat xPos = 0.0f;
GLfloat yPos = 0.0f;
GLfloat zPos = 0.0f;

GLfloat scale = 1.0f;

GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat rotZ = 0.0f;

GLfloat t = 0.0f;

WireframeObject* sphereObject;
WireframeObject* cubeObject;
WireframeObject* monkeyObject;

ObjectLoader* objectLoader;

ShaderProgram* mainProgram;
Camera* camera;

void Initialize(int, char* []);
void InitWindow(int, char* []);
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void MouseMoveFunction(int, int);
void Cleanup(void);

int main(int argc, char* argv[])
{
    Initialize(argc, argv);

    glutMainLoop();

    exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[])
{
    GLenum GlewInitResult;
    FMOD::System_Create(&audioSystem);
    audioSystem->init(512, FMOD_INIT_NORMAL, 0);

    FMOD::Sound* sound;
    audioSystem->createSound("Sounds/music.mp3", FMOD_3D, NULL, &sound);
    audioSystem->playSound(sound, 0, false, NULL);
    glewExperimental = GL_TRUE;
    InitWindow(argc, argv);
    
    GlewInitResult = glewInit();

    if (GLEW_OK != GlewInitResult) {
        fprintf(
            stderr,
            "ERROR: %s\n",
            glewGetErrorString(GlewInitResult)
        );
        exit(EXIT_FAILURE);
    }

    fprintf(
        stdout,
        "INFO: OpenGL Version: %s\n",
        glGetString(GL_VERSION)
    );

    mainProgram = new ShaderProgram("Shaders/vertex.glsl", "Shaders/fragment.glsl");
    mainProgram->Use();

    camera = new Camera(60.0f, CurrentWidth, CurrentHeight, 0.2f, 1000.0f);
    camera->UpdateProjection(mainProgram);
    camera->UpdateView(mainProgram);
    
    objectLoader = new ObjectLoader;

    ObjectInfo sphereInfo = objectLoader->Load("Objects/sphere.3d");
    ObjectInfo cubeInfo = objectLoader->Load("Objects/cube.3d");
    ObjectInfo monkeyInfo = objectLoader->Load("Objects/monke.3d");

    vector<Vector4> vertices;
    vector<GLuint> indices;

    Vector4 redColor = Vector4(1.0f, 0.0f, 0.0f);
    Vector4 greenColor = Vector4(0.0f, 1.0f, 0.0f);
    Vector4 blueColor = Vector4(0.0f, 0.0f, 1.0f);

    sphereObject = new WireframeObject(sphereInfo, redColor);
    cubeObject = new WireframeObject(cubeInfo, greenColor);
    monkeyObject = new WireframeObject(monkeyInfo, blueColor);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glPointSize(3.0f);
}

void InitWindow(int argc, char* argv[])
{
    glutInit(&argc, argv);

    glutInitContextVersion(4, 0);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);

    glutSetOption(
        GLUT_ACTION_ON_WINDOW_CLOSE,
        GLUT_ACTION_GLUTMAINLOOP_RETURNS
    );

    glutInitWindowSize(CurrentWidth, CurrentHeight);

    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

    WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

    if (WindowHandle < 1) {
        fprintf(
            stderr,
            "ERROR: Could not create a new rendering window.\n"
        );
        exit(EXIT_FAILURE);
    }

    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(RenderFunction);
    glutMotionFunc(MouseMoveFunction);
    glutKeyboardFunc(Keyboard::KeyboardDown);
    glutKeyboardUpFunc(Keyboard::KeyboardUp);
    glutIgnoreKeyRepeat(GL_TRUE);
    glutIdleFunc(IdleFunction);
    glutTimerFunc(0, TimerFunction, 0);
    glutCloseFunc(Cleanup);
}

void MouseMoveFunction(int x, int y)
{

}

void ResizeFunction(int Width, int Height)
{
    CurrentWidth = Width;
    CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void)
{
    GLenum ErrorCheckValue = glGetError();

    ++FrameCount;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (Keyboard::KeyPressed(LKEY_W))
        zPos += 0.001;
    if (Keyboard::KeyPressed(LKEY_S))
        zPos -= 0.001;
    if (Keyboard::KeyPressed(LKEY_D))
        xPos += 0.001;
    if (Keyboard::KeyPressed(LKEY_A))
        xPos -= 0.001;
    if (Keyboard::KeyPressed(LKEY_Q))
        yPos += 0.001;
    if (Keyboard::KeyPressed(LKEY_Z))
        yPos -= 0.001;
    if (Keyboard::KeyPressed(KEY_PLUS))
        scale += 0.001;
    if (Keyboard::KeyPressed(KEY_MINUS))
        scale -= 0.001;
    if (Keyboard::KeyPressed(KEY_2))
        rotX += 0.1;
    if (Keyboard::KeyPressed(KEY_8))
        rotX -= 0.1;
    if (Keyboard::KeyPressed(KEY_4))
        rotY -= 0.1;
    if (Keyboard::KeyPressed(KEY_6))
        rotY += 0.1;
    if (Keyboard::KeyPressed(KEY_7))
        rotZ += 0.1;
    if (Keyboard::KeyPressed(KEY_9))
        rotZ -= 0.1;

    camera->SetRotation(rotX, rotY, rotZ);
    Vector3 forward = camera->GetForwardVector();
    Vector3 up = camera->GetUpVector();
    printf("Forward: %f, %f, %f\n", forward.x, forward.y, forward.z);
    printf("Up: %f, %f, %f\n", up.x, up.y, up.z);

    camera->SetRotation(0.0f, 0.0f, 0.0f);
    camera->SetPosition(0.0f, 0.0f, -10.0f);
    camera->UpdateView(mainProgram);

    sphereObject->SetScale(1.0f, 1.0f, 1.0f);
    sphereObject->SetPosition(forward.x * 5.0f, forward.y * 5.0f, forward.z * 5.0f);
    
    cubeObject->SetScale(1.0f, 1.0f, 1.0f);
    cubeObject->SetPosition(up.x * 5.0f, up.y * 5.0f, up.z * 5.0f);
    
    monkeyObject->SetPosition(0.0f, 0.0f, 0.0f);
    monkeyObject->SetRotation(rotX, rotY, rotZ);

    sphereObject->Render(mainProgram);
    cubeObject->Render(mainProgram);
    monkeyObject->Render(mainProgram);

    t += 0.001;

    glutSwapBuffers();
}

void IdleFunction(void)
{
    glutPostRedisplay();
}

void TimerFunction(int Value)
{
    if (0 != Value) {
        int size = 512 + strlen(WINDOW_TITLE_PREFIX);
        char* TempString = (char*)
            malloc(size);
        sprintf_s(
            TempString,
            size,
            "%s: %d Frames Per Second @ %d x %d",
            WINDOW_TITLE_PREFIX,
            FrameCount * 4,
            CurrentWidth,
            CurrentHeight
        );
        
        glutSetWindowTitle(TempString);
        free(TempString);
    }

    FrameCount = 0;
    glutTimerFunc(250, TimerFunction, 1);
}

void Cleanup(void)
{
    delete sphereObject;
    delete cubeObject;

    delete objectLoader;
}
