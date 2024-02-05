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

	Model* Phase1;				// 1페 땅
	vector<Model*> Phase2;		// 2페 땅 + 모서리 + 얼음파편
	vector<Model*> fixeds;		// 고정된(없어지지 않는것)
	vector<Model*> disappears;  // 사라짐(1페 이후로 없어짐)
};

