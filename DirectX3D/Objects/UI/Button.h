#pragma once
#include "Objects/Basic/Quad.h"

class Button : public Quad
{
public:
    Button(wstring textureFile);
    Button(Vector2 size);
    ~Button();

    virtual void Update();
    virtual void Render() override;

// Getter & Setter
public:
    void SetDownEvent(Event event) { this->eventDown = event; }
    void SetOverEvent(Event event) { this->eventOver = event; }
    void SetPressEvent(Event event) { this->eventPress = event; }
    void SetUpEvent(Event event) { this->eventUp = event; }
    bool GetSelect() { return bIsSelected; }
    void SetSelect(bool value) { bIsSelected = value; }
    void SetCilck(bool value) { bIsClicked = value; }

private:
    bool MouseOver();

// Member Variable
private:
    Event eventDown = nullptr;
    Event eventPress = nullptr;
    Event eventOver = nullptr;
    Event eventUp = nullptr;

    bool bIsClicked = false;
    bool bIsSelected = false;
};

