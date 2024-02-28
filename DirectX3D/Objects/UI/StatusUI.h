#pragma once

class StatusUI : public Transform
{
public:
	StatusUI(class CH_Base_ver2* player);
	~StatusUI();

	void Update();
	void UIRender();

private:
	// 플레이어와 상호작용하기 위한 함수
	void InteractWithPlayer();
	// 스탯을 렌더링하기 위한 함수
	void RenderStat();

// Member Variable
private:
	// 무기 정보를 저장하기 위한 변수
	class Item* weapon;

	class Item* tempItem;
	int tempIndex;

	// UI
	class Slot* statusFrame;
	class Slot* weaponSlot;

	// 스탯 창 이동용 변수
	bool bIsMove = false;
	Vector3 prevPos;

	// 플레이어 정보를 저장하기 위한 변수
	class CH_Base_ver2* player;
};

