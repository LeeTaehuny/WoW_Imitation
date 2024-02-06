#include "Framework.h"
#include "FireBall.h"

FireBall::FireBall()
	: TargetSkill(BB)
{
	myCollider = new SphereCollider();
	myCollider->SetActive(false);

	prevSkills.push_back("");
}
FireBall::~FireBall()
{

}

void FireBall::Update()
{
	Target();

	myCollider->UpdateWorld();
}
void FireBall::Render()
{
	myCollider->Render();
}

void FireBall::UseSkill(Vector3 pos)
{
	myCollider->SetActive(true);
	myCollider->Pos() = pos;
}