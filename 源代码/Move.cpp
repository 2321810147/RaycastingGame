#include<iostream>
#include"Move.h"
using namespace std;

//旋转
//处理逆时针旋转
//1.按下Q键,向左旋转角度
void Move::KeyQ(float& PlayerA)
{
	if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
	{
		PlayerA -= (1.5f) * this->ElapsedTime;
	}
}

//2.E键，向右旋转角度
void Move::KeyE(float& PlayerA)
{
	if (GetAsyncKeyState((unsigned short)'E') & 0x8000)
	{
		PlayerA += (1.5f) * this->ElapsedTime;
	}
}

//3,W键,玩家的位置改变，前进
void Move::KeyW(float PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map)
{
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
	{
		//前进的速度
		PlayerX += cosf(PlayerA) * 3.0f * this->ElapsedTime;
		PlayerY += sinf(PlayerA) * 3.0f * this->ElapsedTime;
		int a = (int)PlayerY * MapWidth + (int)PlayerX;
		//检测是否碰墙
		if (map[a] != ' ')
		{
			//位置后退，抵消
			PlayerX -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
		}
		if (map[a] == 'B' || map[a] == 'Y' || map[a] == 'N' || map[a] == 'E')
		{
			PlayerX += cosf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY += sinf(PlayerA) * 3.0f * this->ElapsedTime;
		}
	}
}


//4,S键,玩家的位置改变，后退
void Move::KeyS(float PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map)
{
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
	{
		//后退的速度
		PlayerX -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
		PlayerY -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
		int a = (int)PlayerY * MapWidth + (int)PlayerX;

		//检测是否碰墙
		if (map[a] != ' ')
		{
			//位置前进，抵消
			PlayerX += cosf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY += sinf(PlayerA) * 3.0f * this->ElapsedTime;
		}
		if (map[a] == 'B' || map[a] == 'Y' || map[a] == 'N' || map[a] == 'E')
		{
			PlayerX -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
		}
	}
}


//5,D键,玩家的位置右移
void Move::KeyA(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map)
{
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
	{
		//前进的速度
		PlayerX += sinf(PlayerA) * 3.0f * this->ElapsedTime;
		PlayerY -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
		int a = (int)PlayerY * MapWidth + (int)PlayerX;

		//检测是否碰墙
		if (map[a] != ' ')
		{
			//位置后退，抵消
			PlayerX -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY += cosf(PlayerA) * 3.0f * this->ElapsedTime;
		}
		if (map[a] == 'B' || map[a] == 'Y' || map[a] == 'N' || map[a] == 'E')
		{
			PlayerX += sinf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
		}
	}
}

//6,A键,玩家的位置左移
void Move::KeyD(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map)
{
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
	{
		//前进的速度
		PlayerX -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
		PlayerY += cosf(PlayerA) * 3.0f * this->ElapsedTime;
		int a = (int)PlayerY * MapWidth + (int)PlayerX;

		//检测是否碰墙
		if (map[a] != ' ')
		{
			//位置后退，抵消
			PlayerX += sinf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
		}
		if (map[a] == 'B' || map[a] == 'Y' || map[a] == 'N' || map[a] == 'E')
		{
			PlayerX -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY += cosf(PlayerA) * 3.0f * this->ElapsedTime;
		}
	}
}


// 检测鼠标移动方向（返回 -1:左移, 1:右移, 0:未移动或垂直移动）
int Move::GetMouseHorizontalDirection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD irInBuf;
	DWORD cNumRead;

	// 循环读取输入缓冲区的事件
	while (PeekConsoleInput(hStdin, &irInBuf, 1, &cNumRead) && cNumRead > 0) {
		ReadConsoleInput(hStdin, &irInBuf, 1, &cNumRead); // 不管事件类型，先读出来

		if (irInBuf.EventType == MOUSE_EVENT) {
			MOUSE_EVENT_RECORD mer = irInBuf.Event.MouseEvent;
			if (mer.dwEventFlags == MOUSE_MOVED) {
				int direction = (mer.dwMousePosition.X > g_lastMousePos.X) ? 1 :
					(mer.dwMousePosition.X < g_lastMousePos.X) ? -1 : 0;
				g_lastMousePos = mer.dwMousePosition;
				return direction;
			}
		}

		// 其他类型事件直接忽略，但必须移除掉（已通过 ReadConsoleInput 处理）
	}

	return 0;
}


//向左旋转角度
void Move::MiceL(float& PlayerA)
{
	PlayerA -= (1.5f) * this->ElapsedTime;
}

//向右旋转角度
void Move::MiceR(float& PlayerA)
{
	PlayerA += (1.5f) * this->ElapsedTime;
}


void Move::Skill(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, int MapHeight, wstring map)
{
	
		float EyeX = cosf(PlayerA);
		float EyeY = sinf(PlayerA);

		float TestX = PlayerX + EyeX * 4.0;
		float TestY = PlayerY + EyeY * 4.0;

		if (TestX < MapWidth && TestX >= 0 && TestY < MapHeight && TestY >= 0)
		{
			if (map[(int)TestY * MapWidth + (int)TestX] == ' ')
			{
				PlayerX += EyeX * 4.0;
				PlayerY += EyeY * 4.0;
				this->NumOfSkill++;
			}
		}
}
void Move::RefreshSkill()
{
	while (this->runing)
	{
		this->NumOfSkill = 0;
		this_thread::sleep_for(std::chrono::seconds(4));
	}
}
void Move::IsFire()
{
	bool spacePressedNow = GetAsyncKeyState(VK_LBUTTON) & 0x8000;

	if (spacePressedNow && !this->spacePressedLast)
		this->fire = true;
	else
		this->fire = false;

	this->spacePressedLast = spacePressedNow;
}




//颠倒移动
void Move::RKeyQ(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map)
{
	if (GetAsyncKeyState((unsigned short)'Q') & 0x8000)
	{
		//前进的速度
		PlayerX -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
		PlayerY += cosf(PlayerA) * 3.0f * this->ElapsedTime;
		int a = (int)PlayerY * MapWidth + (int)PlayerX;

		//检测是否碰墙
		if (map[a] != ' ')
		{
			//位置后退，抵消
			PlayerX += sinf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
		}
		if (map[a] == 'B' || map[a] == 'Y' || map[a] == 'N' || map[a] == 'E')
		{
			PlayerX -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY += cosf(PlayerA) * 3.0f * this->ElapsedTime;
		}
	}
}

void Move::RKeyE(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map)
{
	if (GetAsyncKeyState((unsigned short)'E') & 0x8000)
	{
		//前进的速度
		PlayerX += sinf(PlayerA) * 3.0f * this->ElapsedTime;
		PlayerY -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
		int a = (int)PlayerY * MapWidth + (int)PlayerX;

		//检测是否碰墙
		if (map[a] != ' ')
		{
			//位置后退，抵消
			PlayerX -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY += cosf(PlayerA) * 3.0f * this->ElapsedTime;
		}
		if (map[a] == 'B' || map[a] == 'Y' || map[a] == 'N' || map[a] == 'E')
		{
			PlayerX += sinf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
		}
	}
}


void Move::RKeyW(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map)
{
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000)
	{
		//后退的速度
		PlayerX -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
		PlayerY -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
		int a = (int)PlayerY * MapWidth + (int)PlayerX;

		//检测是否碰墙
		if (map[a] != ' ')
		{
			//位置前进，抵消
			PlayerX += cosf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY += sinf(PlayerA) * 3.0f * this->ElapsedTime;
		}
		if (map[a] == 'B' || map[a] == 'Y' || map[a] == 'N' || map[a] == 'E')
		{
			PlayerX -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
		}
	}
}


void Move::RKeyS(float& PlayerA, float& PlayerX, float& PlayerY, int MapWidth, wstring map)
{
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000)
	{
		//前进的速度
		PlayerX += cosf(PlayerA) * 3.0f * this->ElapsedTime;
		PlayerY += sinf(PlayerA) * 3.0f * this->ElapsedTime;
		int a = (int)PlayerY * MapWidth + (int)PlayerX;
		//检测是否碰墙
		if (map[a] != ' ')
		{
			//位置后退，抵消
			PlayerX -= cosf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY -= sinf(PlayerA) * 3.0f * this->ElapsedTime;
		}
		if (map[a] == 'B' || map[a] == 'Y' || map[a] == 'N' || map[a] == 'E')
		{
			PlayerX += cosf(PlayerA) * 3.0f * this->ElapsedTime;
			PlayerY += sinf(PlayerA) * 3.0f * this->ElapsedTime;
		}
	}
}


void Move::RKeyA(float& PlayerA)
{
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
	{
		PlayerA += (1.5f) * this->ElapsedTime;
	}
}

void Move::RKeyD(float& PlayerA)
{
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
	{
		PlayerA -= (1.5f) * this->ElapsedTime;
	}
}