
#include "Core/Application.h"
#include "Core/BasicScene.h"

int main() {
	Application app;
	app.ChangeScene(std::make_unique<BasicScene>(&app));
	app.Run();
	return 0;
}
