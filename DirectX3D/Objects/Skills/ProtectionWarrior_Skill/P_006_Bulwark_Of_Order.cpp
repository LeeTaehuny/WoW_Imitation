#include "Framework.h"
#include "P_006_Bulwark_Of_Order.h"

P_006_Bulwark_Of_Order::P_006_Bulwark_Of_Order()
{
	skillName = "P_006_Bulwark_Of_Order";

	icon = new Quad(L"Textures/Character_Skill_Icon/ProtectionWarrior/006.jpg");
	prevSkills.resize(2);
	prevSkills[0] = "P_002_HOTR";
	prevSkills[1] = "P_004_Ardent_Defender";
}

P_006_Bulwark_Of_Order::~P_006_Bulwark_Of_Order()
{
}

void P_006_Bulwark_Of_Order::Update()
{
}

void P_006_Bulwark_Of_Order::Render()
{
}

void P_006_Bulwark_Of_Order::UseSkill()
{
	owner->GetStat().hp += owner->GetStat().damage * 0.6f;
	if (owner->GetStat().hp >= owner->GetStat().maxHp)
	{
		owner->GetStat().hp = owner->GetStat().maxHp;
	}
}