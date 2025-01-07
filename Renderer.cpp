#include "Renderer.h"
#include "Window.h"
#include "SDL3/SDL_log.h"
#include <SDL3/SDL_assert.h>

void Renderer::Init(Window& window) {
	renderWindow = window.sdlWindow;
	device = SDL_CreateGPUDevice(
		SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL,
		true,
		nullptr);
	SDL_ClaimWindowForGPUDevice(device, renderWindow);
}

void Renderer::Close() const {
	SDL_ReleaseWindowFromGPUDevice(device, renderWindow);
	SDL_DestroyGPUDevice(device);
}

void Renderer::Begin(SDL_GPUDepthStencilTargetInfo* depthStencilTargetInfo) {
	cmdBuffer = SDL_AcquireGPUCommandBuffer(device);
	if (cmdBuffer == nullptr) {
		SDL_Log("AcquireGPUCommandBuffer failed: %s", SDL_GetError());
	}
	SDL_GPUTexture* swapchainTexture;

	if (!SDL_AcquireGPUSwapchainTexture(cmdBuffer, renderWindow, &swapchainTexture,
		nullptr, nullptr)) {
		SDL_Log("AcquireGPUSwapchainTexture failed: %s", SDL_GetError());
	}
	if (swapchainTexture != nullptr) {
		SDL_GPUColorTargetInfo colorTargetInfo = {};
		colorTargetInfo.texture = swapchainTexture;
		colorTargetInfo.clear_color = SDL_FColor{ 0.392f, 0.584f, 0.929f, 1.0f };
		colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
		colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;
		renderPass = SDL_BeginGPURenderPass(cmdBuffer, &colorTargetInfo, 1,
			depthStencilTargetInfo);
	}
}

void Renderer::End() const {
	SDL_EndGPURenderPass(renderPass);
	SDL_SubmitGPUCommandBuffer(cmdBuffer);
}

SDL_GPUShader* Renderer::LoadShader(
	const char* basePath,
	const char* shaderFilename,
	Uint32 samplerCount,
	Uint32 uniformBufferCount,
	Uint32 storageBufferCount,
	Uint32 storageTextureCount
) {
	// Auto-detect the shader stage from the file name for convenience
	SDL_GPUShaderStage stage;
	if (SDL_strstr(shaderFilename, ".vert")) {
		stage = SDL_GPU_SHADERSTAGE_VERTEX;
	}
	else if (SDL_strstr(shaderFilename, ".frag")) {
		stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
	}
	else {
		SDL_Log("Invalid shader stage!");
		return nullptr;
	}
	char fullPath[256];
	SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(device);
	SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
	const char* entrypoint;
	if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV) {
		SDL_snprintf(fullPath, sizeof(fullPath),
			"%sContent/Shaders/Compiled/SPIRV/%s.spv", basePath, shaderFilename);
		format = SDL_GPU_SHADERFORMAT_SPIRV;
		entrypoint = "main";
	}
	else if (backendFormats & SDL_GPU_SHADERFORMAT_MSL) {
		SDL_snprintf(fullPath, sizeof(fullPath), "%sContent/Shaders/Compiled/MSL/%s.msl",
			basePath, shaderFilename);
		format = SDL_GPU_SHADERFORMAT_MSL;
		entrypoint = "main0";
	}
	else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL) {
		SDL_snprintf(fullPath, sizeof(fullPath),
			"%sContent/Shaders/Compiled/DXIL/%s.dxil", basePath, shaderFilename);
		format = SDL_GPU_SHADERFORMAT_DXIL;
		entrypoint = "main";
	}
	else {
		SDL_Log("%s", "Unrecognized backend shader format!");
		return nullptr;
	}
	size_t codeSize;
	void* code = SDL_LoadFile(fullPath, &codeSize);
	if (code == nullptr) {
		SDL_Log("Failed to load shader from disk! %s", fullPath);

		return nullptr;
	}
	SDL_GPUShaderCreateInfo shaderInfo = {
	.code_size = codeSize,
	.code = static_cast<Uint8*>(code),
	.entrypoint = entrypoint,
	.format = format,
	.stage = stage,
	.num_samplers = samplerCount,
	.num_storage_textures = storageTextureCount,
	.num_storage_buffers = storageBufferCount,
	.num_uniform_buffers = uniformBufferCount
	};
	SDL_GPUShader* shader = SDL_CreateGPUShader(device, &shaderInfo);
	if (shader == nullptr) {
		SDL_Log("Failed to create shader!");
		SDL_free(code);
		return nullptr;
	}
	SDL_free(code);
	return shader;
}

void Renderer::ReleaseShader(SDL_GPUShader* shader) const {
	SDL_ReleaseGPUShader(device, shader);
}

SDL_GPUGraphicsPipeline* Renderer::CreateGPUGraphicsPipeline(const
	SDL_GPUGraphicsPipelineCreateInfo& createInfo) const {
	return SDL_CreateGPUGraphicsPipeline(device, &createInfo);
}

void Renderer::BindGraphicsPipeline(SDL_GPUGraphicsPipeline* pipeline) const {
	SDL_BindGPUGraphicsPipeline(renderPass, pipeline);
}
void Renderer::DrawPrimitives(int numVertices, int numInstances, int firstVertex, int
	firstInstance) const {
	SDL_DrawGPUPrimitives(renderPass, numVertices, numInstances, firstVertex,
		firstInstance);
}
void Renderer::SetViewport(const SDL_GPUViewport& viewport) const {
	SDL_SetGPUViewport(renderPass, &viewport);
}
void Renderer::SetScissorRect(const SDL_Rect& rect) const {
	SDL_SetGPUScissor(renderPass, &rect);
}

void Renderer::ReleaseGraphicsPipeline(SDL_GPUGraphicsPipeline* pipeline) const {
	SDL_ReleaseGPUGraphicsPipeline(device, pipeline);
}

SDL_GPUBuffer* Renderer::CreateBuffer(const SDL_GPUBufferCreateInfo& createInfo) const {
	return SDL_CreateGPUBuffer(device, &createInfo);
}
SDL_GPUTransferBuffer* Renderer::CreateTransferBuffer(const
	SDL_GPUTransferBufferCreateInfo& createInfo) const {
	return SDL_CreateGPUTransferBuffer(device, &createInfo);
}
void* Renderer::MapTransferBuffer(SDL_GPUTransferBuffer* transferBuffer, bool cycle) const
{
	return SDL_MapGPUTransferBuffer(device, transferBuffer, cycle);
}
void Renderer::UnmapTransferBuffer(SDL_GPUTransferBuffer* transferBuffer) const {
	SDL_UnmapGPUTransferBuffer(device, transferBuffer);
}
void Renderer::ReleaseTransferBuffer(SDL_GPUTransferBuffer* transferBuffer) const {
	SDL_ReleaseGPUTransferBuffer(device, transferBuffer);
}
void Renderer::BeginUploadToBuffer() {
	uploadCmdBuf = SDL_AcquireGPUCommandBuffer(device);
	copyPass = SDL_BeginGPUCopyPass(uploadCmdBuf);
}
void Renderer::UploadToBuffer(const SDL_GPUTransferBufferLocation& source,
	const SDL_GPUBufferRegion& destination,
	bool cycle) const {

	SDL_UploadToGPUBuffer(copyPass, &source, &destination, cycle);
}
void Renderer::EndUploadToBuffer(SDL_GPUTransferBuffer* transferBuffer) const {
	SDL_EndGPUCopyPass(copyPass);
	SDL_SubmitGPUCommandBuffer(uploadCmdBuf);
	SDL_ReleaseGPUTransferBuffer(device, transferBuffer);
}

void Renderer::ReleaseBuffer(SDL_GPUBuffer* buffer) const {
	SDL_ReleaseGPUBuffer(device, buffer);
}

void Renderer::BindVertexBuffers(Uint32 firstSlot, const SDL_GPUBufferBinding& bindings,
	Uint32 numBindings) const {
	SDL_BindGPUVertexBuffers(renderPass, firstSlot, &bindings, numBindings);
}

void Renderer::BindIndexBuffer(const SDL_GPUBufferBinding& bindings,
	SDL_GPUIndexElementSize indexElementSize) const {
	SDL_BindGPUIndexBuffer(renderPass, &bindings, indexElementSize);
}
void Renderer::DrawIndexedPrimitives(int numIndices, int numInstances, int firstIndex,
	int vertexOffset, int firstInstance) const {
	SDL_DrawGPUIndexedPrimitives(renderPass, numIndices, numInstances, firstIndex,
		vertexOffset, firstInstance);
}

SDL_Surface* Renderer::LoadBMPImage(const char* basePath, const char* imageFilename, int
	desiredChannels) {
	char fullPath[256];
	SDL_PixelFormat format;
	SDL_snprintf(fullPath, sizeof(fullPath), "%sContent/Images/%s", basePath,
		imageFilename);
	SDL_Surface* result = SDL_LoadBMP(fullPath);
	if (result == nullptr) {
		SDL_Log("Failed to load BMP: %s", SDL_GetError());
		return nullptr;
	}
	if (desiredChannels == 4) {
		format = SDL_PIXELFORMAT_ABGR8888;
	}
	else {
		SDL_assert(!"Unexpected desiredChannels");
		SDL_DestroySurface(result);
		return nullptr;
	}
	if (result->format != format) {
		SDL_Surface* next = SDL_ConvertSurface(result, format);
		SDL_DestroySurface(result);
		result = next;
	}
	return result;
}

SDL_GPUSampler* Renderer::CreateSampler(const SDL_GPUSamplerCreateInfo& createInfo) const
{
	return SDL_CreateGPUSampler(device, &createInfo);
}

void Renderer::ReleaseSurface(SDL_Surface* surface) const {
	SDL_DestroySurface(surface);
}
void Renderer::SetBufferName(SDL_GPUBuffer* buffer, const string& name) const {
	SDL_SetGPUBufferName(device, buffer, name.c_str());
}
SDL_GPUTexture* Renderer::CreateTexture(const SDL_GPUTextureCreateInfo& createInfo) const
{
	return SDL_CreateGPUTexture(device, &createInfo);
}

void Renderer::SetTextureName(SDL_GPUTexture* texture, const string& name) const {
	SDL_SetGPUTextureName(device, texture, name.c_str());
}

void Renderer::ReleaseTexture(SDL_GPUTexture* texture) const {
	SDL_ReleaseGPUTexture(device, texture);
}

void Renderer::ReleaseSampler(SDL_GPUSampler* sampler) const {
	SDL_ReleaseGPUSampler(device, sampler);
}

void Renderer::UploadToTexture(const SDL_GPUTextureTransferInfo& source, const
	SDL_GPUTextureRegion& destination,
	bool cycle) const {
	SDL_UploadToGPUTexture(copyPass, &source, &destination, cycle);
}

void Renderer::BindFragmentSamplers(Uint32 firstSlot, const SDL_GPUTextureSamplerBinding&
	bindings,
	Uint32 numBindings) const {
	SDL_BindGPUFragmentSamplers(renderPass, firstSlot, &bindings, numBindings);
}

void Renderer::PushVertexUniformData(uint32_t slot, const void* data, Uint32 size) const {
	SDL_PushGPUVertexUniformData(cmdBuffer, 0, data, size);
}

void Renderer::PushFragmentUniformData(uint32_t slot, const void* data, Uint32 size) const
{
	SDL_PushGPUFragmentUniformData(cmdBuffer, 0, data, size);
}