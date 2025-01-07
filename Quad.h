#include "Mat4.h"

typedef struct FragMultiplyUniform
{
	float r, g, b, a;
} fragMultiplyUniform;

class Quad {
public:
	Quad(float posX, float posY, float posZ);
	void Update(float dt);
	void Draw(class Renderer& renderer);
	const Mat4 getMatrixUniform() const { return matrixUniform; }

private:
	FragMultiplyUniform fragMultiplyUniform;
	Mat4 matrixUniform;
	float x, y, z;
	float rotZ{ 0 };
	float time{ 0 };
};