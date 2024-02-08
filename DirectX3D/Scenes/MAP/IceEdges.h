#pragma once
class IceEdges : public Transform
{
public:
    IceEdges();
    ~IceEdges();

    void Update();
    void Render();

    void ZeroSet();
  
private:
    Model* IceBreak;

    Model* Edge1;
    Model* Edge2;
    Model* Edge3;
    Model* Edge4;

    Model* debris1;
    Model* debris2;
    Model* debris3;
    Model* debris4;


    bool Falling = true;

    //Collider
    Cylinder* Ground_Collider;
};

