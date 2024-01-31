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
         //↑ 정점 버퍼와 소수 버퍼를 하나로 합치고, 날씨에 쓸 수 있도록 이름을 다시 부여한 버퍼
         //  * 나중에 다른 개발을 할 때도, 있는 버퍼 데이터를 조합해서 다른 버퍼를 만들려면 만들면 된다
         //  정점 버퍼는 그림을 출력하기 위한 것
    vector<VertexUV> vertices; //그림용 정점 (그림을 연산하기 위한 것)

};

