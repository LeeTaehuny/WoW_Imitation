#pragma once
class ParticleSystem
{
    // 파티클 개체의 전반적 설정을 담당하는 범용 클래스
    // -> 일반적인 파티클은 이 클래스로 만들어보고
    //    개별 특수한 파티클이 필요하면 따로 해당 클래스를 더 작성

    // * 파티클 : 영어로 입자, 가루. 프로그래밍에서는 단발적으로 생성되는 2D 혹은 3D 이미지
    //           개별 지속시간이 짧거나, 단기간에 여러 개체가 생성되어야 하는 경우가 많아서
    //           일반적인 2D 이미지(쿼드, 스피드트리) 등과는 관리가 조금 다르다

private:
    //파티클에 필요한 데이터들

    //이 효과가 어디서 진행되는가? = 행렬(공간) 필요
    struct InstanceData
    {
        Matrix transform = XMMatrixIdentity(); // 일반 개체 클래스의 트랜스폼에 대응
    };

    //파티클 자체가 갖는 (다양한) 특수 옵션
    struct ParticleData
    {
        bool isLoop = false; // 무한반복 여부
        bool isAdditive = true; // 이미지의 화소가 이전(배경) 화소와 합쳐지는가? = 연한 투명 효과를 연출할 것인가
        bool isBillboard = true; // 카메라 방향에 상관없이 언제나 같은 형태의 이미지가 보일 것인가?
        UINT count = 100; // 카운트 옵션 : 동시에 생성 가능한 수, 스프라이트 수... 등 다양한 상황에서 쓰인다
        float duration = 1.0f; //이펙트 지속시간
        Vector3 minVelocity = { -1, -1, -1 }; //최소 속력기준(+방향)
        Vector3 maxVelocity = { +1, +1, +1 }; //최대 속력기준(+방향)
        Vector3 minAcceleration; //최소 가속력(속도변화량)
        Vector3 maxAcceleration; //최대 가속력(속도변화량)
        Vector3 minStartScale = { 1, 1, 1 }; //생성시 최소 크기
        Vector3 maxStartScale = { 1, 1, 1 }; //생성시 최대 크기
        Vector3 minEndScale = { 1, 1, 1 }; //재생 종료시 최소 크기
        Vector3 maxEndScale = { 1, 1, 1 }; //재생 종료시 최대 크기
        float minSpeed = 1.0f; // 최소 속력 (실제 움직임)
        float maxSpeed = 3.0f; // 최대 속력 (실제 움직임)
        float minAngularVelocity = -10.0f; // 최소 각도 수정량 (있다면)
        float maxAngularVelocity = +10.0f; // 최대 각도 수정량 (있다면)
        float minStartTime = 0.0f; //최소 지연 시작 시간
        float maxStartTime = 0.0f; //최대 지연 시작 시간
        Float4 startColor = { 1, 1, 1, 1 }; //시작시 색상 보정
        Float4 endColor = { 1, 1, 1, 1 }; //재생 종료시 색상 보정
        // 다른 물리연산, 셰이더 연산, 세부항목 조정 등이 고려되지 않을 때 필요한
        // 최소한의 파티클 옵션을 여기서 지정 가능
    };

    //파티클의 정보
    struct ParticleInfo
    {
        Transform transform;
        Vector3 velocity;
        Vector3 acceleration;
        Vector3 startScale;
        Vector3 endScale;

        float speed = 1.0f;
        float angularVelocity = 0.0f;
        float startTime = 0.0f;

        // 파티클의 정보 구조체 : 일반 정보, 혹은 개별 정보를 담는다
        // 일반 정보일 때 : 파티클의 평균 정보, 개발자가 직접 설계된 내용을 작성, 외부 열람 목적
        // 개별 정보일 때 : 생성된 파티클의 정보를 열람용으로 적는다 (이 구조체로 조작은 힘듬)
        //                 -> 호출하면 현재 만들어진 n번째 폭발 이펙트의 옵션을 확인 가능
    };

public:
    ParticleSystem(string file); //텍스처 없이는 존재할 수 없는 것이 파티클의 운명이므로
    ParticleSystem(wstring file);
    ~ParticleSystem();

    void Update();
    void Render();
    void GUIRender();

    void Play(Vector3 pos, Vector3 rot = Vector3()); // 위치는 필수, 회전은 옵션, 기본값은 {0,0,0}
                                                     // (->기본 출력은 빌보드일 테니까...)
    void Stop();

    bool IsActive() { return quad->Active(); } //이 파티클이 활성화 중인가? -> 사각형에서 변수 참조

private:
    void UpdatePhysical(); //실체를 업데이트하는 함수
    void UpdateColor();    //색깔을 업데이트하는 함수
    void Init();           //기능 시작

    void LoadData(string file); //사전에 지정된 텍스트 설정 파일이 있는 경우
    void LoadData(wstring file); //텍스처의 정보를 사용할 경우

private:
    Quad* quad; //이미지를 담을 사각형

    vector<InstanceData> instances; //만들어질 트랜스폼(생성 결과물)들
    vector<ParticleInfo> particleInfos; //파티클들의 정보 (개별 정보 담기)

    VertexBuffer* instanceBuffer; //인스턴스를 구성하는 정점의 버퍼

    ParticleData data; //이 파티클의 관리 옵션

    float lifeSpan = 0.0f;          // 파티클의 생애주기
    UINT drawCount = 0;             // 출력 요청 횟수
    UINT particleCount = 100;       // 파티클의 설정 카운트

    //이미지 출력을 위한 스테이트
    BlendState* blendState[2];
    DepthStencilState* depthState[2];
};

