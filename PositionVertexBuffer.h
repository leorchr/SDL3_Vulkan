#ifndef GRAPHICS_SDL3_POSITIONCOLORVERTEX_H
#define GRAPHICS_SDL3_POSITIONCOLORVERTEX_H
#include <SDL3/SDL_stdinc.h>

struct PositionColorVertex
{
	float x, y, z;
	Uint8 r, g, b, a;
};

struct PositionTextureVertex {
	float x, y, z;
	float u, v;
};

#endif