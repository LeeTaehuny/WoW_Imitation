#include "Framework.h"
#include "MonsterManager.h"

#define UPDATE(k) if (k != nullptr) k->Update()
#define UPDATEWORLD(k) if (k != nullptr) k->UpdateWorld()
#define RENDER(k) if (k != nullptr) k->Render()
#define GUIRENDER(k) if (k != nullptr) k->GUIRender()

MonsterManager::MonsterManager()
{
	skeleton_body = new ModelAnimatorInstancing("Skeleton");
	skeleton_body->ReadClip("Idle");
	skeleton_body->ReadClip("Attack_1");
	skeleton_body->ReadClip("Attack_2");
	skeleton_body->ReadClip("Walking_F");
	skeleton_body->ReadClip("Running");
	skeleton_body->ReadClip("Death");
	skeleton_body->ReadClip("Hit");
	skeleton_body->ReadClip("Scream");

	skeletonKnight_body = new ModelAnimatorInstancing("Skeleton_Knight");
	skeletonKnight_body->ReadClip("Idle");
	skeletonKnight_body->ReadClip("Attack_1");
	skeletonKnight_body->ReadClip("Walking");
	skeletonKnight_body->ReadClip("Death");
	skeletonKnight_body->ReadClip("Hit");

	scarecrow_body = new ModelAnimatorInstancing("Skeleton_Knight");
	scarecrow_body->ReadClip("Idle");
	scarecrow_body->ReadClip("Hit");

	valkier_body = new ModelAnimatorInstancing("VAlkier");
	valkier_body->ReadClip("Idle_2");
	valkier_body->ReadClip("Flying");

	Audio::Get()->Add("iceBall_die", "Sounds/Monster/iceBall/die.ogg");
	Audio::Get()->Add("iceBall_hit", "Sounds/Monster/iceBall/hit.ogg");

	Audio::Get()->Add("skeleton_hit", "Sounds/Monster/Skeleton/hit.ogg");
	Audio::Get()->Add("skeleton_die", "Sounds/Monster/Skeleton/Death.ogg");
	Audio::Get()->Add("skeleton_atk", "Sounds/Monster/Skeleton/Attack.ogg");

	Audio::Get()->Add("skeleton_Night_atk", "Sounds/Monster/Skeleton_Night/Attack.ogg");
	Audio::Get()->Add("skeleton_Night_die", "Sounds/Monster/Skeleton_Night/die.ogg");
	Audio::Get()->Add("skeleton_Night_hit", "Sounds/Monster/Skeleton_Night/hit.ogg");

	Audio::Get()->Add("valkyr_hit", "Sounds/Monster/Valkyr/hit.ogg");
	Audio::Get()->Add("valkyr_die", "Sounds/Monster/Valkyr/die.ogg");
	Audio::Get()->Add("valkyr_wing", "Sounds/Monster/Valkyr/wing.ogg");
}
MonsterManager::~MonsterManager()
{
	delete skeleton_body;
	delete skeletonKnight_body;
	delete scarecrow_body;
	delete LickKing;

	for (MonsterBase* skel : skeleton)
		delete skel;
	for (MonsterBase* skel : skeleton_Knight)
		delete skel;
	for (MonsterBase* skel : scarecrow)
		delete skel;
	for (MonsterBase* skel : valkier)
		delete skel;

	for (CH_Base_ver2* col : targets)
		delete col;
}

void MonsterManager::Update()
{
	skeleton_body->Update();
	skeletonKnight_body->Update();
	scarecrow_body->Update();
	valkier_body->Update();
	if (LickKing) LickKing->Update();

	for (int i = 0; i < skeleton.size(); i++)
	{
		if (!skeleton[i]->GetTransform()->Active())
		{
			skeleton.erase(skeleton.begin() + i);
			break;
		}
		UPDATE(skeleton[i]);
	}
	for (int i = 0; i < skeleton_Knight.size(); i++)
	{
		if (!skeleton_Knight[i]->GetTransform()->Active())
		{
			skeleton_Knight.erase(skeleton_Knight.begin() + i);
			break;
		}
		UPDATE(skeleton_Knight[i]);
	}
	for (MonsterBase* skel : scarecrow)
	{
		UPDATE(skel);
	}	
	for (int i = 0; i < valkier.size(); i++)
	{
		if (!valkier[i]->GetTransform()->Active())
		{
			valkier.erase(valkier.begin() + i);
			break;
		}
		UPDATE(valkier[i]);
	}
	for (int i = 0; i < iceBall.size(); i++)
	{
		if (!iceBall[i]->GetTransform()->Active())
		{
			iceBall.erase(iceBall.begin() + i);
			break;
		}
		UPDATE(iceBall[i]);
	}
}
void MonsterManager::Render()
{
	skeleton_body->Render();
	skeletonKnight_body->Render();
	scarecrow_body->Render();
	valkier_body->Render();
	if (LickKing) LickKing->Render();

	for (MonsterBase* skel : skeleton)
		RENDER(skel);
	for (MonsterBase* skel : skeleton_Knight)
		RENDER(skel);
	for (MonsterBase* skel : scarecrow)
		RENDER(skel);
	for (MonsterBase* skel : valkier)
		RENDER(skel);
	for (MonsterBase* skel : iceBall)
		RENDER(skel);
}

void MonsterManager::PostRender()
{
	for (MonsterBase* skel : skeleton)
		skel->PostRender();
	for (MonsterBase* skel : skeleton_Knight)
		skel->PostRender();
	for (MonsterBase* skel : scarecrow)
		skel->PostRender();
	for (MonsterBase* skel : valkier)
		skel->PostRender();
	for (MonsterBase* skel : iceBall)
		skel->PostRender();

	if (LickKing) LickKing->PostRender();
}

void MonsterManager::GUIRender()
{
	//string nowSize = "skeleton count : " + to_string(skeleton.size());
	//ImGui::Text((nowSize).c_str());
}

void MonsterManager::SetTarget(CH_Base_ver2* transform)
{
	targets.push_back(transform);
}

void MonsterManager::SpawnSkeleton(Vector3 pos)
{
	Transform* transform = skeleton_body->Add();
	transform->Scale() *= 0.01f;
	Skeleton* skel = new Skeleton(transform, skeleton_body, skeleton_Count, targets);
	//monsterCollider.push_back(skel->collider);
	skeleton.push_back(skel);
	skeleton[skeleton.size() - 1]->Spawn(pos);
	skeleton_Count++;
}
void MonsterManager::SpawnSkeletonKnight(Vector3 pos)
{
	Transform* transform = skeletonKnight_body->Add();
	transform->Scale() *= 0.02f;
	Skeleton_Knight* skel = new Skeleton_Knight(transform, skeletonKnight_body, skeleton_Night_Count, targets);
	//monsterCollider.push_back(skel->collider);
	skeleton_Knight.push_back(skel);
	skeleton_Knight[skeleton_Knight.size() - 1]->Spawn(pos);
	skeleton_Night_Count++;
}
void MonsterManager::SpawnScarecrow(Vector3 pos)
{
	Transform* transform = scarecrow_body->Add();
	transform->Scale() *= 0.02f;
	Scarecrow* skel = new Scarecrow(transform, scarecrow_body, scarecrow_Count, targets);
	//monsterCollider.push_back(skel->collider);
	scarecrow.push_back(skel);
	scarecrow[scarecrow.size() - 1]->Spawn(pos);
	scarecrow_Count++;
}
void MonsterManager::SpawnVAlkier(Vector3 pos)
{
	Transform* transform = valkier_body->Add();
	transform->Scale() *= 0.02f;
	VAlkier* skel = new VAlkier(transform, valkier_body, Valkier_Count, targets);
	//monsterCollider.push_back(skel->collider);
	valkier.push_back(skel);
	valkier[valkier.size() - 1]->Spawn(pos);
	Valkier_Count++;
}
void MonsterManager::SpawnIceBall(Vector3 pos)
{
	IceBall* skel = new IceBall(targets);
	//monsterCollider.push_back(skel->collider);
	valkier.push_back(skel);
	valkier[valkier.size() - 1]->Spawn(pos);
}
void MonsterManager::SpawnLickKing(Vector3 pos)
{
	LickKing = new Boss_LichKing();
	LickKing->Spawn(pos);
}

MonsterBase* MonsterManager::hitCollision(IN Collider* collider)
{
	float imer = FLT_MAX;
	MonsterBase* imsi = nullptr;
	for (int i = 0; i < skeleton.size(); i++)
	{
		if (collider->IsCollision(skeleton[i]->GetCollider()))
		{
			Vector3 mol = skeleton[i]->GetTransform()->GlobalPos() - collider->GlobalPos();
			
			float imerjer = mol.Length();
			if (imer >= imerjer)
			{
				imer = imerjer;
				imsi = skeleton[i];
			}
		}
	}
	for (int i = 0; i < skeleton_Knight.size(); i++)
	{
		if (collider->IsCollision(skeleton_Knight[i]->GetCollider()))
		{
			Vector3 mol = skeleton_Knight[i]->GetTransform()->GlobalPos() - collider->GlobalPos();

			float imerjer = mol.Length();
			if (imer >= imerjer)
			{
				imer = imerjer;
				imsi = skeleton_Knight[i];
			}
		}
	}
	for (int i = 0; i < scarecrow.size(); i++)
	{
		if (collider->IsCollision(scarecrow[i]->GetCollider()))
		{
			Vector3 mol = scarecrow[i]->GetTransform()->GlobalPos() - collider->GlobalPos();

			float imerjer = mol.Length();
			if (imer >= imerjer)
			{
				imer = imerjer;
				imsi = scarecrow[i];
			}
		}
	}
	for (int i = 0; i < valkier.size(); i++)
	{
		if (collider->IsCollision(valkier[i]->GetCollider()))
		{
			Vector3 mol = valkier[i]->GetTransform()->GlobalPos() - collider->GlobalPos();

			float imerjer = mol.Length();
			if (imer >= imerjer)
			{
				imer = imerjer;
				imsi = valkier[i];
			}
		}
	}
	for (int i = 0; i < iceBall.size(); i++)
	{
		if (collider->IsCollision(iceBall[i]->GetCollider()))
		{
			Vector3 mol = iceBall[i]->GetTransform()->GlobalPos() - collider->GlobalPos();

			float imerjer = mol.Length();
			if (imer >= imerjer)
			{
				imer = imerjer;
				imsi = iceBall[i];
			}
		}
	}
	if (LickKing)
	{
		if (collider->IsCollision(LickKing->GetCollider()))
		{
			Vector3 mol = LickKing->GetTransform()->GlobalPos() - collider->GlobalPos();

			float imerjer = mol.Length();
			if (imer >= imerjer)
			{
				imer = imerjer;
				imsi = LickKing;
			}
		}
	}	

	return imsi;
}