#pragma once

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void Update();
    void Render();

private:
    void Create();
    void Delete();
};