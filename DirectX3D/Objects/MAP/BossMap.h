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
	Vector3 GetSpawnpoint_BC() { return Spawnpoint_BC; }
	float GetStartBossRot() { return StartBossRotY; }
	bool IsCollision(Collider* c);

private:
	float Height = 4.25f;
	float FallDead = -150.0f;
	Vector3 Spawnpoint_P = { -60.0f, 0, 0 };
	Vector3 Spawnpoint_B = { 40.0f, 0, 0 };
	Vector3 Spawnpoint_BC = { 77.0f, 24.5f, -1.0f };
	float StartBossRotY = 3.15f;

	UINT PhaseNum = 0; 

	SkyBox* skybox;
	//BlendState* blendState[2];

	Model* Phase1;				// 1�� ��
	vector<Model*> Phase2;		// 2�� �� + �𼭸� + ��������
	vector<Model*> fixeds;		// ������(�������� �ʴ°�)
	vector<Model*> disappears;  // �����(1�� ���ķ� ������)

	Cylinder* GroundColider1;
	Cylinder* GroundColider2;
	vector<Cylinder*> disappears_C;
	BoxCollider* StairCollider;
	BoxCollider* Chair_Ground;
	BoxCollider* Chair;
	vector<BoxCollider*> StairGuard;

	void Fall();
	void ZeroSet();
	void NoneRender();
};

