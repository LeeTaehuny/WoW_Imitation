#pragma once
class Arrow : public Transform
{
public:
	Arrow(Transform* transform);
	~Arrow();

	void Update();

	bool GetIsRun() { return isRun; }
	void SetIsRun(bool cam) { this->isRun = cam; }

private:
	bool isRun;


};