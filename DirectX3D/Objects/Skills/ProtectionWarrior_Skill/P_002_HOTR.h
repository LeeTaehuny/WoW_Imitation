#pragma once
class P_002_HOTR : public ActiveSkill
{
public:
	P_002_HOTR();
	~P_002_HOTR();

	virtual void Update() override;
	virtual void Render() override;
	virtual void UseSkill(MonsterBase* monsterbase) override;

private:
	Transform* root;
	Quad* holy_wave; // 파동 이미지를 구현하기 위한 쿼드

	MonsterBase* targetMonster;

	BlendState* blendState[2];
};