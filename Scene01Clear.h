#ifndef SCENE01CLEAR_H
#define SCENE01CLEAR_H
#include "Scene.h"

class Scene01Clear : public Scene {
public:
	void Load(Renderer& renderer) override;
	bool Update(float dt) override;
	void Draw(Renderer& renderer) override;
	void Unload(Renderer& renderer) override;
private:
	InputState inputState;
};

#endif