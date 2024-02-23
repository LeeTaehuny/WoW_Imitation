#include "Framework.h"

#include "Objects/Character_/CH_Base_ver2.h"
#include "Objects/Character_/ArmsWarrior_in.h"
#include "Objects/Character_/FireMage_in.h"
#include "Objects/Character_/HolyPriest_in.h"
#include "Objects/Character_/MarksmanshipHunter_in.h"
#include "Objects/Character_/ProtectionWarrior_in.h"
#include "Objects/UI/PartyUI_Bar.h"
#include "CH_Manager.h"

#define UPDATE(k) if (k != nullptr) k->Update()
#define RENDER(k) if (k != nullptr) k->Render()

CH_Manager::CH_Manager()
{
	//InstancingDataArms();
	//InstancingDataFire();
	//InstancingDataHoly();
	//InstancingDataMarksmanship();
	//InstancingDataProtection();

	partyUI = new PartyUI_Bar();
	partyUI->Pos() = { CENTER_X + 480.0f, CENTER_Y , 0 };

}
CH_Manager::~CH_Manager()
{
	delete paladin;
	delete firemage;
	delete holypriest;
	delete armswarrior;
	delete marksmanshiphunter;

	for (CH_Base_ver2* ch : character)
		delete ch;
}

void CH_Manager::Update()
{
	UPDATE(armswarrior);
	UPDATE(paladin);
	UPDATE(firemage);
	UPDATE(marksmanshiphunter);
	UPDATE(holypriest);

	for (CH_Base_ver2* ch : character)
	{
		if (ch != nullptr)
		{
			if (KEY_DOWN('Z'))
				ch->SetAttackOrder();

			ch->Update();
		}
	}
	
	partyUI->Update();
}

void CH_Manager::PreRender()
{
}

void CH_Manager::Render()
{
	RENDER(armswarrior);
	RENDER(paladin);
	RENDER(firemage);
	RENDER(marksmanshiphunter);
	RENDER(holypriest);

	for (CH_Base_ver2* ch : character)
		if (ch != nullptr) ch->Render();
}

void CH_Manager::PostRender()
{
	for (CH_Base_ver2* ch : character)
		if (ch != nullptr) ch->UIRender();

	partyUI->PostRender();
}

void CH_Manager::GUIRender()
{
	for (CH_Base_ver2* ch : character)
		if (ch != nullptr) ch->GUIRender();
}

void CH_Manager::InstancingDataArms()
{
	armswarrior = new ModelAnimatorInstancing("armswarrior");
	armswarrior->ReadClip("Idle_1");
	armswarrior->ReadClip("Idle_2");
	armswarrior->ReadClip("Attack_1");
	armswarrior->ReadClip("Attack_2");
	armswarrior->ReadClip("Walk_F");
	armswarrior->ReadClip("Walk_B");
	armswarrior->ReadClip("Walk_L");
	armswarrior->ReadClip("Walk_R");
	armswarrior->ReadClip("Die");
	armswarrior->ReadClip("Hit");
	armswarrior->ReadClip("Jump");
}
void CH_Manager::InstancingDataFire()
{
	firemage = new ModelAnimatorInstancing("FireMage");
	firemage->ReadClip("Idle_1");
	firemage->ReadClip("Idle_2");
	firemage->ReadClip("Attack_1");
	firemage->ReadClip("Attack_2");
	firemage->ReadClip("Attack_3");
	firemage->ReadClip("Walk_F");
	firemage->ReadClip("Walk_B");
	firemage->ReadClip("Walk_L");
	firemage->ReadClip("Walk_R");
	firemage->ReadClip("Die_1");
	firemage->ReadClip("Hit_1");
	firemage->ReadClip("Jump");
}
void CH_Manager::InstancingDataHoly()
{
	holypriest = new ModelAnimatorInstancing("HolyPriest");
	holypriest->ReadClip("Idle_1");
	holypriest->ReadClip("Idle_2");
	holypriest->ReadClip("Idle_3");
	holypriest->ReadClip("Attack_1");
	holypriest->ReadClip("Attack_2");
	holypriest->ReadClip("Walk_F");
	holypriest->ReadClip("Walk_B");
	holypriest->ReadClip("Walk_L");
	holypriest->ReadClip("Walk_R");
	holypriest->ReadClip("Die");
	holypriest->ReadClip("Hit");
	holypriest->ReadClip("Jump");
}
void CH_Manager::InstancingDataMarksmanship()
{
	marksmanshiphunter = new ModelAnimatorInstancing("MarksmanshipHunter");
	marksmanshiphunter->ReadClip("Idle");
	marksmanshiphunter->ReadClip("Attack_1");
	marksmanshiphunter->ReadClip("Walk_F");
	marksmanshiphunter->ReadClip("Walk_B");
	marksmanshiphunter->ReadClip("Walk_L");
	marksmanshiphunter->ReadClip("Walk_R");
	marksmanshiphunter->ReadClip("Die");
	marksmanshiphunter->ReadClip("Hit");
	marksmanshiphunter->ReadClip("Jump");
	marksmanshiphunter->ReadClip("S_Dive");
	marksmanshiphunter->ReadClip("S_Shooting");
}
void CH_Manager::InstancingDataProtection()
{
	paladin = new ModelAnimatorInstancing("ProtectionWarrior");
	paladin->ReadClip("Idle_1");
	paladin->ReadClip("Attack_1");
	paladin->ReadClip("Walk_F");
	paladin->ReadClip("Walk_B");
	paladin->ReadClip("Walk_L");
	paladin->ReadClip("Walk_R");
	paladin->ReadClip("Die");
	paladin->ReadClip("Hit");
	paladin->ReadClip("Jump");
	paladin->ReadClip("S_Casting");
}

void CH_Manager::PlayerSpawn(int value)
{
	if (value == 1)
	{
		if (armswarrior == nullptr)
		{
			InstancingDataArms();
		}
		Transform* transform1 = armswarrior->Add();
		CH_Base_ver2* un = new ArmsWarrior_in(CreatureType::Player, transform1, armswarrior, A_count);
		un->SetTag("player");
		character.push_back(un);
		A_count++;
	}
	else if (value == 2)
	{
		if (paladin == nullptr)
		{
			InstancingDataProtection();
		}
		Transform* transform1 = paladin->Add();
		CH_Base_ver2* un = new ProtectionWarrior_in(CreatureType::Player, transform1, paladin, P_count);
		un->SetTag("player");
		character.push_back(un);
		P_count++;
	}
	else if (value == 3)
	{
		if (firemage == nullptr)
		{
			InstancingDataFire();
		}
		Transform* transform1 = firemage->Add();
		CH_Base_ver2* un = new FireMage_in(CreatureType::Player, transform1, firemage, F_count);
		un->SetTag("player");
		character.push_back(un);
		F_count++;
	}
	else if (value == 4)
	{
		if (marksmanshiphunter == nullptr)
		{
			InstancingDataMarksmanship();
		}
		Transform* transform1 = marksmanshiphunter->Add();
		CH_Base_ver2* un = new MarksmanshipHunter_in(CreatureType::Player, transform1, marksmanshiphunter, M_count);
		un->SetTag("player");
		character.push_back(un);
		M_count++;
	}
	else if (value == 5)
	{
		if (holypriest == nullptr)
		{
			InstancingDataHoly();
		}
		Transform* transform1 = holypriest->Add();
		CH_Base_ver2* un = new HolyPriest_in(CreatureType::Player, transform1, holypriest, H_count);
		un->SetTag("player");
		character.push_back(un);
		H_count++;
	}
	else
	{
		return;
	}

	//CAM->SetTarget(character[0]);
	MONSTER->SetTarget(character[0]);
}
void CH_Manager::NonPlayerSpawn(int value)
{
	if (value == 1)
	{
		if (armswarrior == nullptr)
		{
			InstancingDataArms();
		}
		Transform* transform1 = armswarrior->Add();
		CH_Base_ver2* un = new ArmsWarrior_in(CreatureType::NonPlayer, transform1, armswarrior, A_count);
		un->SetTag(to_string(nonCount));
		character.push_back(un);
		A_count++;
	}
	else if (value == 2)
	{
		if (paladin == nullptr)
		{
			InstancingDataProtection();
		}
		Transform* transform1 = paladin->Add();
		CH_Base_ver2* un = new ProtectionWarrior_in(CreatureType::NonPlayer, transform1, paladin, P_count);
		un->SetTag(to_string(nonCount));
		character.push_back(un);
		P_count++;
	}
	else if (value == 3)
	{
		if (firemage == nullptr)
		{
			InstancingDataFire();
		}
		Transform* transform1 = firemage->Add();
		CH_Base_ver2* un = new FireMage_in(CreatureType::NonPlayer, transform1, firemage, F_count);
		un->SetTag(to_string(nonCount));
		character.push_back(un);
		F_count++;
	}
	else if (value == 4)
	{
		if (marksmanshiphunter == nullptr)
		{
			InstancingDataMarksmanship();
		}
		Transform* transform1 = marksmanshiphunter->Add();
		CH_Base_ver2* un = new MarksmanshipHunter_in(CreatureType::NonPlayer, transform1, marksmanshiphunter, M_count);
		un->SetTag(to_string(nonCount));
		character.push_back(un);
		M_count++;
	}
	else if (value == 5)
	{
		if (holypriest == nullptr)
		{
			InstancingDataHoly();
		}
		Transform* transform1 = holypriest->Add();
		CH_Base_ver2* un = new HolyPriest_in(CreatureType::NonPlayer, transform1, holypriest, H_count);
		un->SetTag(to_string(nonCount));
		character.push_back(un);
		H_count++;
	}
	else
	{
		return;
	}

	character[character.size() - 1]->SetPlayer(character[0]);
	MONSTER->SetTarget(character[character.size() - 1]);
	nonCount++;

	partyUI->AddPlayer(character.size() - 1);
}

CH_Base_ver2* CH_Manager::SelectHealCharacter(IN CH_Base_ver2* collider)
{
	

	return nullptr;
}
