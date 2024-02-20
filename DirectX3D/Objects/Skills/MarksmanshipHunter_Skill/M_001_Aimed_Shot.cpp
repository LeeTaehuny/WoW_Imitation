#include "Framework.h"
#include "M_001_Aimed_Shot.h"

M_001_Aimed_Shot::M_001_Aimed_Shot() : ActiveSkill(SkillType::Target)
{
	skillName = "M_001_Aimed_Shot";

	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 20.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본 쿨타임은 : (6초)
		// 충천하여 스킬을 사용하는 방식 (2회 충전)
		// 그렇기 때문에 쿨타입을 반으로 줄임
		MAX_delay = 6.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// 마나 소모 : 3.5%
		requiredMp = 35.0f;
		usingType = monster_Data;
	}
	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/001.jpg");

	effectTexture = new Quad(L"Textures/Effect/Alpha_Red_snow.png");
	effectTexture->Scale() *= 0.05f;
	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

M_001_Aimed_Shot::~M_001_Aimed_Shot()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete targetMonster;
	delete effectTexture;

	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void M_001_Aimed_Shot::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		// 해당 몬스터가 죽어서 액티브가 꺼졌을 경우 
		if (!targetMonster->GetCollider()->Active())
		{
			myCollider->SetActive(false);
			arrow->SetActive(false);
			arrow->SetIsRun(false);
			effectTexture->SetParent(nullptr);
			isRun = false;
			return;
		}

		direction = (targetMonster->GetCollider()->GlobalPos() - myCollider->GlobalPos()).GetNormalized();
		myCollider->Pos() += direction * speed * DELTA;
		myCollider->UpdateWorld();

		effectTexture->Rot() = CAM->Rot() * 1.6f;
		arrow->Rot().y = atan2(direction.x, direction.z) - 1.6f;;
		arrow->SetActive(true);
		arrow->UpdateWorld();
		effectTexture->UpdateWorld();

		if (myCollider->IsCollision(targetMonster->GetCollider()))
		{
			targetMonster->Hit(skillDamage);
			myCollider->SetActive(false);
			arrow->SetActive(false);
			arrow->SetIsRun(false);
			effectTexture->SetParent(nullptr);
			isRun = false;
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void M_001_Aimed_Shot::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		blendState[1]->SetState();
		depthState[1]->SetState();
		effectTexture->Render();
		blendState[0]->SetState();
		depthState[0]->SetState();
	}
}

void M_001_Aimed_Shot::UseSkill(MonsterBase* monsterbase)
{
	if (isCooldown || monsterbase == nullptr ||
		owner->GetStat().mp < requiredMp) return;

	if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(owner))
	{
		c->SetState(MarksmanshipHunter_in::State::ATTACK1);
	}

	skillDamage = owner->GetStat().damage * 2.8f;
	owner->GetStat().mp -= requiredMp;

	myCollider->Pos() = owner->GlobalPos();
	myCollider->Pos().y += owner->GlobalScale().y;
	myCollider->SetActive(true);
	myCollider->UpdateWorld();

	arrow = ARROW->GetActiveArrow();
	arrow->SetParent(myCollider);
	arrow->UpdateWorld();

	effectTexture->SetParent(arrow);

	targetMonster = monsterbase;
	animStart = 0;
	isRun = true;
	isCooldown = true;
}