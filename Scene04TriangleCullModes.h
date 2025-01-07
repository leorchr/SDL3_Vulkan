#ifndef SCENE04TRIANGLECULLMODES_H
#define SCENE04TRIANGLECULLMODES_H

#include <SDL3/SDL_gpu.h>
#include "Scene.h"
#include <array>
#include <string>
using std::array;
using std::string;

class Scene04TriangleCullModes : public Scene {

public:

	void Load(Renderer& renderer) override;
	bool Update(float dt) override;
	void Draw(Renderer& renderer) override;
	void Unload(Renderer& renderer) override;

private:

	InputState inputState;
	const char* basePath;
	SDL_GPUShader* vertexShader;
	SDL_GPUShader* fragmentShader;
	SDL_GPUBuffer* vertexBufferCW;
	SDL_GPUBuffer* vertexBufferCCW;
	int currentMode{ 0 };
	array<string, 6> modeNames{
	"CW_CullNone",
	"CW_CullFront",
	"CW_CullBack",
	"CCW_CullNone",

	"CCW_CullFront",
	"CCW_CullBack"
	};
	array<SDL_GPUGraphicsPipeline*, 6> pipelines;
};

#endif //SCENE04TRIANGLECULLMODES_H