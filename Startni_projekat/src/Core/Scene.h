#ifndef SCENE_H
#define SCENE_H

class Application;

class Scene {
protected:
    Application* app;

public:
    Scene(Application* app) : app(app) {}

    virtual ~Scene() = default;
    virtual void Start() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

    virtual void OnScroll(double xoffset, double yoffset) {};
};

#endif // SCENE_H