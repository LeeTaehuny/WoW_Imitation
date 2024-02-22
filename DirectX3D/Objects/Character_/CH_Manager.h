#pragma once

#define CH CH_Manager::Get()
class CH_Manager : public Singleton<CH_Manager>
{
	friend class Singleton;

	enum Type
	{

	};

public:
	CH_Manager();
	~CH_Manager();

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void GUIRender();

	// 무기전사 인스턴싱 생성
	void InstancingDataArms();
	// 화염마법사 인스턴싱 생성
	void InstancingDataFire();
	// 신성사제 인스턴싱 생성
	void InstancingDataHoly();
	// 저격사냥꾼 인스턴싱 생성
	void InstancingDataMarksmanship();
	// 보호성기사 인스턴싱 생성
	void InstancingDataProtection();

	// 플레이어를 생성하기 위한 인스턴싱
	// 1 : 무기 전사
	// 2 : 보호 성기사
	// 3 : 화염 마법사
	// 4 : 저격 사냥꾼
	// 5 : 신성 사제
	void PlayerSpawn(int value);

	// NPC를 생성하기 위한 인스턴싱
	// 1 : 무기 전사
	// 2 : 보호 성기사
	// 3 : 화염 마법사
	// 4 : 저격 사냥꾼
	// 5 : 신성 사제
	void NonPlayerSpawn(int value);

	// 캐릭터의 정보를 담기 위한 겟터함수?
	CH_Base_ver2* SelectHealCharacter(IN CH_Base_ver2* collider);

	// 플레이어의 데이터를 받아오기 위한 겟터
	CH_Base_ver2* GetPlayerData() { return character[0]; }
	vector<CH_Base_ver2*> GetCharcterData() { return character; }

	// 파티원 정보 UI 반환용 함수
	class PartyUI_Bar* GetPartyUI() { return partyUI; }

private:
	ModelAnimatorInstancing* armswarrior;
	ModelAnimatorInstancing* paladin;
	ModelAnimatorInstancing* firemage;
	ModelAnimatorInstancing* marksmanshiphunter;
	ModelAnimatorInstancing* holypriest;

	vector<CH_Base_ver2*> character;

	UINT nonCount = 0;

	UINT A_count = 0;
	UINT P_count = 0;
	UINT F_count = 0;
	UINT M_count = 0;
	UINT H_count = 0;


private:
	class PartyUI_Bar* partyUI;
};