#include "Framework.h"
#include "M_008_Multi_Shot.h"

M_008_Multi_Shot::M_008_Multi_Shot() : ActiveSkill(SkillType::Target)
{
	skillName = "M_008_Multi_Shot";

	hitCollider = new SphereCollider();
	hitCollider->Scale().x *= 5;
	hitCollider->Scale().z *= 5;

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 5.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본 쿨타임은 : (4초)
		MAX_delay = 4.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// 마나 소모 : 2.0%
		usingType = monster_Data;
	}
	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/008.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "M_004_Lone_Wolf";
	prevSkills[1] = "M_006_Streamline";

	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	monsters.resize(20);
	targetArrows.resize(20);
	startTiming.resize(20);

	FOR(20)
	{
		targetCollider.push_back(new SphereCollider());
		monsterTecture.push_back(new Quad(L"Textures/Effect/Alpha_Red_snow.png"));
		monsterTecture[i]->Scale() *= 0.05f;
		monsterTecture[i]->SetParent(targetCollider[i]);
		monsterTecture[i]->UpdateWorld();
	}
}

M_008_Multi_Shot::~M_008_Multi_Shot()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;

	for (Quad* quad : monsterTecture)
		delete quad;
	for (Collider* tran : targetCollider)
		delete tran;

	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void M_008_Multi_Shot::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		int imsivalue = 0;
		FOR(ThisNumber)
		{
			Using(i);

			if (!targetArrows[i])
				imsivalue++;

			if (ThisNumber <= imsivalue)
			{
				ThisNumber = 0;
				isRun = false;
			}
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void M_008_Multi_Shot::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		blendState[1]->SetState();
		depthState[1]->SetState();

		FOR(ThisNumber)
		{
			if (monsterTecture[i]->Active())
				monsterTecture[i]->Render();
		}

		blendState[0]->SetState();
		depthState[0]->SetState();
	}
}

void M_008_Multi_Shot::UseSkill(MonsterBase* monsterbase)
{
	if (isCooldown || monsterbase == nullptr ||
		owner->GetStat().mp < 20) return;

	if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(owner))
	{
		c->SetState(MarksmanshipHunter_in::State::ATTACK1);
	}

	ThisNumber = 0;
	monsters[ThisNumber] = monsterbase;
	ThisNumber++;
	animStart = 0;
	isRun = true;
	isCooldown = true;

	hitCollider->Pos() = monsters[0]->GetCollider()->GlobalPos();
	hitCollider->UpdateWorld();
	vector<MonsterBase*> monster;
	monster = MONSTER->GetSkeleton();
	for (int i = 0; i < monster.size(); ++i)
	{
		if (monsters[0] == monster[i]) continue;

		if (hitCollider->IsCollision(monster[i]->GetCollider()))
		{
			if (ThisNumber >= 20) break;
			monsters[ThisNumber] = monster[i];
			ThisNumber++;
		}
	}
	monster = MONSTER->GetSkeleton_Knight();
	for (int i = 0; i < monster.size(); ++i)
	{
		if (monsters[0] == monster[i]) continue;

		if (hitCollider->IsCollision(monster[i]->GetCollider()))
		{
			if (ThisNumber >= 20) break;
			monsters[ThisNumber] = monster[i];
			ThisNumber++;
		}
	}
	monster = MONSTER->GetScarecrow();
	for (int i = 0; i < monster.size(); ++i)
	{
		if (monsters[0] == monster[i]) continue;

		if (hitCollider->IsCollision(monster[i]->GetCollider()))
		{
			if (ThisNumber >= 20) break;
			monsters[ThisNumber] = monster[i];
			ThisNumber++;
		}
	}

	if (ThisNumber < 5)
		skillDamage = owner->GetStat().damage * 0.5f;
	else
		skillDamage = owner->GetStat().damage * 0.2f;

	owner->GetStat().mp -= 20;

	FOR(ThisNumber)
	{
		if (targetArrows[i] == nullptr)
		{
			targetArrows[i] = ARROW->GetActiveArrow();
		}		
		targetArrows[i]->SetActive(true);
	}

	FOR(ThisNumber)
	{
		targetArrows[i]->SetParent(targetCollider[i]);
		targetArrows[i]->SetActive(false);
		startTiming[i] = 0;
	}
}

void M_008_Multi_Shot::Using(int imto)
{
	if (monsters[imto])
	{
		if (startTiming[imto] == 0)
		{
			startTiming[imto]++;
			targetCollider[imto]->Pos() = owner->GlobalPos();
			targetCollider[imto]->Pos().y += owner->GlobalScale().y;
			targetCollider[imto]->SetActive(true);
			targetCollider[imto]->UpdateWorld();
			targetArrows[imto]->SetActive(true);
			monsterTecture[imto]->SetActive(true);
		}

		direction = (monsters[imto]->GetCollider()->GlobalPos() - targetCollider[imto]->GlobalPos()).GetNormalized();
		targetCollider[imto]->Pos() += direction * speed * DELTA;
		targetArrows[imto]->Rot().y = atan2(direction.x, direction.z) - 1.6f;
		targetArrows[imto]->UpdateWorld();
		targetCollider[imto]->UpdateWorld();
		monsterTecture[imto]->Rot() = CAM->Rot();
		monsterTecture[imto]->UpdateWorld();
		if (targetCollider[imto]->IsCollision(monsters[imto]->GetCollider()))
		{
			monsters[imto]->Hit(skillDamage);
			targetCollider[imto]->SetActive(false);
			monsterTecture[imto]->SetActive(false);
			targetArrows[imto]->SetActive(false);
			monsters[imto] = nullptr;
		}
	}
}