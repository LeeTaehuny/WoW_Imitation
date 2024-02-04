#include "Framework.h"
#include "IceEdges.h"

IceEdges::IceEdges()
{
    IceBreak = new Model("IceBreak");

    Edge1 = new Model("IceEdge1");
    Edge2 = new Model("IceEdge2");
    Edge3 = new Model("IceEdge3");
    Edge4 = new Model("IceEdge4");


    debris1 = new Model("Ice_debris1");
    debris2 = new Model("Ice_debris2");
    debris3 = new Model("Ice_debris3");
    debris4 = new Model("Ice_debris4");

    debris1->Pos().y = 295.0f;
    debris2->Pos().y = 295.0f;
    debris3->Pos().y = 295.0f;
    debris4->Pos().y = 295.0f;


    Edge1->SetActive(false);
    Edge2->SetActive(false);
    Edge3->SetActive(false);
    Edge4->SetActive(false);

    debris1->SetActive(false);
    debris2->SetActive(false);
    debris3->SetActive(false);
    debris4->SetActive(false);
}

IceEdges::~IceEdges()
{
    delete Edge1;
    delete Edge2;
    delete Edge3;
    delete Edge4;

    delete debris1;
    delete debris2;
    delete debris3;
    delete debris4;
}

void IceEdges::Update()
{
    if (Edge1->Pos().y > -150.0f && Falling)
    {
        IceBreak->UpdateWorld();

        Edge1->Pos().y -= 100 * DELTA;
        Edge2->Pos().y -= 100 * DELTA;
        Edge3->Pos().y -= 100 * DELTA;
        Edge4->Pos().y -= 100 * DELTA;

        debris1->Pos().y -= 50 * DELTA;
        debris2->Pos().y -= 50 * DELTA;
        debris3->Pos().y -= 50 * DELTA;
        debris4->Pos().y -= 50 * DELTA;
    }
    if (Edge1->Pos().y <= -150.0f)
    {
        Falling = false;
    }


    Edge1->UpdateWorld();
    Edge2->UpdateWorld();
    Edge3->UpdateWorld();
    Edge4->UpdateWorld();
    
    debris1->UpdateWorld();
    debris2->UpdateWorld();
    debris3->UpdateWorld();
    debris4->UpdateWorld();
}

void IceEdges::Render()
{
    if(Edge1->Pos().y > -150.0f)
    {   
        IceBreak->Render();

        Edge1->Render();
        Edge2->Render();
        Edge3->Render();
        Edge4->Render();

        debris1->Render();
        debris2->Render();
        debris3->Render();
        debris4->Render();
    }
}

void IceEdges::ZeroSet()
{
    Edge1->Pos().y = 0;
    Edge2->Pos().y = 0;
    Edge3->Pos().y = 0;
    Edge4->Pos().y = 0;

    debris1->Pos().y = 295.0f;
    debris2->Pos().y = 295.0f;
    debris3->Pos().y = 295.0f;
    debris4->Pos().y = 295.0f;

    Falling = true;
}
