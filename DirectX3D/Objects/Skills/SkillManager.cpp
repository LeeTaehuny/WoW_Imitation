#include "Framework.h"
#include "SkillManager.h"
#include "SkillHeader.h"
#include "Objects/Inventory/Slot.h"

SkillManager::SkillManager()
{
}

SkillManager::~SkillManager()
{
}

void SkillManager::Init(CH_Base_ver2* player)
{
	if (player == nullptr) return;

	// 플레이어 정보 저장
	this->player = player;

	// 프레임 생성
	skillTreeFrame = new Slot(L"Textures/UI/skillTreeBase.png", SlotType::SkillTree_Frame);
	skillTreeFrame->Scale() *= 1.5f;
	skillTreeFrame->Pos() = { CENTER_X / 2.0f + 40.0f, CENTER_Y - 40.0f, 1.0f };


	// 슬롯 생성
	skillTreeSlots.reserve(10);

	for (int i = 0; i < 10; i++)
	{
		Slot* slot = new Slot(Vector2(33.0f, 33.0f), SlotType::SkillTree_Slot);
		slot->SetParent(skillTreeFrame);
		slot->GetMaterial()->SetShader(L"Basic/Slot.hlsl");
		slot->UseColorBuffer();
		
		skillTreeSlots.push_back({ slot, false });
	}

	// 직군에 따른 스킬트리 생성
	switch (player->GetProfessionType())
	{
	case ProfessionType::ArmsWarrior:
		CreateA_SkillTree();
		break;

	case ProfessionType::FireMage:
		CreateF_SkillTree();
		break;

	case ProfessionType::HolyPriest:
		CreateH_SkillTree();
		break;

	case ProfessionType::MarksmanshipHunter:
		CreateM_SkillTree();
		break;

	case ProfessionType::ProtectionWarrior:
		CreateP_SkillTree();
		break;

	default:
		break;
	}

	// 이벤트 등록
	{
		// 스킬 배우기
		Observer::Get()->AddParamEvent("LearnSkill", bind(&SkillManager::LearnSkill, this, placeholders::_1));

		// 스킬 창 이동
		//Observer::Get()->AddEvent("MoveSkillFrame", bind(&SkillManager::MoveSkillFrame, this));
		//Observer::Get()->AddEvent("StopSkillFrame", bind(&SkillManager::StopSkillFrame, this));
	}

	skillTreeFrame->SetActive(false);
}

void SkillManager::Update()
{
	if (KEY_DOWN('K'))
	{
		if (skillTreeFrame->Active())
		{
			skillTreeFrame->SetActive(false);
		}
		else
		{
			skillTreeFrame->SetActive(true);
		}
	}

	if (KEY_DOWN(VK_ESCAPE) && skillTreeFrame->Active())
	{
		skillTreeFrame->SetActive(false);
	}

	if (!skillTreeFrame->Active()) return;

	if (KEY_UP(VK_LBUTTON))
	{

		if (tempIndex != -1)
		{
			skillTreeSlots[tempIndex].first->SetSelect(false);
			skillTreeSlots[tempIndex].first->SetCilck(false);
		}

		for (pair<Slot*, bool> slot : skillTreeSlots)
		{
			if (mousePos.x > slot.first->GlobalPos().x + 33.0f || mousePos.x < slot.first->GlobalPos().x - 33.0f &&
				mousePos.y > slot.first->GlobalPos().y + 33.0f || mousePos.y < slot.first->GlobalPos().y - 33.0f)
			{
				tempIndex = -1;
			}
		}
	}


	skillTreeFrame->Update();

	for (pair<Slot*, bool> slot : skillTreeSlots)
	{
		slot.first->Update();
	}
}

void SkillManager::PostRender()
{
	if (!skillTreeFrame->Active()) return;

	skillTreeFrame->Render();

	for (pair<Slot*, bool> slot : skillTreeSlots)
	{
		slot.first->Render();
	}
}

bool SkillManager::GetActive()
{
	return skillTreeFrame->Active();
}

void SkillManager::CreateA_SkillTree()
{
	// 프레임 이미지 설정
	skillTreeFrame->GetMaterial()->SetDiffuseMap(L"Textures/UI/A_skillTree.png");

	// 스킬 생성
	{
		SkillBase* skill = new A_001_MortalStrike();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new A_002_Overpower();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new A_003_MartialProwess();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new A_004_DiebytheSword();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new A_005_SharpenedBlades();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new A_006_FueledbyViolence();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new A_007_ColossusSmash();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new A_008_Massacre();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new A_009_BluntInstruments();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new A_010_Bladestorm();
		skill->SetOwner(player);
		skills.push_back(skill);
	}

	// 슬롯 위치 지정 & 이미지 지정
	{
		skillTreeSlots[0].first->Pos() = Vector3(2, 78, 0);
		skillTreeSlots[0].first->GetMaterial()->SetDiffuseMap(skills[0]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[0].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[1].first->Pos() = Vector3(2, 36, 0);
		skillTreeSlots[1].first->GetMaterial()->SetDiffuseMap(skills[1]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[1].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[2].first->Pos() = Vector3(-60, -6, 0);
		skillTreeSlots[2].first->GetMaterial()->SetDiffuseMap(skills[2]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[2].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[3].first->Pos() = Vector3(62, -6, 0);
		skillTreeSlots[3].first->GetMaterial()->SetDiffuseMap(skills[3]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[3].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[4].first->Pos() = Vector3(-120, -48, 0);
		skillTreeSlots[4].first->GetMaterial()->SetDiffuseMap(skills[4]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[4].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[5].first->Pos() = Vector3(2, -46, 0);
		skillTreeSlots[5].first->GetMaterial()->SetDiffuseMap(skills[5]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[5].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[6].first->Pos() = Vector3(-60, -94, 0);
		skillTreeSlots[6].first->GetMaterial()->SetDiffuseMap(skills[6]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[6].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[7].first->Pos() = Vector3(62, -94, 0);
		skillTreeSlots[7].first->GetMaterial()->SetDiffuseMap(skills[7]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[7].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[8].first->Pos() = Vector3(-60, -138, 0);
		skillTreeSlots[8].first->GetMaterial()->SetDiffuseMap(skills[8]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[8].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[9].first->Pos() = Vector3(62, -138, 0);
		skillTreeSlots[9].first->GetMaterial()->SetDiffuseMap(skills[9]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[9].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };
	}
}

void SkillManager::CreateF_SkillTree()
{
	// 프레임 이미지 설정
	skillTreeFrame->GetMaterial()->SetDiffuseMap(L"Textures/UI/F_skillTree.png");

	// 스킬 생성
	{
		SkillBase* skill = new F_001_Pyroblast();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new F_002_FireBlast();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new F_003_Pyrotechnics();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new F_004_Scorch();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new F_005_PhoenixFlame();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new F_006_SurgingBlaze();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new F_007_SearingTouch();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new F_008_FlameOn();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new F_009_Combustion();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new F_010_Meteor();
		skill->SetOwner(player);
		skills.push_back(skill);
	}

	// 슬롯 위치 지정 & 이미지 지정
	{
		skillTreeSlots[0].first->Pos() = Vector3(2, 68, 0);
		skillTreeSlots[0].first->GetMaterial()->SetDiffuseMap(skills[0]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[0].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[1].first->Pos() = Vector3(-60, 15, 0);
		skillTreeSlots[1].first->GetMaterial()->SetDiffuseMap(skills[1]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[1].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[2].first->Pos() = Vector3(65, 15, 0);
		skillTreeSlots[2].first->GetMaterial()->SetDiffuseMap(skills[2]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[2].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[3].first->Pos() = Vector3(-117, -38, 0);
		skillTreeSlots[3].first->GetMaterial()->SetDiffuseMap(skills[3]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[3].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[4].first->Pos() = Vector3(2, -38, 0);
		skillTreeSlots[4].first->GetMaterial()->SetDiffuseMap(skills[4]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[4].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[5].first->Pos() = Vector3(123, -38, 0);
		skillTreeSlots[5].first->GetMaterial()->SetDiffuseMap(skills[5]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[5].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[6].first->Pos() = Vector3(-117, -90, 0);
		skillTreeSlots[6].first->GetMaterial()->SetDiffuseMap(skills[6]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[6].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[7].first->Pos() = Vector3(123, -90, 0);
		skillTreeSlots[7].first->GetMaterial()->SetDiffuseMap(skills[7]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[7].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[8].first->Pos() = Vector3(57, -140, 0);
		skillTreeSlots[8].first->GetMaterial()->SetDiffuseMap(skills[8]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[8].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[9].first->Pos() = Vector3(123, -140, 0);
		skillTreeSlots[9].first->GetMaterial()->SetDiffuseMap(skills[9]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[9].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };
	}
}

void SkillManager::CreateH_SkillTree()
{
	// 프레임 이미지 설정
	skillTreeFrame->GetMaterial()->SetDiffuseMap(L"Textures/UI/H_skillTree.png");

	// 스킬 생성
	{
		SkillBase* skill = new H_001_Holy_Word_Serenity();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new H_002_Holy_Word_Sanctify();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new H_003_Guardian_Spirit();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new H_004_Holy_Word_Chastise();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new H_005_Censure();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new H_006_Circle_Of_Healing();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new H_007_Cosmic_Ripple();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new H_008_Divine_Hymn();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new H_009_Enlightenment();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new H_010_Everlasting_Light();
		skill->SetOwner(player);
		skills.push_back(skill);
	}

	// 슬롯 위치 지정 & 이미지 지정
	{
		skillTreeSlots[0].first->Pos() = Vector3(2, 67, 0);
		skillTreeSlots[0].first->GetMaterial()->SetDiffuseMap(skills[0]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[0].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[1].first->Pos() = Vector3(-68, 16, 0);
		skillTreeSlots[1].first->GetMaterial()->SetDiffuseMap(skills[1]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[1].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[2].first->Pos() = Vector3(2, 16, 0);
		skillTreeSlots[2].first->GetMaterial()->SetDiffuseMap(skills[2]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[2].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[3].first->Pos() = Vector3(70, 16, 0);
		skillTreeSlots[3].first->GetMaterial()->SetDiffuseMap(skills[3]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[3].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[4].first->Pos() = Vector3(70, -34, 0);
		skillTreeSlots[4].first->GetMaterial()->SetDiffuseMap(skills[4]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[4].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[5].first->Pos() = Vector3(-115, -35, 0);
		skillTreeSlots[5].first->GetMaterial()->SetDiffuseMap(skills[5]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[5].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[6].first->Pos() = Vector3(-68, -35, 0);
		skillTreeSlots[6].first->GetMaterial()->SetDiffuseMap(skills[6]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[6].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[7].first->Pos() = Vector3(2, -84, 0);
		skillTreeSlots[7].first->GetMaterial()->SetDiffuseMap(skills[7]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[7].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[8].first->Pos() = Vector3(70, -84, 0);
		skillTreeSlots[8].first->GetMaterial()->SetDiffuseMap(skills[8]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[8].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[9].first->Pos() = Vector3(-69, -134, 0);
		skillTreeSlots[9].first->GetMaterial()->SetDiffuseMap(skills[9]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[9].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };
	}
}

void SkillManager::CreateM_SkillTree()
{
	// 프레임 이미지 설정
	skillTreeFrame->GetMaterial()->SetDiffuseMap(L"Textures/UI/M_skillTree.png");

	// 스킬 생성
	{
		SkillBase* skill = new M_001_Aimed_Shot();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new M_002_Crack_Shot();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new M_003_Rapid_Fire();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new M_004_Lone_Wolf();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new M_005_Chimaera_Shot();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new M_006_Streamline();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new M_007_Focused_Aim();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new M_008_Multi_Shot();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new M_009_Volley();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new M_010_Wailing_Arrow();
		skill->SetOwner(player);
		skills.push_back(skill);
	}

	// 슬롯 위치 지정 & 이미지 지정
	{
		skillTreeSlots[0].first->Pos() = Vector3(2, 77, 0);
		skillTreeSlots[0].first->GetMaterial()->SetDiffuseMap(skills[0]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[0].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[1].first->Pos() = Vector3(-69, 31, 0);
		skillTreeSlots[1].first->GetMaterial()->SetDiffuseMap(skills[1]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[1].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[2].first->Pos() = Vector3(-69, -15, 0);
		skillTreeSlots[2].first->GetMaterial()->SetDiffuseMap(skills[2]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[2].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[3].first->Pos() = Vector3(2, 31, 0);
		skillTreeSlots[3].first->GetMaterial()->SetDiffuseMap(skills[3]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[3].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[4].first->Pos() = Vector3(76, 31, 0);
		skillTreeSlots[4].first->GetMaterial()->SetDiffuseMap(skills[4]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[4].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[5].first->Pos() = Vector3(-69, -59, 0);
		skillTreeSlots[5].first->GetMaterial()->SetDiffuseMap(skills[5]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[5].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[6].first->Pos() = Vector3(76, -15, 0);
		skillTreeSlots[6].first->GetMaterial()->SetDiffuseMap(skills[6]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[6].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[7].first->Pos() = Vector3(-69, -101, 0);
		skillTreeSlots[7].first->GetMaterial()->SetDiffuseMap(skills[7]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[7].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[8].first->Pos() = Vector3(-69, -144, 0);
		skillTreeSlots[8].first->GetMaterial()->SetDiffuseMap(skills[8]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[8].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[9].first->Pos() = Vector3(76, -60, 0);
		skillTreeSlots[9].first->GetMaterial()->SetDiffuseMap(skills[9]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[9].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };
	}
}

void SkillManager::CreateP_SkillTree()
{
	// 프레임 이미지 설정
	skillTreeFrame->GetMaterial()->SetDiffuseMap(L"Textures/UI/P_skillTree.png");

	// 스킬 생성
	{
		SkillBase* skill = new P_001_Avengers_Shield();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new P_002_HOTR();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new P_003_Grand_Crusader();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new P_004_Ardent_Defender();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new P_005_Barricade_Of_Faith();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new P_006_Bulwark_Of_Order();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new P_007_Blessing_of_Spellwarding();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new P_008_Guardian_Of_Ancient_Kings();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new P_009_Eye_Of_Tyr();
		skill->SetOwner(player);
		skills.push_back(skill);

		skill = new P_010_Moment_Of_Glory();
		skill->SetOwner(player);
		skills.push_back(skill);
	}

	// 슬롯 위치 지정 & 이미지 지정
	{
		skillTreeSlots[0].first->Pos() = Vector3(3, 75, 0);
		skillTreeSlots[0].first->GetMaterial()->SetDiffuseMap(skills[0]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[0].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[1].first->Pos() = Vector3(-80, 32, 0);
		skillTreeSlots[1].first->GetMaterial()->SetDiffuseMap(skills[1]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[1].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[2].first->Pos() = Vector3(3, 32, 0);
		skillTreeSlots[2].first->GetMaterial()->SetDiffuseMap(skills[2]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[2].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[3].first->Pos() = Vector3(3, -11, 0);
		skillTreeSlots[3].first->GetMaterial()->SetDiffuseMap(skills[3]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[3].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[4].first->Pos() = Vector3(85, -11, 0);
		skillTreeSlots[4].first->GetMaterial()->SetDiffuseMap(skills[4]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[4].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[5].first->Pos() = Vector3(-80, -55, 0);
		skillTreeSlots[5].first->GetMaterial()->SetDiffuseMap(skills[5]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[5].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[6].first->Pos() = Vector3(3, -54, 0);
		skillTreeSlots[6].first->GetMaterial()->SetDiffuseMap(skills[6]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[6].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[7].first->Pos() = Vector3(3, -97, 0);
		skillTreeSlots[7].first->GetMaterial()->SetDiffuseMap(skills[7]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[7].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[8].first->Pos() = Vector3(3, -138, 0);
		skillTreeSlots[8].first->GetMaterial()->SetDiffuseMap(skills[8]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[8].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };

		skillTreeSlots[9].first->Pos() = Vector3(-80, -138, 0);
		skillTreeSlots[9].first->GetMaterial()->SetDiffuseMap(skills[9]->GetIcon()->GetMaterial()->GetDiffuseMap());
		skillTreeSlots[9].first->GetColor() = { 0.3f, 0.3f, 0.3f, 1.0f };
	}
}

void SkillManager::MoveSkillFrame()
{
	// 스킬이 선택 중이면 종료
	if (bIsSelected) return;

	// 스킬트리 프레임이 선택되었다면?
	if (skillTreeFrame->GetSelect())
	{
		// 슬롯이 선택된 것이 아닌지 체크하기
		for (pair<Slot*, bool> slot : skillTreeSlots)
		{
			if (slot.first->GetSelect())
			{
				return;
			}
		}

		for (pair<Slot*, bool> slot : skillTreeSlots)
		{
			// 슬롯이 선택된 것이 아닌지 체크하기
			if (mousePos.x <= slot.first->GlobalPos().x + slot.first->GetSize().x && mousePos.x >= slot.first->GlobalPos().x - slot.first->GetSize().x &&
				mousePos.y <= slot.first->GlobalPos().y + slot.first->GetSize().y && mousePos.y >= slot.first->GlobalPos().y - slot.first->GetSize().y)
			{
				return;
			}
		}

		// 마우스 이동량의 Delta값 만큼 이동시키기
		if (!bIsMove)
		{
			prevPos = mousePos;
			bIsMove = true;
		}
		else
		{
			float deltaX = prevPos.x - mousePos.x;
			float deltaY = prevPos.y - mousePos.y;

			skillTreeFrame->Pos().x += -deltaX;
			skillTreeFrame->Pos().y += -deltaY;

			prevPos = mousePos;
		}
	}
}

void SkillManager::StopSkillFrame()
{
	// 이동중이 아니라고 설정
	bIsMove = false;
}

void SkillManager::LearnSkill(void* slot)
{
	Slot* tmpSlot = static_cast<Slot*>(slot);

	if (tmpSlot)
	{
		// 모든 슬롯을 순회하며 동일한 슬롯 인덱스 찾기
		int idx = 0;
		for (pair<Slot*, bool> slot : skillTreeSlots)
		{
			if (slot.first == tmpSlot)
			{
				break;
			}
			idx++;
		}

		// 인덱스가 범위를 넘었다면 종료
		if (idx >= 10) return;

		tempIndex = idx;

		// 만약 해당 스킬이 이미 배워진 것이라면 종료
		if (skillTreeSlots[idx].second == true) return;

		// 스킬 배우기
		if (player->LearnSkill(skills[idx]))
		{
			// 배우는데 성공했으므로 스킬 색상 활성화
			skillTreeSlots[idx].first->GetColor() = { 1.0f, 1.0f, 1.0f, 1.0f };
			// 스킬을 배웠다고 표시
			skillTreeSlots[idx].second = true;
		}
	}
}
