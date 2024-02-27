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
	void Loding();

private:
	class TownMap* townMap;
	// 로딩 화면
	class Quad* loding;
	// 로딩을 위한 판별용 변수
	bool isReady;
};

