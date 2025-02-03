#include "Drawable.hpp"

namespace gdraw
{
	void Drawable::setTransform(Mat4 newTransform) {
		transform = newTransform;
	}
}