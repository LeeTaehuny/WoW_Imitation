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
    bool GetSelect() { return bIsSelected; }

// Member Variable
private:
    Event eventDown = nullptr;
    Event eventOver = nullptr;

    bool bIsClicked = false;
    bool bIsSelected = false;
};

