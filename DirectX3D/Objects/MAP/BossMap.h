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

private:
	float Height = 6.25f;
	float FallDead = -150.0f;
	Vector3 Spawnpoint_P = { -60.0f, 7.0f, 0 };
	Vector3 Spawnpoint_B = { 40.0f, 7.0f, 0 };
	//Vector3 Spawnpoint_B = { 75.0f, 30.25f, 0 };

	UINT PhaseNum = 0; 

	Model* Phase1;				// 1�� ��
	vector<Model*> Phase2;		// 2�� �� + �𼭸� + ��������
	vector<Model*> fixeds;		// ������(�������� �ʴ°�)
	vector<Model*> disappears;  // �����(1�� ���ķ� ������)

	void Fall();
	void ZeroSet();
	void NoneRender();
};

