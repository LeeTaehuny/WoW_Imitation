#include "Framework.h"

Target::Target(Type type) : TargetSkill(AA)
{
	myCollider = new SphereCollider(1);
	myCollider->SetActive(false);
}

Target::~Target()
{

}