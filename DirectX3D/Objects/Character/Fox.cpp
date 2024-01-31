#include "Framework.h"

Fox::Fox() : ModelAnimator("Fox")
{
    ReadClip("Idle");
    ReadClip("Run", 0, "FoxTransform"); // �� ���Ͽ� �ִ� ���븦 �������� ����

    PlayClip(curState); // ���� ���¿� ���� ���� 1ȸ ȣ��
}

Fox::~Fox()
{
}

void Fox::Update()
{
    //ĳ���� ���� 3�� ȣ��
    Control();
    Move();
    Rotate();

    ModelAnimator::Update();
}

void Fox::Render()
{
    ModelAnimator::Render();
}

void Fox::Control()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        destPos = terrain->Pick(); // ���� �������� �������� ã�Ƴ���

        if (aStar->IsCollisionObstacle(GlobalPos(), destPos)) //�����Ÿ��� ��ֹ��� ���̸�
        {
            SetPath(); // ��ֹ��� ��ġ(��λ� ��� ��ֹ�����) ã�Ƴ� ���� �ش� �κ��� ���ư��� ��� ��� ����
        }
        else //��ֹ��� ������
        {
            path.clear(); //��δ� ���ǹ��ϴϱ� �� ���ְ�
            path.push_back(destPos); //���� ������ �ϳ��� ����� = �������� Move() �Լ��� �����ϸ�
        }
    }

}

void Fox::Move()
{
    if (path.empty()) //��ΰ� ������ = �������� ���� ������
    {
        SetState(IDLE);
        return; //�������� �ʱ�
    }

    SetState(RUN); // �̵� ���ۿ� ���� �����̱� ����

    // ���ͷ� ���� ��θ� �ϳ��� ã�ư��鼭 �����̱�

    Vector3 dest = path.back(); // ���� �������κκ��� ���۵� "��"�� ������
                                // = �������� ���� ���� "������" �ܱ� ������

    Vector3 direction = dest - GlobalPos(); // �� ��ġ���� ������ �������� ���� ���� ����

    direction.y = 0; //�¿��̵� ���ַ� �� �Ŷ� ���̴� ������� ����

    if (direction.Length() < 0.5f) // ���� �� �� �� ������
    {
        path.pop_back(); // �� �� �������� ���Ϳ��� ���� (üũ����Ʈ üũ)
    }

    //�������� ���� ���� �������� �̵�
    velocity = direction.GetNormalized();
    Pos() += velocity * moveSpeed * DELTA;
}

void Fox::Rotate()
{
    if (curState == IDLE) return; //�̵� ���� �ƴ� ���� ȸ�� ����

    Vector3 forward = Forward(); //���� �� ������
    Vector3 cross = Cross(forward, velocity); //�� �հ� ���� �� �擇���� ���� ����

    if (cross.y < 0) //�� ��꿡 ���� ������ ���̸� = ���� ���������� �������� ���� ���̴�
        Rot().y += rotSpeed * DELTA; // ���� ȸ��
    else if (cross.y > 0) //���� �ݴ�
        Rot().y -= rotSpeed * DELTA; //������ ȸ��
}

void Fox::SetState(State state) //ȣ���� �̰� �ϳ��θ�
{
    if (state == curState) return;

    curState = state; //���¸� �������ְ�
    PlayClip(state);  //����� ���¿� ���� �ִϸ��̼� ���
}

void Fox::SetPath()
{
    int startIndex = aStar->FindCloseNode(GlobalPos()); // ���찡 �ִ� ��尡 ���� �ε���
    int endIndex = aStar->FindCloseNode(destPos); //���� �������� ���� ����� ��尡 ��

    aStar->GetPath(startIndex, endIndex, path); // ����, �� �ε����� A* ��ã�⿡ �����ϰ�,
                                                // ����� path�� ����
    aStar->MakeDirectionPath(GlobalPos(), destPos, path); // �߰��� ��ֹ��� ������ �ش� �κе�
                                                          // path�� �ݿ�

    UINT pathSize = path.size(); //ó�� ���� ũ�� �ޱ�

    while (path.size() > 2) // ���� ���� ã�ư��鼭 ���� ��� ���� 2 ���ϰ� �� ������ �Ʒ� �ݺ�
    {
        vector<Vector3> tempPath = path; // ���� �ӽ� ��� �޾ƿ���
        tempPath.erase(tempPath.begin()); // ���� �������� �ϴ� ���� �� �� (������ �߰� ��ΰ� �־)
        tempPath.pop_back(); //���� ��ο��� ���� ���̴ϱ� ���� ��ġ�� ���� �� �� (������ "������ ��"�̾)

        Vector3 start = path.back(); //���ο� ������
        Vector3 end = path.front(); //���ο� ��

        aStar->MakeDirectionPath(start, end, tempPath); // ��ֹ� ���θ� �߰����� �ٽ� ������
        
        //������ ��� �ٽ� ���ݿ�
        path.clear();
        path = tempPath;

        //���ο� ���۰� ���� ��ο� �ֱ�
        path.insert(path.begin(), end);
        path.push_back(start);

        if (pathSize == path.size()) //������ ���Ϳ� ���ؼ� ��� ũ�Ⱑ ������
            break;
        else
            pathSize = path.size(); //��ΰ� �پ� ������ �پ�� ��θ� �ݿ�
    }

    //��ֹ� ���ο� ���� �������� ��ο� ���� �������� �ִ´�
    path.insert(path.begin(), destPos);
}
