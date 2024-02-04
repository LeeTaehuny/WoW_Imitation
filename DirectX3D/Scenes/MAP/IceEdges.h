#pragma once
class IceEdges : public Transform
{
public:
    IceEdges();
    ~IceEdges();

    void Update();
    void Render();

    void ZeroSet();
    void Fall();
  
private:
    Model* IceBreak;
    Model* Edge1;
    Model* Edge2;
    Model* Edge3;
    Model* Edge4;

    bool Falling = true;

    //Collider
    Cylinder* Ground_Collider;
};

