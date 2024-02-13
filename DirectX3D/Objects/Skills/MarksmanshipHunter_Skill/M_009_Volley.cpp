#include "Framework.h"
#include "M_009_Volley.h"

M_009_Volley::M_009_Volley() : ActiveSkill(SkillType::Target)
{
	hitCollider = new SphereCollider();
	hitCollider->Scale().x *= 5;
	hitCollider->Scale().z *= 5;

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 5.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본 쿨타임은 : (45초)
		MAX_delay = 4.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// 마나 소모 : 8.0%
		usingType = monster_Data;
	}
	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/009.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "M_008_Multi_Shot";

	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	targetArrows.resize(25);
	startTiming.resize(25);
	directions.resize(25);
	velocity.resize(25);

	FOR(25)
	{
		targetCollider.push_back(new SphereCollider(0.05f));
		monsterTecture.push_back(new Quad(L"Textures/Effect/Alpha_Red_snow.png"));
		monsterTecture[i]->Scale() *= 0.05f;
		monsterTecture[i]->SetParent(targetCollider[i]);
		monsterTecture[i]->UpdateWorld();
	}
}

M_009_Volley::~M_009_Volley()
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

void M_009_Volley::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		FOR(ThisNumber)
			Using(i);

		tickDamageTime += DELTA;
		if (tickDamageTime >= Max_tickDamageTime)
		{
			tickDamageTime = 0;

			vector<MonsterBase*> monster;
			monster = MONSTER->GetSkeleton();
			for (int i = 0; i < monster.size(); ++i)
			{
				if (hitCollider->IsCollision(monster[i]->GetCollider()))
				{
					monster[i]->Hit(skillDamage);
				}
			}
			monster = MONSTER->GetSkeleton_Knight();
			for (int i = 0; i < monster.size(); ++i)
			{
				if (hitCollider->IsCollision(monster[i]->GetCollider()))
				{
					monster[i]->Hit(skillDamage);
				}
			}
			monster = MONSTER->GetScarecrow();
			for (int i = 0; i < monster.size(); ++i)
			{
				if (hitCollider->IsCollision(monster[i]->GetCollider()))
				{
					monster[i]->Hit(skillDamage);
				}
			}
		}

		runTime += DELTA;
		if (runTime >= Max_runTime)
		{
			runTime = 0;
			isRun = false;

			FOR(targetArrows.size())
			{
				targetCollider[i]->SetActive(false);
				monsterTecture[i]->SetActive(false);
				monsterTecture[i]->SetParent(nullptr);
				targetArrows[i]->SetActive(false);
				targetArrows[i] = nullptr;
			}
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void M_009_Volley::Render()
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

void M_009_Volley::UseSkill(MonsterBase* monsterbase)
{
	if (isCooldown || monsterbase == nullptr ||
		owner->GetStat().mp < 80) return;

	targetMonster = monsterbase;
	ThisNumber = -1;

	if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(owner))
	{
		c->SetState(MarksmanshipHunter_in::State::ATTACK1);
	}

	skillDamage = owner->GetStat().damage * 0.24f;
	owner->GetStat().mp -= 80;
	animStart = 0;
	isRun = true;
	isCooldown = true;

	hitCollider->SetActive(true);
	hitCollider->Pos() = targetMonster->GetCollider()->GlobalPos();
	hitCollider->Pos().y -= targetMonster->GetCollider()->Scale().y * 4;
	hitCollider->UpdateWorld();

	FOR(targetArrows.size())
	{
		targetArrows[i] = ARROW->GetActiveArrow();
		targetArrows[i]->SetActive(true);
		ThisNumber++;
	}

	FOR(ThisNumber)
	{
		targetArrows[i]->SetParent(targetCollider[i]);
		targetArrows[i]->SetActive(false);
		startTiming[i] = 0;
	}
}

void M_009_Volley::Using(int imto)
{
	if (startTiming[imto] == 0)
	{
		startTiming[imto]++;
		targetCollider[imto]->SetActive(true);
		targetCollider[imto]->Pos() = hitCollider->GlobalPos();
		targetCollider[imto]->Pos().y += hitCollider->GlobalScale().y * 20;
		targetCollider[imto]->UpdateWorld();

		targetArrows[imto]->SetActive(true);
		targetArrows[imto]->Pos().x = Random(-hitCollider->GlobalScale().x, hitCollider->GlobalScale().x);
		targetArrows[imto]->Pos().z = Random(-hitCollider->GlobalScale().z,	hitCollider->GlobalScale().z);
		targetArrows[imto]->UpdateWorld();

		monsterTecture[imto]->SetActive(true);
		monsterTecture[imto]->SetParent(targetArrows[imto]);
		monsterTecture[imto]->UpdateWorld();

		// 무조건 밑으로 떨어트림
		directions[imto] = Vector3(0, -1, 0);
		velocity[imto] = Random(10, 20);
		targetArrows[imto]->Rot().z = -1.8;
	}

	targetArrows[imto]->UpdateWorld();
	targetCollider[imto]->Pos() += directions[imto] * velocity[imto] * DELTA;
	targetCollider[imto]->UpdateWorld();
	monsterTecture[imto]->Rot() = CAM->Rot();
	monsterTecture[imto]->UpdateWorld();

	
	if (targetCollider[imto]->IsCollision(hitCollider))
	{
		startTiming[imto] = 0;
	}
}