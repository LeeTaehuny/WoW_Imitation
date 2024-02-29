#include "Framework.h"
#include "M_009_Volley.h"

M_009_Volley::M_009_Volley() : ActiveSkill(SkillType::Target)
{
	skillName = "M_009_Volley";

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
		MAX_delay = 45.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// 마나 소모 : 8.0%
		requiredMp = 80;
		usingType = monster_Data;
	}
	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/009.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "M_008_Multi_Shot";

	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);

	Arrows.resize(25);
	startTiming.resize(25);
	directions.resize(25);
	velocity.resize(25);

	FOR(25)
	{
		targetCollider.push_back(new SphereCollider(0.05f));
		monsterTecture.push_back(new Quad(L"Textures/Effect/Alpha_Red_snow.png"));
		monsterTecture[i]->Scale() *= 0.05f;
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

		if (!isOne_sound)
		{
			switch (owner->GetcreatureType())
			{
			case CreatureType::Player:
				Audio::Get()->Play("MH_09_using", owner->Pos(), 1.0f);
				break;
			}
			isOne_sound = true;
		}

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
			monster = MONSTER->GetVAlkier();
			for (int i = 0; i < monster.size(); ++i)
			{
				if (hitCollider->IsCollision(monster[i]->GetCollider()))
				{
					monster[i]->Hit(skillDamage);
				}
			}
			monster = MONSTER->GetIceBall();
			for (int i = 0; i < monster.size(); ++i)
			{
				if (hitCollider->IsCollision(monster[i]->GetCollider()))
				{
					monster[i]->Hit(skillDamage);
				}
			}
			if (MONSTER->GetLichKing())
			{
				if (hitCollider->IsCollision(MONSTER->GetLichKing()->GetCollider()))
				{
					MONSTER->GetLichKing()->Hit(skillDamage);
				}
			}
		}

		runTime += DELTA;
		if (runTime >= Max_runTime)
		{
			runTime = 0;
			isRun = false;

			FOR(Arrows.size())
			{
				targetCollider[i]->SetActive(false);
				monsterTecture[i]->SetActive(false);
				monsterTecture[i]->SetParent(nullptr);
				if (Arrows[i] != nullptr)
				{
					Arrows[i]->Rot() = Vector3();
					Arrows[i]->Pos() = Vector3();
					Arrows[i]->SetActive(false);
					Arrows[i]->SetIsRun(false);
				}
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
		owner->GetStat().mp < requiredMp ||
		!monsterbase->GetCollider()->Active()) return;

	targetMonster = monsterbase;
	ThisNumber = 0;
	isOne_sound = false;

	if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(owner))
	{
		c->SetState(MarksmanshipHunter_in::State::ATTACK1);
	}

	skillDamage = owner->GetStat().damage * 0.24f;
	owner->GetStat().mp -= requiredMp;
	animStart = 0;
	isRun = true;
	isCooldown = true;

	hitCollider->SetActive(true);
	hitCollider->Pos() = targetMonster->GetCollider()->GlobalPos();
	hitCollider->Pos().y -= targetMonster->GetCollider()->Scale().y * 4;
	hitCollider->UpdateWorld();

	FOR(Arrows.size())
	{
		Arrows[i] = ARROW->GetActiveArrow();
		Arrows[i]->SetParent(targetCollider[i]);
		monsterTecture[i]->SetParent(Arrows[i]);
		startTiming[i] = 0;
		ThisNumber++;
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

		Arrows[imto]->SetActive(true);
		Arrows[imto]->Pos().x = Random(-hitCollider->GlobalScale().x, hitCollider->GlobalScale().x);
		Arrows[imto]->Pos().z = Random(-hitCollider->GlobalScale().z, hitCollider->GlobalScale().z);
		Arrows[imto]->UpdateWorld();

		monsterTecture[imto]->SetActive(true);
		monsterTecture[imto]->UpdateWorld();

		// 무조건 밑으로 떨어트림
		directions[imto] = Vector3(0, -1, 0);
		velocity[imto] = Random(10, 20);
		Arrows[imto]->Rot().z = -1.6f;
	}

	monsterTecture[imto]->Rot() = CAM->Rot();
	monsterTecture[imto]->UpdateWorld();

	Arrows[imto]->UpdateWorld();

	targetCollider[imto]->Pos() += directions[imto] * velocity[imto] * DELTA;
	targetCollider[imto]->UpdateWorld();

	if (targetCollider[imto]->IsCollision(hitCollider))
	{
		startTiming[imto] = 0;
	}
}