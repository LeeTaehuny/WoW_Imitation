#include "Framework.h"

GameObject::GameObject(wstring shaderFile)
{
    material = new Material(shaderFile);
    worldBuffer = new MatrixBuffer();
}

GameObject::~GameObject()
{ 
    delete material;
    delete worldBuffer;
}

void GameObject::SetRender()
{   
    worldBuffer->Set(world);
    worldBuffer->SetVS(0);    

    material->Set();
}

void GameObject::GUIRender()
{    
    string label = tag + "_Object";
    if (ImGui::TreeNode(label.c_str()))
    {
        Transform::GUIRender();
        material->GUIRender();

        ImGui::TreePop();
    }
}
