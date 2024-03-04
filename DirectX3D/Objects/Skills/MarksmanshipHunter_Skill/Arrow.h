#pragma once
class Arrow : public Transform
{
public:
	Arrow(Transform* transform);
	~Arrow();

	void Update();

	// 현재 이 화살이 사용중인지를 확인하기 위한 겟터
	bool GetIsRun() { return isRun; }
	// 화살의 사용 상태를 변경하기 위한 셋터
	void SetIsRun(bool cam) { this->isRun = cam; }

private:
	bool isRun;
};