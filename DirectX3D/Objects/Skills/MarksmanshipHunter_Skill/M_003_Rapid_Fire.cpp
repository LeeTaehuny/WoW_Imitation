#include "Framework.h"
#include "M_003_Rapid_Fire.h"

// 일단 보류
// 첫 사용은 문제가 없지만 두 번째 사용부터 화살 모델이 안보임
M_003_Rapid_Fire::M_003_Rapid_Fire() : ActiveSkill(SkillType::Target)
{
	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 5.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본 쿨타임은 : (20초)
		MAX_delay = 2.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// 마나 소모 : 10.0%
		usingType = monster_Data;
	}
	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/003.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "M_002_Crack_Shot";
	seven.resize(7);

	FOR(7)
	{
		it_me_Mario.push_back(new SphereCollider());
		deleyTime.push_back(0.0f);
		startTiming.push_back(0);
		effectTexture.push_back(new Quad(L"Textures/Effect/Alpha_Red_snow.png"));
		effectTexture[i]->SetParent(it_me_Mario[i]);
		effectTexture[i]->Scale() *= 0.05f;
		effectTexture[i]->SetActive(false);
		effectTexture[i]->UpdateWorld();
		skillonoff.push_back(false);
	}

	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

M_003_Rapid_Fire::~M_003_Rapid_Fire()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete monster;

	for (Quad* qu : effectTexture)
		delete qu;
	for (Collider* col : it_me_Mario)
		delete col;
	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void M_003_Rapid_Fire::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		int imto = 0;
		tack(imto);

		imto = 1;
		if (deleyTime[imto] <= Max_time)
		{
			deleyTime[imto] += DELTA;
			return;
		}
		tack(imto);

		imto = 2;
		if (deleyTime[imto] <= Max_time)
		{
			deleyTime[imto] += DELTA;
			return;
		}
		tack(imto);

		imto = 3;
		if (deleyTime[imto] <= Max_time)
		{
			deleyTime[imto] += DELTA;
			return;
		}
		tack(imto);

		imto = 4;
		if (deleyTime[imto] <= Max_time)
		{
			deleyTime[imto] += DELTA;
			return;
		}
		tack(imto);

		imto = 5;
		if (deleyTime[imto] <= Max_time)
		{
			deleyTime[imto] += DELTA;
			return;
		}
		tack(imto);

		imto = 6;
		if (deleyTime[imto] <= Max_time)
		{
			deleyTime[imto] += DELTA;
			return;
		}
		tack(imto);
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void M_003_Rapid_Fire::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		blendState[1]->SetState();
		depthState[1]->SetState();

		FOR(seven.size())
		{
			if (effectTexture[i]->Active())
				effectTexture[i]->Render();
		}

		blendState[0]->SetState();
		depthState[0]->SetState();
	}
}

void M_003_Rapid_Fire::UseSkill(MonsterBase* monsterbase)
{
	if (isRun || isCooldown || monsterbase == nullptr ||
		owner->GetStat().mp < 100) return;

	if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(owner))
	{
		c->SetState(MarksmanshipHunter_in::State::ATTACK1);
	}

	monster = monsterbase;
	animStart = 0;
	isRun = true;
	isCooldown = true;

	skillDamage = owner->GetStat().damage * 0.4f;
	owner->GetStat().mp -= 100;

	FOR(7)
	{
		if (!seven[i])
		{
			seven[i] = ARROW->GetActiveArrow();
			seven[i]->SetActive(true);
			seven[i]->SetParent(it_me_Mario[i]);
		}		
	}

	FOR(7)
	{
		it_me_Mario[i]->SetActive(true);
		seven[i]->SetActive(false);
		startTiming[i] = 0;
		deleyTime[i] = 0;
		skillonoff[i] = true;
	}
}

void M_003_Rapid_Fire::tack(int imto)
{
	//if (it_me_Mario[imto]->Active())
	if (skillonoff[imto])
	{
		if (startTiming[imto] == 0)
		{
			startTiming[imto]++;
			it_me_Mario[imto]->Pos() = owner->GlobalPos();
			it_me_Mario[imto]->Pos().y += owner->GlobalScale().y;
			it_me_Mario[imto]->SetActive(true);
			it_me_Mario[imto]->UpdateWorld();
			seven[imto]->SetActive(true);
			seven[imto]->UpdateWorld();
			effectTexture[imto]->SetActive(true);
		}

		direction = (monster->GetCollider()->GlobalPos() - it_me_Mario[imto]->GlobalPos()).GetNormalized();
		it_me_Mario[imto]->Pos() += direction * speed * DELTA;
		seven[imto]->Rot().y = atan2(direction.x, direction.z) - 1.6f;
		seven[imto]->UpdateWorld();
		it_me_Mario[imto]->UpdateWorld();
		effectTexture[imto]->Rot() = CAM->Rot();
		effectTexture[imto]->UpdateWorld();
		if (it_me_Mario[imto]->IsCollision(monster->GetCollider()))
		{
			if (imto == 6)
			{
				isRun = false;
			}
			monster->Hit(skillDamage);
			it_me_Mario[imto]->SetActive(false);
			effectTexture[imto]->SetActive(false);
			seven[imto]->SetActive(false);
			skillonoff[imto] = false;
		}
	}
}