#include "Core/Application/Application.h"
#include "Core/BasicScene.h"
#include <memory>

int main() {
	std::unique_ptr<ApplicationBase> app = std::make_unique<Application>();
	app->ChangeScene(std::make_unique<BasicScene>(app.get()));
	app->Run();
	return 0;
}
