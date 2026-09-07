#ifndef BASIC_SCENE_H
#define BASIC_SCENE_H

#include "Scene.h"
#include "shaderClass.h"
#include "Camera/Camera.h"
#include "Application.h"
#include "ErrorHandler.h"

class BasicScene : public Scene
{
private:
    Shader shader;
    Camera camera;
    float fov = 45.0f;

    virtual void OnScroll(double xoffset, double yoffset) override;

public:
    BasicScene(Application* app);

    virtual void Start() override;
    virtual void Update(float dt) override;
    virtual void Render() override;
};

#endif // !BASIC_SCENE_H
