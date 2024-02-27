#include "Framework.h"
#include "Lich_001_Necrotic_Plague.h"

Lich_001_Necrotic_Plague::Lich_001_Necrotic_Plague(Boss_LichKing* lich)
{
	this->lich = lich;

	particle = new ParticleSystem("TextData/Particles/LichKing/LichKing_01.fx");
	Yad = new SphereCollider();
	Yad->Scale() *= 5;
	Yad->UpdateWorld();

	MAX_delay = 30;
	coolTime = MAX_delay;
	Max_animStart = 0.45f;
	isCooldown = true;
	isRun = false;
}

Lich_001_Necrotic_Plague::~Lich_001_Necrotic_Plague()
{
	delete particle;
	delete Yad;
}

void Lich_001_Necrotic_Plague::Update()
{
	if (isRun)
	{
		animStart += DELTA;
		if (animStart <= Max_animStart) return;

		if (!particle->IsPlay())
		{
			particle->Play(Vector3());
		}

		if (particle->IsPlay())
		{
			particle->SetPos(characterData->Pos());
			particle->Update();
		}
		
		onTime -= DELTA;
		if (onTime <= 0)
		{
			tickDamageCount++;
			onTime = Max_onTime;

			if ((characterData->GetStat().hp - charcter_HP_LastData) < charcter_HP_ratio)
			{
				characterData->OnHit(characterData->GetStat().maxHp * 0.3f);
				charcter_HP_LastData = characterData->GetStat().hp;
			}
			else
			{
				isRun = false;
				tickDamageCount = 0;
				return;
			}

			// 이 공격으로 인해 해당 캐릭터가 죽었거나
			// 틱 데미지를 3번 받았을 경우
			if (characterData->GetStat().hp <= 0 || tickDamageCount == 3)
			{
				Yad->Pos() = characterData->GlobalPos();
				Yad->UpdateWorld();
				//lich->GetStat().damage = 2;

				vector<CH_Base_ver2*> plData = lich->characterData;
				float min_Len = FLT_MAX;
				CH_Base_ver2* min_charac = nullptr;
				for (CH_Base_ver2* ch : plData)
				{
					if (ch == characterData) continue;

					if (Yad->IsCollision(ch->GetCollider()))
					{
						Vector3 imLeng = characterData->GlobalPos() - ch->GlobalPos();
						float imflflfl = imLeng.Length();

						if (min_Len >= imflflfl)
						{
							min_Len = imflflfl;
							min_charac = ch;
						}
					}
				}

				if (min_charac != nullptr)
				{
					characterData = min_charac;
					charcter_HP_LastData = characterData->GetStat().hp;
					charcter_HP_ratio = characterData->GetStat().maxHp * 0.3f;
					tickDamageCount = 0;
				}
				else
				{
					isRun = false;
					tickDamageCount = 0;
				}
			}
		}
	}

	if (isCooldown && !isRun)
		Lich_000_Base::Cooldown();
}

void Lich_001_Necrotic_Plague::Render()
{
	if (isRun)
	{
		if (animStart <= Max_animStart) return;

		if (particle->IsPlay())
			particle->Render();
	}
}

void Lich_001_Necrotic_Plague::UseSkill(CH_Base_ver2* chbase)
{
	if (isCooldown || chbase == nullptr) return;
	characterData = chbase;

	isRun = true;
	isCooldown = true;
	tickDamageCount = 0;

	MAX_delay = 60;
	coolTime = MAX_delay;

	charcter_HP_LastData = characterData->GetStat().hp;
	charcter_HP_ratio = characterData->GetStat().maxHp * 0.3f;
	animStart = 0;
}