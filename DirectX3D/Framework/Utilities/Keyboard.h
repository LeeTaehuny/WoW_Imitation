#pragma once

class Keyboard : public Singleton<Keyboard>
{
private:
    friend class Singleton;

    static const UINT KEY_MAX = 255;

    enum KeyState
    {
        NONE, DOWN, UP, PRESS
    };    

    Keyboard() = default;
    ~Keyboard() = default;

public:
    void Update();

    bool Down(UINT key) { return mapState[key] == DOWN; }
    bool Up(UINT key) { return mapState[key] == UP; }
    bool Press(UINT key) { return mapState[key] == PRESS; }
private:
    BYTE curState[KEY_MAX] = {};
    BYTE oldState[KEY_MAX] = {};
    KeyState mapState[KEY_MAX] = {};
};