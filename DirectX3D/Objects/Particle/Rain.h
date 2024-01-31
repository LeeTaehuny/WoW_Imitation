#pragma once

class Rain : public Particle
{
public:
    Rain();
    ~Rain();

    virtual void Update() override;
    virtual void Render() override;
    virtual void GUIRender() override;

private:
    void Create();

private:
    WeatherBuffer* buffer;
         //�� ���� ���ۿ� �Ҽ� ���۸� �ϳ��� ��ġ��, ������ �� �� �ֵ��� �̸��� �ٽ� �ο��� ����
         //  * ���߿� �ٸ� ������ �� ����, �ִ� ���� �����͸� �����ؼ� �ٸ� ���۸� ������� ����� �ȴ�
         //  ���� ���۴� �׸��� ����ϱ� ���� ��
    vector<VertexUV> vertices; //�׸��� ���� (�׸��� �����ϱ� ���� ��)

};

