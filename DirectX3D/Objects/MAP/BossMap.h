#pragma once
class BossMap : public Transform
{
public:
	BossMap();
	~BossMap();

	void Update();
	void Render();
	
	UINT SetPhase(UINT Num) { return PhaseNum = Num; }
	float GetHeight() { return Height; }
	float GetFallDead() { return FallDead; }
	Vector3 GetSpawnpoint_P() { return Spawnpoint_P; }
	Vector3 GetSpawnpoint_B() { return Spawnpoint_B; }
	bool IsCollision(Collider* c);

private:
	float Height = 4.25f;
	float FallDead = -150.0f;
	Vector3 Spawnpoint_P = { -60.0f, 4.25f, 0 };
	Vector3 Spawnpoint_B = { 40.0f, 4.25f, 0 };
	//Vector3 Spawnpoint_B = { 75.0f, 30.25f, 0 };

	UINT PhaseNum = 0; 

	SkyBox* skybox;

	Model* Phase1;				// 1페 땅
	vector<Model*> Phase2;		// 2페 땅 + 모서리 + 얼음파편
	vector<Model*> fixeds;		// 고정된(없어지지 않는것)
	vector<Model*> disappears;  // 사라짐(1페 이후로 없어짐)

	Cylinder* GroundColider1;
	Cylinder* GroundColider2;
	vector<Cylinder*> disappears_C;
	BoxCollider* StairCollider;
	BoxCollider* Chair_Ground;
	BoxCollider* Chair;

	void Fall();
	void ZeroSet();
	void NoneRender();
};

