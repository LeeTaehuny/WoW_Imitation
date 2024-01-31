#pragma once

class Trail : public GameObject
{
    // 궤적 클래스 : 스프라이트와 유사한 양식을 가지고 있지만, 작동방식이나 목적이 다른 특수 파티클
    // -> 면적이나 길이가 있는 물체의 지나온 경로상의 흔적에 생성되어 움직임의 궤적을 나타내기 위함

public:
    Trail(wstring imageFile, Transform* start, Transform* end, UINT width, float speed);
         // 매개변수 : 그림파일, 궤적 파티클(개별 표시 효과)의 시작점, 종점, 궤적의 크기, 표현 속도
    ~Trail();

    void Update();
    void Render();

private:
    void CreateMesh();

private:
    Mesh<VertexUV>* mesh; // 이미지 출력용 메시

    Transform* start, * end; //시작, 끝 위치 (트랜스폼)

    UINT width; //궤적의 크기
    float speed; //재생하는 속도

    //출력상태 설정용 변수
    RasterizerState* rasterizerState[2];
    BlendState* blendState[2];
};