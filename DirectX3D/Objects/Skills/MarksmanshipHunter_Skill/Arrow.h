#pragma once
class Arrow : public Transform
{
public:
	Arrow(Transform* transform);
	~Arrow();

	void Update();

	// ���� �� ȭ���� ����������� Ȯ���ϱ� ���� ����
	bool GetIsRun() { return isRun; }
	// ȭ���� ��� ���¸� �����ϱ� ���� ����
	void SetIsRun(bool cam) { this->isRun = cam; }

private:
	bool isRun;
};