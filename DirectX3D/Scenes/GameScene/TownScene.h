#pragma once
#include "Scenes/Scene.h"

class TownScene : public Scene
{
public:
	TownScene();
	virtual ~TownScene() override;

	virtual void Start() override;
	virtual void Update() override;

	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	class TownMap* townMap;
};

