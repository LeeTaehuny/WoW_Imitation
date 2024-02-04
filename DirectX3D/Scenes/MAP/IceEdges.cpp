#include "Framework.h"
#include "IceEdges.h"

IceEdges::IceEdges()
{
    IceBreak = new Model("IceBreak");

    Edge1 = new Model("IceEdge1");
    Edge2 = new Model("IceEdge2");
    Edge3 = new Model("IceEdge3");
    Edge4 = new Model("IceEdge4");
}

IceEdges::~IceEdges()
{
    delete Edge1;
    delete Edge2;
    delete Edge3;
    delete Edge4;
}

void IceEdges::Update()
{
    if (Edge1->Pos().y > -150.0f)
    {
        IceBreak->UpdateWorld();

        Edge1->Pos().y -= 100 * DELTA;
        Edge2->Pos().y -= 100 * DELTA;
        Edge3->Pos().y -= 100 * DELTA;
        Edge4->Pos().y -= 100 * DELTA;


        Edge1->UpdateWorld();
        Edge2->UpdateWorld();
        Edge3->UpdateWorld();
        Edge4->UpdateWorld();
    }
    if (Edge1->Pos().y <= -150.0f)
    {
        Edge1->SetActive(false);
        Edge2->SetActive(false);
        Edge3->SetActive(false);
        Edge4->SetActive(false);

        Edge1->Pos().y = 0;
        Edge2->Pos().y = 0;
        Edge3->Pos().y = 0;
        Edge4->Pos().y = 0;
    }
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
    }

    if (Edge1->Pos().y <= -150.0f)
    {
        Edge1->SetActive(false);
        Edge2->SetActive(false);
        Edge3->SetActive(false);
        Edge4->SetActive(false);
    }
}