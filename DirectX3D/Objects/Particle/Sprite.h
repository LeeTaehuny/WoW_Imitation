#pragma once
class Sprite : public Particle
{
    // 스프라이트 : 애니메이션을 구성하기 위한 프레임을 같은 크기로 나열한 큰 아틀라스
    // 아틀라스 : 세계지도, 혹은 여러 장의 그림을 하나의 파일로 묶은 이미지 데이터

    // -> 스프라이트 파티클 : 애니메이션으로 만든 파티클

private:

    class SpriteBuffer : public ConstBuffer
    {
    private:
        struct Data
        {
            Vector2 maxFrame;
            Vector2 curFrame;
        };
        Data data;
    public:
        SpriteBuffer() : ConstBuffer(&data, sizeof(Data)){}
        Data& Get() { return data; }
    };

public:
    Sprite(wstring imageFile,           //이미지 파일
            float width,                //그림의 가로
            float height,               //그림의 세로
            UINT frameCol,              //프레임의 열(...의 개수, 가로 개수)
            UINT frameRow,              //프레임의 행(...의 개수, 세로 개수)
            bool isAdditive = false);   //혼합 투명인가?
    ~Sprite();

    void Update();
    void Render();
    void GUIRender();

    void Play(Vector3 pos);

private:
    void Create();

private:
    float time = 0;
    float speed = 1;
    UINT curFrameCount = 0;
    UINT maxFrameCount = 0;
    Vector2 size;

    SpriteBuffer* buffer;
    VertexUV vertex;
};

