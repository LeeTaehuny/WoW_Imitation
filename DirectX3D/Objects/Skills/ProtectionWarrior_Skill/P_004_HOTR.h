#pragma once
class P_004_HOTR : public ActiveSkill
{
public:
	P_004_HOTR();
	~P_004_HOTR();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill() {}
	virtual void UseSkill(Collider* targetCollider) override;
	virtual void UseSkill(Vector3 direction) {}

private:
	Transform* root;
	Quad* holy_wave; // 파동 이미지를 구현하기 위한 쿼드

	BlendState* blendState[2];
};