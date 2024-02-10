#include "Framework.h"
#include "P_014_Blessing_of_Spellwarding.h"

//
P_014_Blessing_of_Spellwarding::P_014_Blessing_of_Spellwarding() : ActiveSkill(SkillType::Target)
{
	/*
	스킬의 효과

	대상 파티원에게 10초동안 모든 마법 피해 및 해로운 효과의 면역을 줍니다.
	*/

	myCollider = new SphereCollider(2.5f);
	myCollider->SetActive(false);

	// 기본 생성 요소
	{
		// 스킬 속도 (필요 없음)
		speed = 0.0f;

		// 스킬 데미지 (회복으로 넣어야 함)
		skillDamage = 100.0f;

		// 쿨타임 설정
		MAX_delay = 300.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;
	}

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/014.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "001";
	prevSkills[1] = "005";

	particle = new ParticleSystem("TextData/Particles/holy/Heal.fx");
	//particle->Getdata().count = particle->Getdata().count;
}

P_014_Blessing_of_Spellwarding::~P_014_Blessing_of_Spellwarding()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete characterData;
	delete particle;
}

void P_014_Blessing_of_Spellwarding::Update()
{
	if (target != nullptr)
	{
		myCollider->Pos() = target->GlobalPos();
		myCollider->UpdateWorld();
	}

	// 회복이나 버프 관련은 이곳에서 추가해주면 될 듯
	if (isRun)
	{
		isRun = false;

		Vector3 im = target->GlobalPos();
		im.y += target->GlobalScale().y;
		particle->Play(im);
	}

	particle->Update();
	ActiveSkill::Cooldown();
}

void P_014_Blessing_of_Spellwarding::Render()
{
	//if (target != nullptr)
	//	myCollider->Render();
	particle->Render();
}

// 해당 스킬이 회복스킬인지 아니면 공격 스킬인지 구분하여
// 공격 스킬이라면 적의 정보를 받아오고
// 회복 스킬이면 아군의 정보를 받아오게 하는 함수를 따로 만들 필요가 있어보임
void P_014_Blessing_of_Spellwarding::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown && chbase == nullptr) return;
	target = chbase->GetCollider();
	myCollider->SetActive(true);
	isCooldown = true;
	isRun = true;
}