#ifndef SCENE03TRIANGLEVERTEXBUFFER_H
#define SCENE03TRIANGLEVERTEXBUFFER_H

#include <SDL3/SDL_gpu.h>
#include "Scene.h"

class Scene03TriangleVertexBuffer : public Scene {
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
	SDL_GPUGraphicsPipeline* pipeline;
	SDL_GPUBuffer* vertexBuffer;
};

#endif