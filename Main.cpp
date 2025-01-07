#include <iostream>
#include <SDL3/SDL_main.h>
#include "Renderer.h"
#include "Scene08TextureQuadMoving.h"
#include "Time.h"
#include "Window.h"

using namespace std;
int main(int argc, char** argv) {
	Window window{};
	Renderer renderer{};
	Time time{};
	window.Init();
	renderer.Init(window);
	auto scene = std::make_unique<Scene08TextureQuadMoving>();
	scene->Load(renderer);
	bool isRunning{ true };
	while (isRunning) {
		const float dt = time.ComputeDeltaTime();
		isRunning = scene->Update(dt);
		scene->Draw(renderer);
		time.DelayTime();
	}
	scene->Unload(renderer);
	renderer.Close();
	window.Close();
	return 0;
}