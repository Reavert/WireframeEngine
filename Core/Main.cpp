#include <stdlib.h>
#include <stdio.h>

#include "WireframeObject.h"
#include "ObjectLoader.h"
#include "Keyboard.h"
#include "Camera.h"
#include "fmod.hpp"
#include "Window.h"

GLfloat xPos = 0.0f;
GLfloat yPos = 0.0f;
GLfloat zPos = 0.0f;

GLfloat scale = 1.0f;

GLfloat xRot = 0.0f;
GLfloat yRot = 0.0f;
GLfloat zRot = 0.0f;

GLfloat t = 0.0f;

WireframeObject* sphereObject;
WireframeObject* cubeObject;
WireframeObject* monkeyObject;

ObjectLoader* objectLoader;

ShaderProgram* mainProgram;
Camera* camera;

FMOD::System* audioSystem;
FMOD::Sound* sound;
FMOD::Channel* channel;

FMOD_VECTOR soundPosition = { 0.0f, 0.0f, 0.0f };
FMOD_VECTOR soundVelocity = { 0.0f, 0.0f, 0.0f };

FMOD_VECTOR listenerPosition;
FMOD_VECTOR listenerForward;
FMOD_VECTOR listenerUp;
FMOD_VECTOR listenerVelocity;

void Initialize();
void InitAudioSystem();
void LoadShaders();
void LoadObjects();
void InitCamera();

int main(int argc, char* argv[])
{
    Window window = Window(argc, argv);
    window.SetSize(1920, 1080);
    window.SetTitle("test");
    Initialize();
}

void InitAudioSystem()
{
    FMOD::System_Create(&audioSystem);
    audioSystem->init(512, FMOD_INIT_NORMAL, 0);

    audioSystem->createSound("Sounds/music.mp3", FMOD_3D, NULL, &sound);
    sound->set3DMinMaxDistance(0.5f, 5000.0f);
    sound->setMode(FMOD_LOOP_NORMAL);
    audioSystem->playSound(sound, 0, false, &channel);
    channel->set3DAttributes(&soundPosition, &soundVelocity);
}

void LoadShaders()
{
    mainProgram = new ShaderProgram("Shaders/vertex.glsl", "Shaders/fragment.glsl");
    mainProgram->Use();
}

void InitCamera()
{
    camera = new Camera(60.0f, 800, 600, 0.2f, 1000.0f);
    camera->UpdateProjection(mainProgram);
    camera->UpdateView(mainProgram);
}
void LoadObjects()
{
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
}

void Initialize()
{
    InitAudioSystem();
    LoadShaders();
    LoadObjects();
    InitCamera();
}

void RenderFunction(void)
{
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
        xRot += 0.1;
    if (Keyboard::KeyPressed(KEY_8))
        xRot -= 0.1;
    if (Keyboard::KeyPressed(KEY_4))
        yRot -= 0.1;
    if (Keyboard::KeyPressed(KEY_6))
        yRot += 0.1;
    if (Keyboard::KeyPressed(KEY_7))
        zRot += 0.1;
    if (Keyboard::KeyPressed(KEY_9))
        zRot -= 0.1;

    camera->SetRotation(xRot, yRot, zRot);
    camera->SetPosition(xPos, yPos, zPos);
    camera->UpdateView(mainProgram);

    sphereObject->SetPosition(cos(t) * 10.0f, 0.0f, sin(t) * 10.0f);
    cubeObject->SetPosition(0.0f, sin(t), 1.0f);

    sphereObject->Render(mainProgram);
    cubeObject->Render(mainProgram);
    monkeyObject->Render(mainProgram);

    Vector3 forward = camera->GetForwardVector();
    Vector3 up = camera->GetUpVector();
    Vector3 position = camera->GetPosition();

    listenerForward.x = forward.x;
    listenerForward.y = forward.y;
    listenerForward.z = forward.z;

    listenerUp.x = up.x;
    listenerUp.y = up.y;
    listenerUp.z = up.z;

    listenerVelocity.x = listenerPosition.x - position.x;
    listenerVelocity.y = listenerPosition.y - position.y;
    listenerVelocity.z = listenerPosition.z - position.z;

    listenerPosition.x = position.x;
    listenerPosition.y = position.y;
    listenerPosition.z = position.z;

    audioSystem->set3DListenerAttributes(0, &listenerPosition, &listenerVelocity, &listenerForward, &listenerUp);
    audioSystem->update();
}

void Cleanup(void)
{
    sound->release();
    
    audioSystem->close();
    audioSystem->release();

    delete sphereObject;
    delete cubeObject;
    delete monkeyObject;

    delete objectLoader;
}
