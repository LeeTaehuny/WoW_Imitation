#include "Framework.h"

// ���� Ŭ���� ȯ�濡�� ���� �������� (=�ؽ�Ʈ ����)
ParticleSystem::ParticleSystem(string file)
{
    LoadData(file); // ���� ������ �ҷ����� �Լ� �������

    //Ʈ������ ������ �غ�
    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //��¿� ������Ʈ�� �غ�
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Alpha(true); //���� ���� (������ ���� ������ ����)

    FOR(2) depthState[i] = new DepthStencilState();
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL); // �������� ����Ʈ
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // �� �������� ����Ʈ

    quad->SetActive(false); // �ϴ� ���� ���� �ƴϾ ��Ȱ��ȭ
}

// �ܺ� Ž���⿡�� ���� �������� (=�׸� ����)
ParticleSystem::ParticleSystem(wstring file)
{
    LoadData(file); // ���� ������ �ҷ����� �Լ� �������

    //Ʈ������ ������ �غ�
    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //��¿� ������Ʈ�� �غ�
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Alpha(true); //���� ���� (������ ���� ������ ����)

    FOR(2) depthState[i] = new DepthStencilState();
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL); // �������� ����Ʈ
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // �� �������� ����Ʈ

    quad->SetActive(false); // �ϴ� ���� ���� �ƴϾ ��Ȱ��ȭ
}

ParticleSystem::~ParticleSystem()
{
    delete quad;
    delete instanceBuffer;
    FOR(2) delete blendState[i];
    FOR(2) delete depthState[i];
}

void ParticleSystem::Update()
{
    if (!quad->Active()) return;

    lifeSpan += DELTA;

    UpdatePhysical(); // ���� ������Ʈ
    UpdateColor();    // ������ ������Ʈ
    quad->UpdateWorld();  //������Ʈ�� ������ �׸��� ���߱� (�׸��� ��ƼŬ�� �°� ������Ʈ)

    if (lifeSpan > data.duration) //������ ����ð��� �����ֱ�(�� ����ð�)�� �ʰ��ϸ�
    {
        if (data.isLoop) Init(); // �ݺ� �ɼ��� ���� ������ �����
        else Stop(); // ���߱�
    }
}

void ParticleSystem::Render()
{
    if (!quad->Active()) return;

    //�ν��Ͻ� �غ�
    instanceBuffer->Set(1);

    //�׸��غ�
    quad->SetRender();

    //������Ʈ �غ�
    blendState[1]->SetState();
    depthState[1]->SetState();

    //�����ġ�� ȣ��
    DC->DrawIndexedInstanced(6, drawCount, 0, 0, 0); // �Ű������� � ������, �󸶳� ����
                                                     // ���, � �߰� ���� �ڷ�� ����� ���ΰ�

    //���󺹱�
    blendState[0]->SetState();
    depthState[0]->SetState();
}

void ParticleSystem::GUIRender()
{
    quad->GUIRender();
}

void ParticleSystem::Play(Vector3 pos, Vector3 rot)
{
    quad->SetActive(true);

    quad->Pos() = pos;
    quad->Rot() = rot;

    Init();
}

void ParticleSystem::Stop()
{
    quad->SetActive(false);
}

//�Ʒ� �� �Լ� = ��ƼŬ (���� ���� ������) ������Ʈ
void ParticleSystem::UpdatePhysical()
{
    drawCount = 0;

    FOR(data.count) //���� ����Ʈ ���
    {
        // * particleInfos[i] : �̸� ������� ��ƼŬ�� ����� ��� ȣ���� ���

        if (lifeSpan < particleInfos[i].startTime) continue;
                // �ֱⰡ ������ ���� = ���۵� �ȵ� ��ƼŬ ��ġ��

        //���� ���� ��ƼŬ ���
        particleInfos[i].velocity += particleInfos[i].acceleration * DELTA; // �ӷ±���
        particleInfos[i].transform.Pos() += particleInfos[i].velocity
            * particleInfos[i].speed * DELTA; // �ӷ±��� * �⺻�ӵ� * �ð���� = �����ӷ�
                                              // �����ӷ��� ��ġ�� ���ؼ� ��ġ ����
        particleInfos[i].transform.Rot().z += particleInfos[i].angularVelocity * DELTA;
                                              // ���� ����

        //������ �ɼ��� Ȱ��ȭ�Ǿ� ������ �׸��� ī�޶� ������ (����ȭ)
        if (data.isBillboard)
        {
            particleInfos[i].transform.Rot().x = CAM->Rot().x;
            particleInfos[i].transform.Rot().y = CAM->Rot().y;
        }
        // ���͸� ���� ������ ������ ���������� -> �׸��� ������ 100% 2D �������� ���δٴ� ������ ����
        // ������Ʈ�� ���̴��� �ᵵ ������ -> ���� ������ �޶����� �� ���� �ִ� (�ɼǿ� ������ ���� �Ͽ�ȭ)

        float t = (lifeSpan - particleInfos[i].startTime)
            / (data.duration - particleInfos[i].startTime); //�ֱ� �� ��� �ð��� (������Ʈ �߿��� �����ֱ�=����ð�)
                                                            //��ƼŬ�� ��ü ��� �ð��� ���� ���۽ð��� ���� ���̸� ����
                                                            //�׿� ���� ��� ����(t)�� ����
                                                            // = ������� ����(0)���� ������� ����(1) ������ ���� ���� ��

        //������ ���� �ð� ��� ������ �̿��ؼ� ũ�� (��쿡 ���� �ٸ� �ɼ��� �ִٸ� �װ͵�) ����
        particleInfos[i].transform.Scale() =
            Lerp(particleInfos[i].startScale, particleInfos[i].endScale, t);

        //��ġ, ȸ��, ũ�� ���� ���� ���� ��� ���� ������Ʈ
        particleInfos[i].transform.UpdateWorld();

        //������Ʈ�� ������ ��ƼŬ�� ���� ����
        instances[drawCount++].transform = //drawCount�� ȣ���� ��, ������ ������ ������ +1 (�������� Ȱ�� �ļ�)
            XMMatrixTranspose(particleInfos[i].transform.GetWorld());
    }

    // ������� ���� �� ��ƼŬ�� ���� ���� ������ ��� ������ �ȴ�
    // -> �̿� ���� ���۸� ������Ʈ
    instanceBuffer->Update(instances.data(), drawCount);// ��� ������ �� �� ������Ʈ�� ���ΰ�
}

void ParticleSystem::UpdateColor()
{
    // ���� ������Ʈ ���� �������� �̹� ��ƼŬ�� �������, ��������(��������) ������ ������ ��
    // -> ���� �� �׷��ٸ� ���ʿ��� �ٽ� �� ������ �� ����� ���� ��
    // -> ������ �������� ������ ���⼭ �� �� �ʿ�� ����. ��� �ű⼭ ���� �� ä����� �Ѵ�

    float t = lifeSpan / data.duration; // ����ð� ������ ������ ����ð�(�Ϲݰ�)

    //��ٷ� Ȱ��
    Float4 color;
    color.x = Lerp(data.startColor.x, data.endColor.x, t); // R
    color.y = Lerp(data.startColor.y, data.endColor.y, t); // G
    color.z = Lerp(data.startColor.z, data.endColor.z, t); // B
    color.w = Lerp(data.startColor.w, data.endColor.w, t); // A

    //���忡�� ����
    quad->GetMaterial()->GetData().diffuse = color;
}

void ParticleSystem::Init()
{
    // ���� ��ƼŬ�� �����ϱ�

    // �׸��� ������ ȥ�������ΰ�(additive) �ƴϸ� �׳� �ܵ� ���İ� �ִ� �ǰ�(���� �ִ� ������)
    // ->�ɼǿ� ���� ������Ʈ ���� �ѹ� �� Ȯ�λ��
    if (data.isAdditive) blendState[1]->Additive(); //ȥ�տ� ���� ���� Ȱ��ȭ
    else blendState[1]->Alpha(true);                //���İ� �ִ� ������ Ȱ��ȭ
                                                    //->�߰��� �ɼ��� �ٲ�� ��츦 ���ؼ�

    lifeSpan = 0; //�ֱ�(�� ��� �ð�) 0
    drawCount = 0; //��ο� ��û Ƚ�� 0
    data.count = particleCount; //������ ��� (���� �ɼ��� �޶����� �� �ڵ嵵 ���� �ʿ�)

    // ���� �ٽ� ����
    instances.resize(data.count);
    particleInfos.resize(data.count); //���� ��ƼŬ ����

    //�Ʒ� �ڵ�� ���� : ���� ��ƼŬ ������ �ְ�, ���� �������ٰ� ����
    // -> �ó������� �ٲ�� �� �ڵ�� �����ǰų�, �ٸ� ������ ���� ȣ��Ǿ�� �Ѵ�
    for (ParticleInfo& info : particleInfos) //���� ���� ���� ���� Ȱ��
    {
        info.transform.Pos() = {}; //�ϴ� ��� ����. Ʈ�������� �ֱ�� ����

        //��ƼŬ�μ��� �ɼ� ����
        info.velocity = Random(data.minVelocity, data.maxVelocity);
        info.acceleration = Random(data.minAcceleration, data.maxAcceleration);
        info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        info.speed = Random(data.minSpeed, data.maxSpeed);
        info.startTime = Random(data.minStartTime, data.maxStartTime);
        info.startScale = Random(data.minStartScale, data.maxStartScale);
        info.endScale = Random(data.minEndScale, data.maxEndScale);

        //��ƼŬ���� �ӷ��� ����ȭ�Ѵٸ� �Ʒ� �ڵ����
        info.velocity.Normalize();
    }
    //�� �ݺ����� ������ ������ ���� �� ���� ��ƼŬ�� ���� �ٸ� ������ ����
    //->���߿� �� �������� �ٸ� ��ƼŬ�� �θ��⸸ �ص� �پ��� ������ ���� ��ƼŬ ���� ����
    //-> �̸� ��ƼŬ�� ����� ����ȭ���� ������ �ǰ�, ����� ���� ������Դ� ū ��̸� ���� ���Ѵ�
}

void ParticleSystem::LoadData(string file)
{
    //������ ������ ����(�ؽ�Ʈ ����, ini ��)�� �ִٰ� ġ�� �ű⼭ �ڷ� �ҷ�����

    //���� �б� �غ�
    BinaryReader* reader = new BinaryReader(file);

    //���� ���� ���Ͽ��� ���� �̸��� �����ؼ� �׸� �����
    wstring tFile = reader->WString();
    quad = new Quad(Vector2(1, 1));
    quad->GetMaterial()->SetDiffuseMap(tFile);
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl");

    //������ ������ ��ƼŬ �ɼ� �ҷ��ͼ� �����ϱ�
    // -> �ؽ�Ʈ ������� Ȱ���ؼ� �츮�� ������ ���� ���� �ְ� (�׷��� ���� ���� ������ ���� �ְ�)
    // -> ���� ��ƼŬ�̸� ���� ������� ������ ������ �ɼ��� �ּ������� ������ �Ǳ� ������ ���⼭
    //    ������ �о �ٷ� �ɼ� ������ �����ϴ�

    ParticleData* pData = new ParticleData();
    reader->Byte((void**)&pData, sizeof(ParticleData));
    data = *pData;

    //���� ����
    instances.resize(data.count);
    particleInfos.resize(data.count);

    delete reader;
}

void ParticleSystem::LoadData(wstring file)
{
    //�׸� �����
    quad = new Quad(Vector2(1, 1)); // ������ ���ذ�. ���⼭ �ٲ㵵 ������,
                                    // ������ �ɼǿ��� �����ϴ� ���� ����

    quad->GetMaterial()->SetDiffuseMap(file); // �׸� ���� �ҷ�����
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl"); // �⺻ �ؽ�ó Ȥ�� ���� ���̴�

    //���� ����Ʈ, ���� �ν��Ͻ��� ����ؼ� ���� ����(��������)
    instances.resize(data.count);
    
    //���� �ν��Ͻ� ������ �ʿ��ϴٸ� ���� ���͵� ����
    particleInfos.resize(data.count);

    // ������� ����� �׸��� ���� ����(��ƼŬ �⺻ �׸�) �� �⺻ �����ʹ� ���� ��
    // ���� �ɼ��� �����ϰ�... (data ����ü�� �����ϰ�)
    // �ű⿡ �ִ� count�� ���� �� ���� ���� 2���� �ٽ� ��������� �Ѵ�

    // -> �ٸ� �� LoadData �Լ��� �����ϸ� �Ƹ� ���� ���� ������ ���� ���� ���� ��.
}
