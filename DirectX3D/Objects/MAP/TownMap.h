#pragma once
class TownMap : Transform
{
public:
	TownMap();
	~TownMap();

	void Init();
	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void GUIRender();

public:
	float GetHeight(Vector3 pos) { return terrain->GetHeight(pos); }
	bool isCollisionPortal() { return collider->IsCollision(CH->GetPlayerData()->GetCollider()); }

private:
	void CreateBillboard();
	void RenderBillboard();

// Objects
private:
	class Terrain* terrain;
	class Shop* shop;
	class Guild* guild;
	class Model* portal;
	class SkyBox* sky;
	class Quad* portalImage;
	class BoxCollider* collider;

// Billboard
private:
	BlendState* blendState[2];
	Material* material;
	VertexBuffer* vertexBuffer;
	GeometryShader* geometryShader;
	DepthStencilState* depthState[2];
	vector<VertexUV> vertices;
};

