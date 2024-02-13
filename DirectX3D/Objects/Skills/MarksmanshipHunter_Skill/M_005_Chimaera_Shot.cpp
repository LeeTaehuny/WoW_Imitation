#include "Framework.h"
#include "M_005_Chimaera_Shot.h"

M_005_Chimaera_Shot::M_005_Chimaera_Shot() : ActiveSkill(SkillType::Target)
{
	Yad = new SphereCollider();
	Yad->Scale() *= 7;
	Yad->UpdateWorld();

	col1 = new SphereCollider();
	col1->SetActive(false);
	col2 = new SphereCollider();
	col2->SetActive(false);

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

		// 마나 소모 : 4.0%
		usingType = monster_Data;
	}
	icon = new Quad(L"Textures/Character_Skill_Icon/MarksmanshipHunter/005.jpg");
	prevSkills.resize(1);
	prevSkills[0] = "M_001_Aimed_Shot";

	effectTexture1 = new Quad(L"Textures/Effect/Alpha_Red_snow.png");
	effectTexture1->Scale() *= 0.05f;
	effectTexture1->SetParent(col1);
	effectTexture2 = new Quad(L"Textures/Effect/Alpha_Red_snow.png");
	effectTexture2->Scale() *= 0.05f;
	effectTexture2->SetParent(col2);
	FOR(2) blendState[i] = new BlendState();
	FOR(2) depthState[i] = new DepthStencilState();
	blendState[1]->Alpha(true);
	depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO);
}

M_005_Chimaera_Shot::~M_005_Chimaera_Shot()
{
	delete myCollider;
	delete hitCollider;
	delete icon;
	delete target;
	delete Yad;
	delete col1;
	delete col2;
	delete effectTexture1;
	delete effectTexture2;

	FOR(2) delete blendState[i];
	FOR(2) delete depthState[i];
}

void M_005_Chimaera_Shot::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		if (col1->Active())
		{
			tol1->SetActive(true);
			direction = (mon1->GetCollider()->GlobalPos() - col1->GlobalPos()).GetNormalized();
			col1->Pos() += direction * speed * DELTA;
			tol1->Rot().y = atan2(direction.x, direction.z) - 1.6f;
			tol1->UpdateWorld();
			col1->UpdateWorld();
			effectTexture1->Rot() = CAM->Rot();
			effectTexture1->UpdateWorld();
			if (col1->IsCollision(mon1->GetCollider()))
			{
				mon1->Hit(skillDamage);
				col1->SetActive(false);
				tol1->SetActive(false);
			}
		}

		if (col2->Active())
		{
			tol2->SetActive(true);
			direction = (mon2->GetCollider()->GlobalPos() - col2->GlobalPos()).GetNormalized();
			col2->Pos() += direction * speed * DELTA;
			tol2->Rot().y = atan2(direction.x, direction.z) - 1.6f;
			tol2->UpdateWorld();
			col2->UpdateWorld();
			effectTexture2->Rot() = CAM->Rot();
			effectTexture2->UpdateWorld();
			if (col2->IsCollision(mon2->GetCollider()))
			{
				mon2->Hit(skillDamage * 0.5f);
				col2->SetActive(false);
				tol2->SetActive(false);
			}
		}

		if (!col1->Active() && !col2->Active())
		{
			isRun = false;
		}
	}

	if (isCooldown)
		ActiveSkill::Cooldown();
}

void M_005_Chimaera_Shot::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		blendState[1]->SetState();
		depthState[1]->SetState();

		if (col1->Active())
			effectTexture1->Render();
		if (col2->Active())
			effectTexture2->Render();

		blendState[0]->SetState();
		depthState[0]->SetState();
	}
}

void M_005_Chimaera_Shot::UseSkill(MonsterBase* monsterbase)
{
	if (isCooldown || monsterbase == nullptr ||
		owner->GetStat().mp < 40) return;

	if (MarksmanshipHunter_in* c = dynamic_cast<MarksmanshipHunter_in*>(owner))
	{
		c->SetState(MarksmanshipHunter_in::State::ATTACK1);
	}

	skillDamage = owner->GetStat().damage * 1.6f;
	owner->GetStat().mp -= 40;

	mon1 = monsterbase;
	animStart = 0;
	isRun = true;
	isCooldown = true;

	col1->SetActive(true);
	col1->Pos() = owner->GlobalPos();
	col1->UpdateWorld();
	col2->SetActive(true);
	col2->Pos() = owner->GlobalPos();
	col2->UpdateWorld();

	Yad->Pos() = mon1->GetCollider()->GlobalPos();
	Yad->UpdateWorld();
	vector<MonsterBase*> monster;
	float min_length = FLT_MAX;
	monster = MONSTER->GetSkeleton();
	for (int i = 0; i < monster.size(); ++i)
	{
		if (!Yad->IsCollision(monster[i]->GetCollider()) ||
			mon1 == monster[i]) continue;

		Vector3 im = monster[i]->GetCollider()->GlobalPos() - mon1->GetTransform()->GlobalPos();
		float length = abs(im.Length());
		if (min_length >= length)
		{
			min_length = length;
			mon2 = monster[i];
		}
	}
	monster = MONSTER->GetSkeleton_Knight();
	for (int i = 0; i < monster.size(); ++i)
	{
		if (!Yad->IsCollision(monster[i]->GetCollider()) ||
			mon1 == monster[i]) continue;

		Vector3 im = monster[i]->GetCollider()->GlobalPos() - mon1->GetTransform()->GlobalPos();
		float length = abs(im.Length());
		if (min_length >= length)
		{
			min_length = length;
			mon2 = monster[i];
		}
	}
	monster = MONSTER->GetScarecrow();
	for (int i = 0; i < monster.size(); ++i)
	{
		if (!Yad->IsCollision(monster[i]->GetCollider()) ||
			mon1 == monster[i]) continue;

		Vector3 im = monster[i]->GetCollider()->GlobalPos() - mon1->GetTransform()->GlobalPos();
		float length = abs(im.Length());
		if (min_length >= length)
		{
			min_length = length;
			mon2 = monster[i];
		}
	}

	if (min_length == FLT_MAX)
	{
		col2->SetActive(false);
	}

	if (!tol1)
	{
		tol1 = ARROW->GetActiveArrow();
		tol1->SetParent(col1);
	}
	tol1->SetActive(true);
	
	if (mon2 != nullptr)
	{
		if (!tol2)
		{
			tol2 = ARROW->GetActiveArrow();
			tol2->SetParent(col2);
			tol2->UpdateWorld();
		}		
	}
	tol1->SetActive(false);
	tol1->UpdateWorld();
}