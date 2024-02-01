#include "Framework.h"
#include "Button.h"

Button::Button(wstring textureFile)
    : Quad(textureFile)
{
}

Button::Button(Vector2 size)
    : Quad(size)
{
}

Button::~Button()
{
}

void Button::Update()
{
    if (!isActive) return;

    if (mousePos.x <= GlobalPos().x + size.x && mousePos.x >= GlobalPos().x - size.x &&
        mousePos.y <= GlobalPos().y + size.y && mousePos.y >= GlobalPos().y - size.y)
    {
        if (KEY_DOWN(VK_LBUTTON))
        {
            // �̺�Ʈ �Լ� ����
            if (eventDown != nullptr)
                eventDown();

            bIsClicked = true;
            bIsSelected = true;
        }
        
        if (!bIsClicked)
        {
            // �̺�Ʈ �Լ� ����
            if (eventOver != nullptr)
                eventOver();
        }
    }
    else
    {
        bIsClicked = false;
        bIsSelected = false;
    }

    UpdateWorld();
}

void Button::Render()
{
    if (!isActive) return;

    Quad::Render();
}