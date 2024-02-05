#include "Framework.h"
#include "FireBall.h"

FireBall::FireBall()
	: TargetSkill(BB)
{
	myCollider = new SphereCollider();
	myCollider->SetActive(false);
	particle = new Rain();
}
FireBall::~FireBall()
{

}

void FireBall::Update()
{
	Target();

	if (myCollider->Active())
	{
		particle->Play(myCollider->Pos());
	}

	particle->Update();
	myCollider->UpdateWorld();
}
void FireBall::Render()
{
	particle->Render();
	myCollider->Render();
}

void FireBall::UseSkill(Vector3 pos)
{
	myCollider->SetActive(true);
	myCollider->Pos() = pos;
}