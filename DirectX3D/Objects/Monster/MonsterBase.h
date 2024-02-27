#pragma once

// 피격 정보를 출력하기 위한 구조체
struct HitDesc
{
	// 출력 On, Off
	bool isPrint = false;
	// 피격 데미지
	string damage = "";
	// 출력 시간
	float duration = 1.0f;
};

enum MonsterType
{
	MON, LICH,
};

class MonsterBase
{
public:
	// 몬스터의 피격 콜라이더
	CapsuleCollider* collider;

	int GetmyNumber() { return index; }

	virtual void Update() = 0;
	virtual void Spawn(Vector3 pos) = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
	virtual void Hit(float amount = 1) = 0;

	CapsuleCollider* GetCollider() { return collider; }
	Transform* GetTransform() { return transform; }
	float GetHpPercent() { return curHP / maxHP; }

	MonsterType GetMonsterType() { return type; }

	void targetActiveSerch()
	{
		if (!targetTransform->GetCollider()->Active())
		{
			attackTarget_serch->UpdateWorld();
			float atk_leng = FLT_MAX;
			vector<CH_Base_ver2*> characterData = CH->GetCharcterData();
			CH_Base_ver2* lom = target[0];
			for (int i = 0; i < characterData.size(); ++i)
			{
				if (!characterData[i]->GetCollider()->Active()) continue;
				if (attackTarget_serch->IsCollision(characterData[i]->GetCollider()))
				{
					Vector3 leng = characterData[i]->GlobalPos() - attackTarget_serch->GlobalPos();
					float min = leng.Length();

					if (atk_leng >= min)
					{
						atk_leng = min;
						lom = characterData[i];
					}
				}
			}
			targetTransform = lom;
		}
	}

protected:

	// 타겟의 콜라이더를 받아옴 (나중에 변경 가능)
	vector<CH_Base_ver2*> target;
	// 현재 타겟의 정보를 받아옴 (공격을 위한 변수)
	CH_Base_ver2* targetTransform;
	// 현재 움직일 수 있는가를 판별하는 변수 (거짓이면 움직이지 못함)
	bool Moving = true;

	Transform* transform;
	// 공격범위 콜라이더 (충돌시 공격 모션 재생)
	SphereCollider* attackRange;
	// 실제 공격 범위 (충돌시 대상에게 데미지를 줌)
	BoxCollider* attackBumwe;
	Collider* attackTarget_serch;
	float Max_attack_deley = 0.9f;
	float attack_deley = Max_attack_deley;
	int oneAttack = 0;

	ModelAnimatorInstancing* instancing;
	ModelAnimatorInstancing::Motion* motion;

	Transform* root;

	float moveSpeed = 30;
	float maxHP;
	float curHP;
	float Atk;

	// 방향
	Vector3 velocity;

	UINT index;
	// 현재 재생중인 애니메이션
	vector<map<float, Event>> totalEvents;
	vector<map<float, Event>::iterator> eventIters;

protected:
	// 피격시 데미지를 화면에 띄워주기 위한 배열 선언
	vector<HitDesc> hitText;

	MonsterType type = MON;
};