#pragma once

class Crowbar : public Model
{
    //Crowbar : ���߸�����, ��������.

public:
    Crowbar();
    ~Crowbar();

    void Update();
    void Render();
    void GUIRender();

private:
    BoxCollider* collider;

};

