#pragma once
class BossMap : public Transform
{
public:
	BossMap();
	~BossMap();

	void Update();
	void Render();
	
	UINT SetPhase(UINT Num) { return PhaseNum = Num; }


private:
	UINT PhaseNum = 0; 

	Model* Phase1;				// 1�� ��
	vector<Model*> Phase2;		// 2�� �� + �𼭸� + ��������
	vector<Model*> fixeds;		// ������(�������� �ʴ°�)
	vector<Model*> disappears;  // �����(1�� ���ķ� ������)
};

