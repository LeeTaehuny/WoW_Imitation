#include "Framework.h"
#include "M_010_Wailing_Arrow.h"

M_010_Wailing_Arrow::M_010_Wailing_Arrow() : ActiveSkill(SkillType::Target)
{
	myCollider = new SphereCollider();
	myCollider->SetActive(false);
	hitCollider = new SphereCollider();
	hitCollider->Scale() *= 7;
	hitCollider->SetActive(false);

	// 기본 생성 요소
	{
		// 스킬 속도
		speed = 5.0f;

		// 스킬 데미지
		skillDamage = 0.0f;

		// 쿨타임 설정 기본 쿨타임은 : (60초)
		MAX_delay = 4.0f;
		coolTime = MAX_delay;

		// 처음은 스킬 실행중인 상태가 아니도록 설정
		isRun = false;
		isCooldown = false;

		// 마나 소모 : 1.5%
		usingType = monster_Data;
	}
	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/010.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "M_007_Focused_Aim";

	arrowTexture = new Quad(L"Textures/Effect/Alpha_Red_snow.png");
	arrowTexture->Scale() *= 0.05f;
	arrowTexture->UpdateWorld();
	arrowTexture->SetParent(myCollider);

	particle = new ParticleSystem("TextData/Particles/Hunter/Skill10.fx");
	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

M_010_Wailing_Arrow::~M_010_Wailing_Arrow()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete arrowTexture;
	delete particle;

	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void M_010_Wailing_Arrow::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		direction = (monsterTarget->GetCollider()->GlobalPos() - myCollider->Pos()).GetNormalized();
		myCollider->Pos() += direction * speed * DELTA;
		myCollider->UpdateWorld();

		arrow->SetActive(true);
		arrow->Rot().y = atan2(direction.x, direction.z) - 1.6f;
		arrow->UpdateWorld();
		arrowTexture->Rot() = CAM->Rot();
		arrowTexture->UpdateWorld();

		if (myCollider->IsCollision(monsterTarget->GetCollider()))
		{
			if (nujucIndex == 0)
			{
				particle->Play(Vector3());
				nujucIndex++;

				hitCollider->SetActive(true);
				hitCollider->Pos() = myCollider->GlobalPos();
				hitCollider->UpdateWorld();

				monsterTarget->Hit(skillDamage * 2);

				vector<MonsterBase*> monster;
				monster = MONSTER->GetSkeleton();
				for (int i = 0; i < monster.size(); ++i)
				{
					if (monster[i] == monsterTarget) continue;

					if (hitCollider->IsCollision(monster[i]->GetCollider()))
					{
						monster[i]->Hit(skillDamage);
					}
				}
				monster = MONSTER->GetSkeleton_Knight();
				for (int i = 0; i < monster.size(); ++i)
				{
					if (monster[i] == monsterTarget) continue;

					if (hitCollider->IsCollision(monster[i]->GetCollider()))
					{
						monster[i]->Hit(skillDamage);
					}
				}
				monster = MONSTER->GetScarecrow();
				for (int i = 0; i < monster.size(); ++i)
				{
					if (monster[i] == monsterTarget) continue;

					if (hitCollider->IsCollision(monster[i]->GetCollider()))
					{
						monster[i]->Hit(skillDamage);
					}
				}
			}
		}

		if (particle->IsPlay())
		{
			particle->SetPos(monsterTarget->GetCollider()->GlobalPos());
			particle->Update();
		}
		else if (!particle->IsPlay() && nujucIndex >= 1)
		{
			isRun = false;
			myCollider->SetActive(false);
			arrow->SetActive(false);
			arrow = nullptr;
			return;
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void M_010_Wailing_Arrow::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		blendState[1]->SetState();
		depthState[1]->SetState();

		arrowTexture->Render();

		blendState[0]->SetState();
		depthState[0]->SetState();

		if (particle->IsPlay())
		{
			particle->Render();
		}
	}
}

void M_010_Wailing_Arrow::UseSkill(MonsterBase* monsterbase)
{
	if (isCooldown || monsterbase == nullptr ||
		owner->GetStat().mp < 15) return;

	monsterTarget = monsterbase;
	myCollider->SetActive(true);
	myCollider->Pos() = owner->GlobalPos();
	myCollider->Pos().y += owner->Scale().y * 0.5f;
	myCollider->UpdateWorld();
	nujucIndex = 0;

	if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(owner))
	{
		c->SetState(MarksmanshipHunter_in::State::ATTACK1);
	}

	skillDamage = owner->GetStat().damage * 1.33f;
	owner->GetStat().mp -= 15;
	animStart = 0;
	isRun = true;
	isCooldown = true;

	arrow = ARROW->GetActiveArrow();
	arrow->SetParent(myCollider);
}