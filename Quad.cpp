#include "Quad.h"
#include "Mat4.h"
#include "Renderer.h"

Quad::Quad(float posX, float posY, float posZ) : x(posX), y(posY), z(posZ) {}

void Quad::Update(float dt)
{
	time += dt;
	matrixUniform =
		Mat4::CreateRotationZ(time) *
		Mat4::CreateRotationY(time) *
		Mat4::CreateRotationX(time) *
		Mat4::CreateTranslation(0, 0, 0);

	fragMultiplyUniform.r = 1.0f;
	fragMultiplyUniform.g = 0.5f + SDL_sinf(time) * 0.5f;
	fragMultiplyUniform.b = 1.0f;
	fragMultiplyUniform.a = 1.0f;
}

void Quad::Draw(Renderer& renderer)
{
	renderer.PushVertexUniformData(0, &matrixUniform, sizeof(matrixUniform));

	renderer.PushFragmentUniformData(0, &fragMultiplyUniform,
		sizeof(FragMultiplyUniform));
	renderer.DrawIndexedPrimitives(36, 1, 0, 0, 0);
}