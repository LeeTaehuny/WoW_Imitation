#include "Framework.h"

// 내부 클래스 환경에서 파일 가져오기 (=텍스트 설정)
ParticleSystem::ParticleSystem(string file)
{
    LoadData(file); // 파일 데이터 불러오기 함수 끌어오기

    //트랜스폼 데이터 준비
    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //출력용 스테이트값 준비
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Alpha(true); //알파 적용 (반투명 설정 있으면 적용)

    FOR(2) depthState[i] = new DepthStencilState();
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL); // 가려지는 이펙트
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // 안 가려지는 이펙트

    quad->SetActive(false); // 일단 터질 때가 아니어서 비활성화
}

// 외부 탐색기에서 파일 가져오기 (=그림 파일)
ParticleSystem::ParticleSystem(wstring file)
{
    LoadData(file); // 파일 데이터 불러오기 함수 끌어오기

    //트랜스폼 데이터 준비
    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), data.count);

    //출력용 스테이트값 준비
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->Alpha(true); //알파 적용 (반투명 설정 있으면 적용)

    FOR(2) depthState[i] = new DepthStencilState();
    //depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ALL); // 가려지는 이펙트
    depthState[1]->DepthWriteMask(D3D11_DEPTH_WRITE_MASK_ZERO); // 안 가려지는 이펙트

    quad->SetActive(false); // 일단 터질 때가 아니어서 비활성화
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

    UpdatePhysical(); // 정점 업데이트
    UpdateColor();    // 색깔을 업데이트
    quad->UpdateWorld();  //업데이트된 정보에 그림을 맞추기 (그림을 파티클에 맞게 업데이트)

    if (lifeSpan > data.duration) //설정된 재생시간을 생애주기(중 경과시간)가 초과하면
    {
        if (data.isLoop) Init(); // 반복 옵션이 켜져 있으면 재시작
        else Stop(); // 멈추기
    }
}

void ParticleSystem::Render()
{
    if (!quad->Active()) return;

    //인스턴스 준비
    instanceBuffer->Set(1);

    //그림준비
    quad->SetRender();

    //스테이트 준비
    blendState[1]->SetState();
    depthState[1]->SetState();

    //출력장치로 호출
    DC->DrawIndexedInstanced(6, drawCount, 0, 0, 0); // 매개변수는 어떤 단위를, 얼마나 많이
                                                     // 어디서, 어떤 추가 참조 자료로 출력할 것인가

    //원상복구
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

//아래 두 함수 = 파티클 (개별 내부 데이터) 업데이트
void ParticleSystem::UpdatePhysical()
{
    drawCount = 0;

    FOR(data.count) //동시 이펙트 고려
    {
        // * particleInfos[i] : 미리 만들어진 파티클을 사용할 경우 호출할 대상

        if (lifeSpan < particleInfos[i].startTime) continue;
                // 주기가 오지도 않은 = 시작도 안된 파티클 제치기

        //진행 중인 파티클 계산
        particleInfos[i].velocity += particleInfos[i].acceleration * DELTA; // 속력기준
        particleInfos[i].transform.Pos() += particleInfos[i].velocity
            * particleInfos[i].speed * DELTA; // 속력기준 * 기본속도 * 시간경과 = 최종속력
                                              // 최종속력을 위치에 더해서 위치 갱신
        particleInfos[i].transform.Rot().z += particleInfos[i].angularVelocity * DELTA;
                                              // 각도 갱신

        //빌보드 옵션이 활성화되어 있으면 그림을 카메라 쪽으로 (동기화)
        if (data.isBillboard)
        {
            particleInfos[i].transform.Rot().x = CAM->Rot().x;
            particleInfos[i].transform.Rot().y = CAM->Rot().y;
        }
        // 벡터를 쓰면 연산은 빠르고 간단하지만 -> 그림이 언제나 100% 2D 정면으로 보인다는 보장은 없다
        // 지오메트리 셰이더를 써도 되지만 -> 렌더 절차가 달라져야 할 수도 있다 (옵션에 무관한 렌더 일원화)

        float t = (lifeSpan - particleInfos[i].startTime)
            / (data.duration - particleInfos[i].startTime); //주기 중 경과 시간과 (업데이트 중에는 생애주기=경과시간)
                                                            //파티클의 전체 재생 시간을 각각 시작시간에 대해 차이를 내고
                                                            //그에 따른 경과 비율(t)을 낸다
                                                            // = 만들어진 직후(0)부터 사라지기 직전(1) 사이의 값이 나올 것

        //위에서 만든 시간 경과 비율을 이용해서 크기 (경우에 따라 다른 옵션이 있다면 그것도) 보간
        particleInfos[i].transform.Scale() =
            Lerp(particleInfos[i].startScale, particleInfos[i].endScale, t);

        //위치, 회전, 크기 값이 각각 나온 대로 정점 업데이트
        particleInfos[i].transform.UpdateWorld();

        //업데이트된 정점을 파티클에 직접 적용
        instances[drawCount++].transform = //drawCount를 호출한 후, 연산이 끝나면 변수에 +1 (누적연산 활용 꼼수)
            XMMatrixTranspose(particleInfos[i].transform.GetWorld());
    }

    // 여기까지 오면 각 파티클에 대한 정점 정보가 모두 갱신이 된다
    // -> 이에 따라 버퍼를 업데이트
    instanceBuffer->Update(instances.data(), drawCount);// 어느 범위를 몇 번 업데이트할 것인가
}

void ParticleSystem::UpdateColor()
{
    // 정점 업데이트 진행 과정에서 이미 파티클의 재생여부, 정점정보(존재정보) 연산을 거쳤을 것
    // -> 만약 안 그랬다면 이쪽에서 다시 그 과정을 다 해줘야 맞을 것
    // -> 한쪽이 진행해준 연산을 여기서 또 할 필요는 없다. 대신 거기서 빠진 걸 채워줘야 한다

    float t = lifeSpan / data.duration; // 경과시간 나누기 본래의 재생시간(일반값)

    //곧바로 활용
    Float4 color;
    color.x = Lerp(data.startColor.x, data.endColor.x, t); // R
    color.y = Lerp(data.startColor.y, data.endColor.y, t); // G
    color.z = Lerp(data.startColor.z, data.endColor.z, t); // B
    color.w = Lerp(data.startColor.w, data.endColor.w, t); // A

    //쿼드에도 적용
    quad->GetMaterial()->GetData().diffuse = color;
}

void ParticleSystem::Init()
{
    // 만든 파티클을 시작하기

    // 그림의 성격이 혼합투명인가(additive) 아니면 그냥 단독 알파가 있는 건가(알파 있는 불투명)
    // ->옵션에 따라 스테이트 값을 한번 더 확인사살
    if (data.isAdditive) blendState[1]->Additive(); //혼합에 의한 투명 활성화
    else blendState[1]->Alpha(true);                //알파가 있는 불투명 활성화
                                                    //->중간에 옵션이 바뀌는 경우를 위해서

    lifeSpan = 0; //주기(중 경과 시간) 0
    drawCount = 0; //드로우 요청 횟수 0
    data.count = particleCount; //설정된 대로 (이후 옵션이 달라지면 이 코드도 수정 필요)

    // 벡터 다시 리셋
    instances.resize(data.count);
    particleInfos.resize(data.count); //개별 파티클 정보

    //아래 코드는 샘플 : 개별 파티클 정보가 있고, 지금 정해진다고 가정
    // -> 시나리오가 바뀌면 이 코드는 수정되거나, 다른 곳에서 따로 호출되어야 한다
    for (ParticleInfo& info : particleInfos) //위의 개별 정보 벡터 활용
    {
        info.transform.Pos() = {}; //일단 대기 상태. 트랜스폼이 있기는 있음

        //파티클로서의 옵션 설정
        info.velocity = Random(data.minVelocity, data.maxVelocity);
        info.acceleration = Random(data.minAcceleration, data.maxAcceleration);
        info.angularVelocity = Random(data.minAngularVelocity, data.maxAngularVelocity);
        info.speed = Random(data.minSpeed, data.maxSpeed);
        info.startTime = Random(data.minStartTime, data.maxStartTime);
        info.startScale = Random(data.minStartScale, data.maxStartScale);
        info.endScale = Random(data.minEndScale, data.maxEndScale);

        //파티클에서 속력을 정규화한다면 아래 코드까지
        info.velocity.Normalize();
    }
    //이 반복문이 끝나면 개수에 따른 각 개별 파티클에 각자 다른 설정값 대입
    //->나중에 이 설정값이 다른 파티클을 부르기만 해도 다양한 느낌이 나는 파티클 구현 가능
    //-> 미리 파티클을 만들면 최적화에는 도움이 되고, 눈썰미 좋은 사람에게는 큰 흥미를 주지 못한다
}

void ParticleSystem::LoadData(string file)
{
    //사전에 설정된 파일(텍스트 파일, ini 등)이 있다고 치고 거기서 자료 불러오기

    //파일 읽기 준비
    BinaryReader* reader = new BinaryReader(file);

    //사전 설정 파일에서 파일 이름을 추출해서 그림 만들기
    wstring tFile = reader->WString();
    quad = new Quad(Vector2(1, 1));
    quad->GetMaterial()->SetDiffuseMap(tFile);
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl");

    //사전에 설정된 파티클 옵션 불러와서 설정하기
    // -> 텍스트 입출력을 활용해서 우리가 사전에 만들 수도 있고 (그렇게 만든 것을 가져올 수도 있고)
    // -> 보통 파티클이면 지금 헤더에서 구현된 정도의 옵션은 최소한으로 가지게 되기 때문에 여기서
    //    파일을 읽어서 바로 옵션 적용이 가능하다

    ParticleData* pData = new ParticleData();
    reader->Byte((void**)&pData, sizeof(ParticleData));
    data = *pData;

    //벡터 리셋
    instances.resize(data.count);
    particleInfos.resize(data.count);

    delete reader;
}

void ParticleSystem::LoadData(wstring file)
{
    //그림 만들기
    quad = new Quad(Vector2(1, 1)); // 설정은 기준값. 여기서 바꿔도 되지만,
                                    // 어차피 옵션에서 설정하는 편이 낫다

    quad->GetMaterial()->SetDiffuseMap(file); // 그림 파일 불러오기
    quad->GetMaterial()->SetShader(L"Effect/Particle.hlsl"); // 기본 텍스처 혹은 맞춤 셰이더

    //같은 이펙트, 복수 인스턴스에 대비해서 벡터 리셋(리사이즈)
    instances.resize(data.count);
    
    //개별 인스턴스 정보가 필요하다면 정보 벡터도 리셋
    particleInfos.resize(data.count);

    // 여기까지 만들면 그림에 의한 쿼드(파티클 기본 그림) 및 기본 데이터는 형성 끝
    // 이후 옵션을 설정하고... (data 구조체를 설정하고)
    // 거기에 있는 count에 따라 위 벡터 리셋 2줄을 다시 수행해줘야 한다

    // -> 다른 쪽 LoadData 함수를 응용하면 아마 전용 설정 파일을 만들 수도 있을 것.
}
