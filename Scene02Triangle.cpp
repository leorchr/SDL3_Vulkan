#include "Scene02Triangle.h"
#include "SDL3/SDL_log.h"
#include "Renderer.h"
#include <SDL3/SDL_filesystem.h>

void Scene02Triangle::Load(Renderer& renderer) {
	basePath = SDL_GetBasePath();
	vertexShader = renderer.LoadShader(basePath, "RawTriangle.vert", 0, 0, 0, 0);
	fragmentShader = renderer.LoadShader(basePath, "SolidColor.frag", 0, 0, 0, 0);
	// Create the pipelines
	SDL_GPUGraphicsPipelineCreateInfo pipelineCreateInfo = {
	.vertex_shader = vertexShader,
	.fragment_shader = fragmentShader,
	.primitive_type = SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
	.target_info = {
	.color_target_descriptions = new SDL_GPUColorTargetDescription[1] {{
	.format = SDL_GetGPUSwapchainTextureFormat(renderer.device,

	renderer.renderWindow)
	}},
	.num_color_targets = 1,
	},
	};
	pipelineCreateInfo.rasterizer_state.fill_mode = SDL_GPU_FILLMODE_FILL;
	fillPipeline = renderer.CreateGPUGraphicsPipeline(pipelineCreateInfo);
	if (fillPipeline == nullptr)
	{
		SDL_Log("Failed to create fill pipeline!");
	}

	pipelineCreateInfo.rasterizer_state.fill_mode = SDL_GPU_FILLMODE_LINE;
	linePipeline = renderer.CreateGPUGraphicsPipeline(pipelineCreateInfo);
	if (linePipeline == nullptr)
	{
		SDL_Log("Failed to create line pipeline!");
	}
	// Clean up shader resources
	renderer.ReleaseShader(vertexShader);
	renderer.ReleaseShader(fragmentShader);
	// Finally, print instructions!
	SDL_Log("Press Left to toggle wireframe mode");
	SDL_Log("Press Down to toggle small viewport");
	SDL_Log("Press Right to toggle scissor rect");
}

bool Scene02Triangle::Update(float dt) {
	const bool isRunning = ManageInput(inputState);
	if (inputState.IsPressed(DirectionalKey::Left)) {
		useWireframeMode = !useWireframeMode;
	}
	if (inputState.IsPressed(DirectionalKey::Up)) {
		useSmallViewport = !useSmallViewport;
	}
	if (inputState.IsPressed(DirectionalKey::Right)) {
		useScissorRect = !useScissorRect;
	}
	return isRunning;
}

void Scene02Triangle::Draw(Renderer& renderer) {
	renderer.Begin();
	renderer.BindGraphicsPipeline(useWireframeMode ? linePipeline : fillPipeline);
	if (useSmallViewport) {
		renderer.SetViewport(smallViewport);
	}
	if (useScissorRect) {
		renderer.SetScissorRect(scissorRect);
	}
	renderer.DrawPrimitives(3, 1, 0, 0);

	renderer.End();
}

void Scene02Triangle::Unload(Renderer& renderer) {
	renderer.ReleaseGraphicsPipeline(fillPipeline);
	renderer.ReleaseGraphicsPipeline(linePipeline);
}