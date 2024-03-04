#pragma once

#define SKILL SkillManager::Get()

class SkillManager : public Singleton<SkillManager>
{
public:
	SkillManager();
	~SkillManager();

	void Init(CH_Base_ver2* player);
	void Update();
	void PostRender();

public:
	void SetSkillSelect(bool value) { bIsSelected = value; }
	bool GetActive();
	const vector<pair<class Slot*, bool>>& GetSlot() { return skillTreeSlots; }
	vector<class SkillBase*> GetSkills() { return skills; }

private:
	// 스킬트리 생성용 함수 5종
	void CreateA_SkillTree();
	void CreateF_SkillTree();
	void CreateH_SkillTree();
	void CreateM_SkillTree();
	void CreateP_SkillTree();

private:
	// 스킬트리 클릭 이벤트
	void LearnSkill(void* slot);

private:
	// 스킬트리 프레임
	class Slot* skillTreeFrame;
	// 스킬트리 슬롯
	vector<pair<class Slot*, bool>> skillTreeSlots;
	// 실제 스킬을 저장하기 위한 벡터 컨테이너
	vector<class SkillBase*> skills;

	// 플레이어 정보를 저장하기 위한 변수
	CH_Base_ver2* player;

	// 스킬 창 이동용 변수
	bool bIsMove = false;
	Vector3 prevPos;
	bool bIsSelected = false;

	int tempIndex = -1;
};

