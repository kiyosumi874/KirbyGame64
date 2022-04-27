#pragma once
//#include <Xinput.h>

class Input
{
public:
    enum ButtonID
    {
        BUTTON_ID_LEFT,     // 十字キー
        BUTTON_ID_RIGHT,
        BUTTON_ID_UP,
        BUTTON_ID_DOWN,
        BUTTON_ID_0,        // その他ボタン
        BUTTON_ID_RETURN,
        BUTTON_ID_ESC,
        BUTTON_ID_F,
        BUTTON_ID_W,
        BUTTON_ID_A,
        BUTTON_ID_S,
        BUTTON_ID_D,
        BUTTON_ID_E,
        BUTTON_ID_Q,
        BUTTON_ID_SPACE,


        BUTTON_ID_MAX
    };
private:
    struct KeyInformation
    {
        char keyCode; // VK_SHIFTとか'A'のやつh
        int pressCount; // 状態
    };
    KeyInformation m_keys[BUTTON_ID_MAX];

public:

    Input();
	~Input() {}

	void Update();
    // 押した瞬間
    bool IsDown(int buttonID)    const { return m_keys[buttonID].pressCount == 1; } 
    // 押しているとき
    bool IsPress(int buttonID)   const { return m_keys[buttonID].pressCount > 1;  } 
    // 離した瞬間
    bool IsUp(int buttonID)      const { return m_keys[buttonID].pressCount == 0; } 
    // 離しているとき
    bool IsRelease(int buttonID) const { return m_keys[buttonID].pressCount < 0;  } 
};