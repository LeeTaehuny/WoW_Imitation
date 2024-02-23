#include "Framework.h"
#include "TestExportRender.h"

TestExportRender::TestExportRender()
{
    M1 = new Model("Practiceplace_1");
    M2 = new Model("Practiceplace_2");
    M3 = new Model("Practiceplace_3");

    M2->Pos().x = 250;
    M3->Pos().x = 350;
}

TestExportRender::~TestExportRender()
{
    delete M1;
    delete M2;
    delete M3;
}

void TestExportRender::Update()
{
    M1->UpdateWorld();
    M2->UpdateWorld();
    M3->UpdateWorld();
}

void TestExportRender::Render()
{
    M1->Render();
    M2->Render();
    M3->Render();
}

void TestExportRender::PreRender()
{
}

void TestExportRender::PostRender()
{
}

void TestExportRender::GUIRender()
{
}
