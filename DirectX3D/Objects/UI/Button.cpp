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

    if (MouseOver())
    {
        if (KEY_DOWN(VK_LBUTTON))
        {
            // 이벤트 함수 실행
            if (eventDown != nullptr)
                eventDown();

            bIsClicked = true;
            bIsSelected = true;
        }

        if (KEY_PRESS(VK_LBUTTON) && bIsClicked)
        {
            // 이벤트 함수 실행
            if (eventPress != nullptr)
                eventPress();
        }
        
        if (!bIsClicked)
        {
            // 이벤트 함수 실행
            if (eventOver != nullptr)
                eventOver();
        }

        if (KEY_UP(VK_LBUTTON))
        {
            // 이벤트 함수 실행
            if (eventUp != nullptr)
                eventUp();

            bIsClicked = false;
            bIsSelected = false;
        }
    }

    UpdateWorld();
}

void Button::Render()
{
    if (!isActive) return;

    Quad::Render();
}

bool Button::MouseOver()
{
    // 마우스가 영역 내에 존재하는지를 판별해 리턴
    return (mousePos.x <= GlobalPos().x + size.x && mousePos.x >= GlobalPos().x - size.x && mousePos.y <= GlobalPos().y + size.y && mousePos.y >= GlobalPos().y - size.y);
}
