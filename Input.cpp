#include "Input.h"
#include <Windows.h>
#include <vector>

Input::Input()
{
	std::vector<char> initKeyCode;
	initKeyCode.push_back(VK_LEFT);
	initKeyCode.push_back(VK_RIGHT);
	initKeyCode.push_back(VK_UP);
	initKeyCode.push_back(VK_DOWN);
	initKeyCode.push_back('0');
	initKeyCode.push_back(VK_RETURN);
	initKeyCode.push_back(VK_ESCAPE);
	initKeyCode.push_back('F');
	initKeyCode.push_back('W');
	initKeyCode.push_back('A');
	initKeyCode.push_back('S');
	initKeyCode.push_back('D');
	initKeyCode.push_back('E');
	initKeyCode.push_back('Q');
	initKeyCode.push_back(VK_SPACE);
	
	for (int i = 0; i < BUTTON_ID_MAX; i++)
	{
		m_keys[i].keyCode = initKeyCode[i];
		m_keys[i].pressCount = -1;
	}
}

void Input::Update()
{
	for (int i = 0; i < BUTTON_ID_MAX; i++)
	{
		// GetAsyncKeyState�͉����Ă���Ƃ��ŏ�ʃr�b�g������
		if (GetAsyncKeyState(m_keys[i].keyCode) & 0x8000) // 0x8000��short�̍ŏ�ʃr�b�g�������Ă��邱�Ƃ�\��
		{
			m_keys[i].pressCount = max(++m_keys[i].pressCount, 1);
		}
		else
		{
			m_keys[i].pressCount = min(--m_keys[i].pressCount, 0);
		}
	}
}
