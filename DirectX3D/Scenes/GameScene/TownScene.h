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
	void CreateBillboard();
	void RenderBillboard();

// Objects
private:
	class Terrain* terrain;
	class Shop* shop;

	int tempPos;

// Billboard
private:
	BlendState* blendState[2];
	Material* material;
	VertexBuffer* vertexBuffer;
	GeometryShader* geometryShader;
	DepthStencilState* depthState[2];
	vector<VertexUV> vertices;
};

