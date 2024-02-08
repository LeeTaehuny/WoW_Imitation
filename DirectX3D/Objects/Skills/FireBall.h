#pragma once
#include "Objects/Skills/Base/ActiveSkill.h"

class FireBall : public ActiveSkill
{
public:
	FireBall();
	virtual ~FireBall() override;

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(Collider* targetCollider);
	virtual void UseSkill(Vector3 direction) {}

private:

};