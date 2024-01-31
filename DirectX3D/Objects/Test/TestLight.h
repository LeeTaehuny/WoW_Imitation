#pragma once
class TestLight : public Transform
{
public:
    TestLight();
    ~TestLight();

    void Update();
    LightBuffer::Light* GetLight() { return light; }

private:

    LightBuffer::Light* light;
    

};

