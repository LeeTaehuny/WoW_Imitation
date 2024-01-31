#pragma once

class Crowbar : public Model
{
    //Crowbar : ³ë·ç¹ß¸ø»ÌÀÌ, ¼èÁö·¿´ë.

public:
    Crowbar();
    ~Crowbar();

    void Update();
    void Render();
    void GUIRender();

private:
    BoxCollider* collider;

};

