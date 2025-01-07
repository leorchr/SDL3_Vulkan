#include "Scene01Clear.h"
#include "Renderer.h"
#include <SDL3/SDL_events.h>

void Scene01Clear::Load(Renderer& renderer) {
}
bool Scene01Clear::Update(float dt) {
	return ManageInput(inputState);
}
void Scene01Clear::Draw(Renderer& renderer) {
	renderer.Begin();
	renderer.End();
}
void Scene01Clear::Unload(Renderer& renderer) {
}