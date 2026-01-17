#define _CRT_SECURE_NO_DEPRECATE 
#include<iostream>
#include<cmath>
#include<chrono>
#include<algorithm>
#include<vector>
#include<string>
#include <stdio.h>
#include<Windows.h>
#include"ScreenInitial.h"
#include"ScreenCanvas.h"
#include"Map.h"
#include <conio.h>
#include"Move.h"
#include<string.h>
#include"PlayerInitialData.h"
#include"Enemy.h"
#include<thread>
#include <limits.h>
#include"Weapon.h"
#include <cstdio>
using namespace std;
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

//无效放大窗口
void DisableConsoleResize()
{
	HWND hWnd = GetConsoleWindow();
	if (hWnd == NULL) return;

	// 获取当前窗口样式
	LONG style = GetWindowLong(hWnd, GWL_STYLE);

	// 移除最大化按钮 (WS_MAXIMIZEBOX) 和可调大小边框 (WS_SIZEBOX)
	style &= ~WS_MAXIMIZEBOX;
	style &= ~WS_SIZEBOX;

	// 设置新样式
	SetWindowLong(hWnd, GWL_STYLE, style);

	// 强制刷新窗口以应用样式更改
	SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}
int main()
{
	//背景音乐
	mciSendString(L"open \"Summer.wav\" type waveaudio alias summer", NULL, 0, NULL);
	mciSendString(L"play summer ", NULL, 0, NULL);



	HANDLE hDefault = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written;
	DisableConsoleResize();
	bool keyPressed = false;
	// 准备文本内容（每一行）
	std::vector<std::wstring> story = {
	L"F键展开对话",
	L"？？？：……能听到吗？喂，喂！你醒了吗？",
	L"程序员：唔……头好晕……这里是……？我不是刚在电脑前调Bug吗？",
	L"？？？：（松了口气）太好了，你还活着。",
	L"程序员：（警觉）你是谁？你又把我带到哪了？",
	L"小小框：我叫小小框，是这个世界的精灵。你……被选中了。",
	L"程序员：选中？你不会是说——那种“被召唤到异世界拯救世界”的老套展开吧？",
	L"小小框：（认真点头）没错，我们的世界“黑框框”正处于危机之中。",
	L"小小框：终焉的魔王--红框入侵了我们的世界，我们的世界本来只有黑框和白框，但魔王的力量感染了它们，不少框框都变色啦",
	L"小小框：这怎么可以呢，黑框框的世界应该只有黑框和白框，变色的框框都迷失了自我，情况危急，只有你——传说中的勇者——能够阻止魔王。",
	L"程序员：（无语）拜托，现在都2025年了，怎么还搞这种设定……",
	L"小小框：（微笑）……但你确实拥有异界之力。你看——",
	L"（小小框轻抬手，程序员掌心浮现出发光的纹章）",
	L"程序员：？！这是什么！？好烫——不对，好像有种奇怪的力量……",
	L"小小框：那是“圣徽”，证明你是勇者。",
	L"小小框：从现在起，我将作为你的向导，陪你踏上旅程。",
	L"程序员：（叹气）行吧……反正回不去了是吧？",
	L"小小框：（沉默片刻）……除非你打倒魔王，找到“世界之钥”，否则无法回到原来的世界。",
	L"程序员：（苦笑）果然是这种设定啊……唉，谁让我闲着也是闲着。",
	L"程序员：那就上吧！魔王什么的，听起来也不是不能打嘛！",
	L"小小框：好，接下来我指代你异界之力如何使用",
	L"WASD为方向移动，EQ为视角转换，鼠标也可移动视角，R为技能突刺，可以向前突进4格，鼠标左键为攻击",
	L"F为进入下一关的按钮，击败每层的敌人后到地图右下角的缺口里按F就可以进入下一关啦",
	L"小小框：你学会了吗？",
	L"程序员：太简单了，一看就会",
	L"小小框：对了，魔王还会在某一层埋下了陷阱，按键全都反了，怎么办啊",
	L"程序员：不用担心，对于一个程序员来说这不是问题，我把键盘反过来就行了",
	L"小小框，原来还有这种方法，你太厉害了"
	L"程序员：话不多说，为了回到原来的实界，黑框框，启动！！！"
	};
	size_t currentLine = 0; // 当前正在输出的行数
	// 主循环
	while (true)
	{
		// 检测 F 键是否按下
		if (GetAsyncKeyState(0x46) & 0x8000)
		{
			if (!keyPressed)
			{
				keyPressed = true;

				if (currentLine < story.size())
				{
					// 输出当前行
					const wchar_t* text = story[currentLine].c_str();
					WriteConsoleW(hDefault, text, wcslen(text), &written, NULL);
					WriteConsoleW(hDefault, L"\n", 1, &written, NULL);
					currentLine++;
				}
				else
				{
					// 所有行已输出，退出程序
					WriteConsoleW(hDefault, L"\n", 13, &written, NULL);
					break;
				}
			}
		}
		else
		{
			keyPressed = false; // 松开时清除状态
		}
		Sleep(10); // 防止CPU占用过高
	}


	ScreenInitial ScreenIn(390, 130);
	//用于切换控制台的当前活动屏幕缓冲区
	SetConsoleActiveScreenBuffer(ScreenIn.hConsole);
	ScreenIn.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn.SetConsoleBufferSize(ScreenIn.ScreenWidth, ScreenIn.ScreenHeight);
	ScreenIn.SetConsoleWindowSize(ScreenIn.ScreenWidth, ScreenIn.ScreenHeight);
	SMALL_RECT windowSize = { 0, 0, ScreenIn.ScreenWidth - 1, ScreenIn.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn.hConsole, TRUE, &windowSize);
	Map map(13, 13);
	PlayerInitialData Player(2,6.5);
	map.ChangeMaxLine(map.MapWidth, map.MapHeight);
	map.map += L"#############";
	map.map += L"#####   #####";
	map.map += L"####@   #####";
	map.map += L"####$   W####";
	map.map += L"####&   #####";
	map.map += L"#           $";
	map.map += L"#            ";
	map.map += L"#           $";
	map.map += L"####M   W####";
	map.map += L"#####   K####";
	map.map += L"####K   $####";
	map.map += L"#####   #####";
	map.map += L"#############";

	ScreenCanvas Canvas(390, 130);
	Move move;
	//敌人
	int NumOfEnemy = 1;
	Enemy2 e1(11,6);
	e1.StartAutoMove(map.map,map.MapWidth);
	//获取当前系统时间点
	auto t = chrono::system_clock::now();
	auto p = chrono::system_clock::now();
	//刷新技能
	thread timerThread(&Move::RefreshSkill,&move);
	//武器
	Weapon weapon;
	//游戏引擎循环
	while (1)
	{
		p = chrono::system_clock::now();
		chrono::duration<float>elapsedtime = p - t;
		t = p;
		move.ElapsedTime = elapsedtime.count();
		//鼠标
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		//1.按下Q键,向左旋转角度
		move.KeyQ(Player.PlayerA);
		//2.E键，向右旋转角度
		move.KeyE(Player.PlayerA);
		//3,W键,玩家的位置改变，前进
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map.MapWidth, map.map);
		//4,S键,玩家的位置改变，后退
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map.MapWidth, map.map);
		//5,A键,玩家的位置左移
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map.MapWidth, map.map);
		//6,D键,玩家的位置右移
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map.MapWidth, map.map);
		//7.技能
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000)&&move.NumOfSkill==0)
		{
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map.MapWidth, map.MapHeight, map.map);
		}
		//8.鼠标移动视野
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs== -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)		
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		//缓冲加载画面
		Canvas.CanvasFilling(map.map, map.MapWidth, map.MapHeight, map.MaxMapLine,
			ScreenIn.ScreenWidth, ScreenIn.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		//小地图
		Canvas.MiniMap(map.map, map.MapWidth, map.MapHeight, ScreenIn.ScreenWidth, ScreenIn.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人处理
		if (e1.alive)
		{
			e1.FillEnemy(map.map, map.MapWidth);//把敌人导入到小地图上，然后通过小地图创建敌人
		}
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e1.DeleEnemy(Player.PlayerA,Player.PlayerX,Player.PlayerY,map.MaxMapLine, map.map, map.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn.ScreenWidth, ScreenIn.ScreenHeight, Canvas.ColorBuffer);
		}
		//武器处理
		weapon.hand(Canvas.Canvas, ScreenIn.ScreenWidth, ScreenIn.ScreenHeight,Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn.ScreenWidth, ScreenIn.ScreenHeight, Canvas.ColorBuffer);

		Player.CheckHP(map.MapWidth,map.map);
		//创建一个输出参数，用于接收实际写入的字符数
		DWORD dwBytesWritten = 0;
		//索引是从0开始的,\0为标记最后一个位置的终止符
		Canvas.Canvas[ScreenIn.ScreenWidth * ScreenIn.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacterW(
			ScreenIn.hConsole,                               // 控制台屏幕缓冲区的句柄
			Canvas.Canvas,                                   // 要写入的字符数组指针
			ScreenIn.ScreenWidth * ScreenIn.ScreenHeight,    // 要写入的字符数
			{ 0,0 },					                     // 起始写入位置（坐标）
			&dwBytesWritten				                     // 实际写入字符数的指针
		);
		WriteConsoleOutputAttribute(
			ScreenIn.hConsole,                               // 控制台屏幕缓冲区的句柄
			Canvas.ColorBuffer,                              // 要写入的字符数组指针
			ScreenIn.ScreenWidth * ScreenIn.ScreenHeight,    // 要写入的字符数
			{ 0,0 },			                     		 // 起始写入位置（坐标）
			&dwBytesWritten			                    	 // 实际写入字符数的指针
		);
		Sleep(1);//休眠一豪秒，让攻击效果可以显现
		if ((int)Player.PlayerX == 12 && (int)Player.PlayerY == 6&&GetAsyncKeyState((unsigned short)'F') & 0x8000)
		break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 6.5; Player.PlayerY = 6.5;
			e1.HP = 6;
			e1.alive = 1;
			Player.HP = 5;
			NumOfEnemy = 1;
		}
	}
	e1.StopAutoMove();
	CloseHandle(ScreenIn.hConsole);


	
	//第一关
	ScreenInitial ScreenIn1(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn1.hConsole);
	ScreenIn1.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn1.SetConsoleBufferSize(ScreenIn1.ScreenWidth, ScreenIn1.ScreenHeight);
	ScreenIn1.SetConsoleWindowSize(ScreenIn1.ScreenWidth, ScreenIn1.ScreenHeight);
	SMALL_RECT windowSize1 = { 0, 0, ScreenIn1.ScreenWidth - 1, ScreenIn1.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn1.hConsole, TRUE, &windowSize1);
	Player.ChangeXY(3.0, 3.0);
	Player.ChangeA(-1.0f);
	Map map1(16, 16);
	map1.ChangeMaxLine(map1.MapWidth, map1.MapHeight);
	map1.map += L"################";
	map1.map += L"#              #";
	map1.map += L"#   #    ###   #";
	map1.map += L"#   #          #";
	map1.map += L"#   #      #   #";
	map1.map += L"#   ###    #   #";
	map1.map += L"#   #          #";
	map1.map += L"#  ##          #";
	map1.map += L"#   #          #";
	map1.map += L"#   #          #";
	map1.map += L"#   #          #";
	map1.map += L"#              #";
	map1.map += L"######### ######";
	map1.map += L"#      ## #####$";
	map1.map += L"#               ";
	map1.map += L"###############$";
	//敌人
	NumOfEnemy = 2;
	Enemy1 e1_1(9, 12);
	Enemy1 e1_2(9, 13);
	auto t1 = chrono::system_clock::now();
	auto p1 = chrono::system_clock::now();
	while (1)
	{
		p1 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime1 = p1 - t1;
		t1 = p1;
		move.ElapsedTime = elapsedtime1.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.KeyQ(Player.PlayerA);
		move.KeyE(Player.PlayerA);
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map1.MapWidth, map1.map);
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map1.MapWidth, map1.map);
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map1.MapWidth, map1.map);
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map1.MapWidth, map1.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
		{
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map1.MapWidth, map1.MapHeight, map1.map);
		}
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map1.map, map1.MapWidth, map1.MapHeight, map1.MaxMapLine,
			ScreenIn1.ScreenWidth, ScreenIn1.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map1.map, map1.MapWidth, map1.MapHeight, ScreenIn1.ScreenWidth, ScreenIn1.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人
		if (e1_1.alive)
		{
			e1_1.FillEnemy(map1.map, map1.MapWidth);
		}
		if (e1_2.alive)
		{
			e1_2.FillEnemy(map1.map, map1.MapWidth);
		}
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e1_1.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map1.MaxMapLine, map1.map, map1.MapWidth, NumOfEnemy);
			e1_2.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map1.MaxMapLine, map1.map, map1.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn1.ScreenWidth, ScreenIn1.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn1.ScreenWidth, ScreenIn1.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn1.ScreenWidth, ScreenIn1.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map1.MapWidth, map1.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn1.ScreenWidth * ScreenIn1.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn1.hConsole,                   
			Canvas.Canvas,                   
			ScreenIn1.ScreenWidth * ScreenIn1.ScreenHeight,  
			{ 0,0 },			
			&dwBytesWritten			
		);
		WriteConsoleOutputAttribute(
			ScreenIn1.hConsole,                             
			Canvas.ColorBuffer,                             
			ScreenIn1.ScreenWidth* ScreenIn1.ScreenHeight,  
			{ 0,0 },			                     		
			& dwBytesWritten			                    
		);
		Sleep(1);
		if ((int)Player.PlayerX == 15 && (int)Player.PlayerY == 14 && GetAsyncKeyState((unsigned short)'F') & 0x8000)
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			e1_1.HP = 4;
			e1_1.alive = 1;
			e1_2.HP = 4;
			e1_2.alive = 1;
			Player.HP = 5;
			NumOfEnemy = 2;
		}
	}
	CloseHandle(ScreenIn1.hConsole);
	


	//第二关
	ScreenInitial ScreenIn2(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn2.hConsole);
	ScreenIn2.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn2.SetConsoleBufferSize(ScreenIn2.ScreenWidth, ScreenIn2.ScreenHeight);
	ScreenIn2.SetConsoleWindowSize(ScreenIn2.ScreenWidth, ScreenIn2.ScreenHeight);
	SMALL_RECT windowSize2 = { 0, 0, ScreenIn2.ScreenWidth - 1, ScreenIn2.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn2.hConsole, TRUE, &windowSize2);
	Player.ChangeXY(3.0, 3.0);
	Player.ChangeA(-1.0f);
	Map map2(16, 16);
	map2.ChangeMaxLine(map2.MapWidth, map2.MapHeight);
	map2.map += L"################";
	map2.map += L"#              #";
	map2.map += L"#  #####       #";
	map2.map += L"#           #  #";
	map2.map += L"#   ###   # #  #";
	map2.map += L"#   #     # #  #";
	map2.map += L"#   # @        #";
	map2.map += L"#        #    ##";
	map2.map += L"#            # #";
	map2.map += L"#            W #";
	map2.map += L"#              #";
	map2.map += L"#           ## #";
	map2.map += L"#         #    #";
	map2.map += L"#  W # M       $";
	map2.map += L"#     #         ";
	map2.map += L"###############$";
	//敌人
	NumOfEnemy = 2;
	Enemy2 e2_1(10, 2);
	Enemy2 e2_2(10, 4);
	e2_1.StartAutoMove(map2.map, map2.MapWidth);
	e2_2.StartAutoMove(map2.map, map2.MapWidth);
	auto t2 = chrono::system_clock::now();
	auto p2 = chrono::system_clock::now();
	while (1)
	{
		p2 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime2 = p2 - t2;
		t2 = p2;
		move.ElapsedTime = elapsedtime2.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.KeyQ(Player.PlayerA);
		move.KeyE(Player.PlayerA);
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map2.MapWidth, map2.map);
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map2.MapWidth, map2.map);
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map2.MapWidth, map2.map);
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map2.MapWidth, map2.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
		{
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map2.MapWidth, map2.MapHeight, map2.map);
		}
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map2.map, map2.MapWidth, map2.MapHeight, map2.MaxMapLine,
			ScreenIn2.ScreenWidth, ScreenIn2.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map2.map, map2.MapWidth, map2.MapHeight, ScreenIn2.ScreenWidth, ScreenIn2.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人
		if (e2_1.alive)
		{
			e2_1.FillEnemy(map2.map, map2.MapWidth);
		}
		if (e2_2.alive)
		{
			e2_2.FillEnemy(map2.map, map2.MapWidth);
		}
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e2_1.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map2.MaxMapLine, map2.map, map2.MapWidth, NumOfEnemy);
			e2_2.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map2.MaxMapLine, map2.map, map2.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn1.ScreenWidth, ScreenIn1.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn2.ScreenWidth, ScreenIn2.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn2.ScreenWidth, ScreenIn2.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map2.MapWidth, map2.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn2.ScreenWidth * ScreenIn2.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn2.hConsole,
			Canvas.Canvas,
			ScreenIn2.ScreenWidth * ScreenIn2.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		WriteConsoleOutputAttribute(
			ScreenIn2.hConsole,
			Canvas.ColorBuffer,
			ScreenIn2.ScreenWidth * ScreenIn2.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		if ((int)Player.PlayerX == 15 && (int)Player.PlayerY == 14 && GetAsyncKeyState((unsigned short)'F') & 0x8000)
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			e2_1.HP = 4;
			e2_1.alive = 1;
			e2_2.HP = 4;
			e2_2.alive = 1;
			Player.HP = 5;
			NumOfEnemy = 2;
		}
		Sleep(1);
	}
	e2_1.StopAutoMove();
	e2_2.StopAutoMove();
	CloseHandle(ScreenIn2.hConsole);
	


	//第三关
	ScreenInitial ScreenIn3(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn3.hConsole);
	ScreenIn3.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn3.SetConsoleBufferSize(ScreenIn3.ScreenWidth, ScreenIn3.ScreenHeight);
	ScreenIn3.SetConsoleWindowSize(ScreenIn3.ScreenWidth, ScreenIn3.ScreenHeight);
	SMALL_RECT windowSize3 = { 0, 0, ScreenIn3.ScreenWidth - 1, ScreenIn3.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn3.hConsole, TRUE, &windowSize3);
	Player.ChangeXY(3.0, 2.0);
	Player.ChangeA(-1.0);
	Map map3(32, 32);
	map3.ChangeMaxLine(map3.MapWidth, map3.MapHeight);
	map3.map += L"################################";
	map3.map += L"#         @                    #";
	map3.map += L"#   #######    #######         #";
	map3.map += L"#   #     #    #     #         #";
	map3.map += L"#   #     #    #     #         #";
	map3.map += L"#   #     #    #     #         #";
	map3.map += L"#   #######    #######         #";
	map3.map += L"#                              #";
	map3.map += L"#       #####                  #";
	map3.map += L"#       #   #                  #";
	map3.map += L"#       # W #                  #";
	map3.map += L"#       #   #                  #";
	map3.map += L"#       #####                  #";
	map3.map += L"#                              #";
	map3.map += L"#   #####      #####           #";
	map3.map += L"#   #   #      #   #           #";
	map3.map += L"#   # $ #      # K #           #";
	map3.map += L"#   #   #      #   #           #";
	map3.map += L"#   #####      #####           #";
	map3.map += L"#                              #";
	map3.map += L"#                              #";
	map3.map += L"#                              #";
	map3.map += L"#         M   M   M            #";
	map3.map += L"#                              #";
	map3.map += L"#                              #";
	map3.map += L"#                              #";
	map3.map += L"#                              #";
	map3.map += L"#                              #";
	map3.map += L"#                              #";
	map3.map += L"#                              $";
	map3.map += L"#                               ";
	map3.map += L"###############################$";
	//敌人
	NumOfEnemy = 4;
	Enemy2 e2_4(28, 28);
	Enemy2 e2_5(7, 27);
	Enemy2 e2_6(7, 26);
	Enemy2 e2_7(7, 28);
	e2_4.StartAutoMove(map3.map, map3.MapWidth);
	e2_5.StartAutoMove(map3.map, map3.MapWidth);
	e2_6.StartAutoMove(map3.map, map3.MapWidth);
	e2_7.StartAutoMove(map3.map, map3.MapWidth);
	auto t3 = chrono::system_clock::now();
	auto p3 = chrono::system_clock::now();
	while (1)
	{
		p3 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime3 = p3 - t3;
		t3 = p3;
		move.ElapsedTime = elapsedtime3.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.KeyQ(Player.PlayerA);
		move.KeyE(Player.PlayerA);
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map3.MapWidth, map3.map);
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map3.MapWidth, map3.map);
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map3.MapWidth, map3.map);
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map3.MapWidth, map3.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
		{
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map3.MapWidth, map3.MapHeight, map3.map);
		}
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map3.map, map3.MapWidth, map3.MapHeight, map3.MaxMapLine,
			ScreenIn3.ScreenWidth, ScreenIn3.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map3.map, map3.MapWidth, map3.MapHeight, ScreenIn3.ScreenWidth, ScreenIn3.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人
		if (e2_4.alive)
		{
			e2_4.FillEnemy(map3.map, map3.MapWidth);
		}
		if (e2_5.alive)
		{
			e2_5.FillEnemy(map3.map, map3.MapWidth);
		}
		if (e2_7.alive)
		{
			e2_7.FillEnemy(map3.map, map3.MapWidth);
		}
		if (e2_6.alive)
		{
			e2_6.FillEnemy(map3.map, map3.MapWidth);
		}
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e2_4.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map3.MaxMapLine, map3.map, map3.MapWidth, NumOfEnemy);
			e2_5.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map3.MaxMapLine, map3.map, map3.MapWidth, NumOfEnemy);
			e2_6.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map3.MaxMapLine, map3.map, map3.MapWidth, NumOfEnemy);
			e2_7.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map3.MaxMapLine, map3.map, map3.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn3.ScreenWidth, ScreenIn3.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn3.ScreenWidth, ScreenIn3.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn3.ScreenWidth, ScreenIn3.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map3.MapWidth, map3.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn3.ScreenWidth * ScreenIn3.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn3.hConsole,
			Canvas.Canvas,
			ScreenIn3.ScreenWidth * ScreenIn3.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		WriteConsoleOutputAttribute(
			ScreenIn3.hConsole,
			Canvas.ColorBuffer,
			ScreenIn3.ScreenWidth * ScreenIn3.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		Sleep(1);
		if ((int)Player.PlayerX == 31 && (int)Player.PlayerY == 30 && GetAsyncKeyState((unsigned short)'F') & 0x8000)
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			e2_4.HP = 6;
			e2_4.alive = 1;
			e2_5.HP = 6;
			e2_5.alive = 1;
			Player.HP = 5;
			e2_6.HP = 6;
			e2_6.alive = 1;
			e2_7.HP = 6;
			e2_7.alive = 1;
			NumOfEnemy = 4;
		}
	}
	e2_4.StopAutoMove();
	e2_5.StopAutoMove();
	e2_6.StopAutoMove();
	e2_7.StopAutoMove();
	CloseHandle(ScreenIn3.hConsole);





	//第四关
	ScreenInitial ScreenIn4(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn4.hConsole);
	ScreenIn4.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn4.SetConsoleBufferSize(ScreenIn4.ScreenWidth, ScreenIn4.ScreenHeight);
	ScreenIn4.SetConsoleWindowSize(ScreenIn4.ScreenWidth, ScreenIn4.ScreenHeight);
	SMALL_RECT windowSize4 = { 0, 0, ScreenIn4.ScreenWidth - 1, ScreenIn4.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn4.hConsole, TRUE, &windowSize4);
	Player.ChangeXY(3.0, 2.0);
	Player.ChangeA(-1.0);
	Map map4(32, 32);
	map4.ChangeMaxLine(map4.MapWidth, map4.MapHeight);
	map4.map += L"################################";
	map4.map += L"#@                             #";
	map4.map += L"#   ######     #######         #";
	map4.map += L"#   #    #     #     #         #";
	map4.map += L"#   #  $ #     #     #         #";
	map4.map += L"#   #    #     #     #         #";
	map4.map += L"#   ######     #######         #";
	map4.map += L"#                              #";
	map4.map += L"#      #########               #";
	map4.map += L"#      #       #               #";
	map4.map += L"#      #   M   #               #";
	map4.map += L"#      #       #               #";
	map4.map += L"#      ########                #";
	map4.map += L"#                              #";
	map4.map += L"#   #RRRRRRRR    #####         #";
	map4.map += L"#   #       #    #   #         #";
	map4.map += L"#   #       #    # K #         #";
	map4.map += L"#   #       #    #   #         #";
	map4.map += L"#   ##KKKKK##    #####         #";
	map4.map += L"#                              #";
	map4.map += L"#         #####                #";
	map4.map += L"#         #   #                #";
	map4.map += L"#         # W #                #";
	map4.map += L"#         #   #                #";
	map4.map += L"#         #####                #";
	map4.map += L"#                              #";
	map4.map += L"#                              #";
	map4.map += L"#                              #";
	map4.map += L"#                              #";
	map4.map += L"#                              $";
	map4.map += L"#                               ";
	map4.map += L"###############################$";
	//敌人
	NumOfEnemy = 4;
	Enemy2 e2_8(30, 3);
	Enemy2 e2_9(30, 5);
	Enemy2 e2_10(30, 18);
	Enemy2 e2_11(7, 28);
	e2_8.StartAutoMove(map4.map, map4.MapWidth);
	e2_9.StartAutoMove(map4.map, map4.MapWidth);
	e2_10.StartAutoMove(map4.map, map4.MapWidth);
	e2_11.StartAutoMove(map4.map, map4.MapWidth);
	auto t4 = chrono::system_clock::now();
	auto p4 = chrono::system_clock::now();
	while (1)
	{
		p4 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime3 = p4 - t4;
		t4 = p4;
		move.ElapsedTime = elapsedtime3.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.KeyQ(Player.PlayerA);
		move.KeyE(Player.PlayerA);
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map4.MapWidth, map4.map);
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map4.MapWidth, map4.map);
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map4.MapWidth, map4.map);
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map4.MapWidth, map4.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map4.MapWidth, map4.MapHeight, map4.map);
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map4.map, map4.MapWidth, map4.MapHeight, map4.MaxMapLine,
			ScreenIn4.ScreenWidth, ScreenIn4.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map4.map, map4.MapWidth, map4.MapHeight, ScreenIn4.ScreenWidth, ScreenIn4.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人
		if (e2_8.alive)
			e2_8.FillEnemy(map4.map, map4.MapWidth);
		if (e2_9.alive)
			e2_9.FillEnemy(map4.map, map4.MapWidth);
		if (e2_11.alive)
			e2_11.FillEnemy(map4.map, map4.MapWidth);
		if (e2_10.alive)
			e2_10.FillEnemy(map4.map, map4.MapWidth);
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e2_8.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map4.MaxMapLine, map4.map, map4.MapWidth, NumOfEnemy);
			e2_9.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map4.MaxMapLine, map4.map, map4.MapWidth, NumOfEnemy);
			e2_10.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map4.MaxMapLine, map4.map, map4.MapWidth, NumOfEnemy);
			e2_11.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map4.MaxMapLine, map4.map, map4.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn4.ScreenWidth, ScreenIn4.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn4.ScreenWidth, ScreenIn4.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn4.ScreenWidth, ScreenIn4.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map4.MapWidth, map4.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn4.ScreenWidth * ScreenIn4.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn4.hConsole,
			Canvas.Canvas,
			ScreenIn4.ScreenWidth * ScreenIn4.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		WriteConsoleOutputAttribute(
			ScreenIn4.hConsole,
			Canvas.ColorBuffer,
			ScreenIn4.ScreenWidth * ScreenIn4.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		Sleep(1);
		if ((int)Player.PlayerX == 31 && (int)Player.PlayerY == 30 && GetAsyncKeyState((unsigned short)'F') & 0x8000)
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			e2_8.HP = 6;
			e2_8.alive = 1;
			e2_9.HP = 6;
			e2_9.alive = 1;
			Player.HP = 5;
			e2_10.HP = 6;
			e2_10.alive = 1;
			e2_11.HP = 6;
			e2_11.alive = 1;
			NumOfEnemy = 4;
		}
	}
	e2_8.StopAutoMove();
	e2_9.StopAutoMove();
	e2_10.StopAutoMove();
	e2_11.StopAutoMove();
	CloseHandle(ScreenIn4.hConsole);

	





	//第五关
	ScreenInitial ScreenIn5(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn5.hConsole);
	ScreenIn5.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn5.SetConsoleBufferSize(ScreenIn5.ScreenWidth, ScreenIn5.ScreenHeight);
	ScreenIn5.SetConsoleWindowSize(ScreenIn5.ScreenWidth, ScreenIn5.ScreenHeight);
	SMALL_RECT windowSize5 = { 0, 0, ScreenIn5.ScreenWidth - 1, ScreenIn5.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn5.hConsole, TRUE, &windowSize5);
	Player.ChangeXY(3.0, 2.0);
	Player.ChangeA(-1.0);
	Map map5(32, 32);
	map5.ChangeMaxLine(map5.MapWidth, map5.MapHeight);
	map5.map += L"################################";
	map5.map += L"K         @                    K";
	map5.map += L"K   #####     ## ###           K";
	map5.map += L"K   #   #     #    #           K";
	map5.map += L"K   # $ #     #  K #           K";
	map5.map += L"K   #   #      #   #           K";
	map5.map += L"K   #####      #####           K";
	map5.map += L"K                              K";
	map5.map += L"K     ######                   K";
	map5.map += L"K     #     #                  K";
	map5.map += L"K     # M   #                  K";
	map5.map += L"K     #     #                  K";
	map5.map += L"K     ## ####                  K";
	map5.map += L"K                              K";
	map5.map += L"K   ## #####    #######        K";
	map5.map += L"K    #     #    #     #        K";
	map5.map += L"K    #     #    #     #        K";
	map5.map += L"K    #     #    #     #        K";
	map5.map += L"K    #######    #######        K";
	map5.map += L"K                              K";
	map5.map += L"K      ######                  K";
	map5.map += L"K      #    #                  K";
	map5.map += L"K      #    #                  K";
	map5.map += L"K      # W  #                  K";
	map5.map += L"K      ######                  K";
	map5.map += L"K                              K";
	map5.map += L"K                              K";
	map5.map += L"K     $   &     K              K";
	map5.map += L"K                              K";
	map5.map += L"K                              $";
	map5.map += L"K                               ";
	map5.map += L"###############################$";
	//敌人
	NumOfEnemy = 4;
	Enemy2 e2_12(29, 4);
	Enemy2 e2_13(29, 7);
	Enemy2 e2_14(28, 29);
	Enemy2 e2_15(7, 29);
	e2_12.StartAutoMove(map5.map, map5.MapWidth);
	e2_13.StartAutoMove(map5.map, map5.MapWidth);
	e2_14.StartAutoMove(map5.map, map5.MapWidth);
	e2_15.StartAutoMove(map5.map, map5.MapWidth);
	auto t5 = chrono::system_clock::now();
	auto p5 = chrono::system_clock::now();
	while (1)
	{
		p5 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime3 = p5 - t5;
		t5 = p5;
		move.ElapsedTime = elapsedtime3.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.KeyQ(Player.PlayerA);
		move.KeyE(Player.PlayerA);
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map5.MapWidth, map5.map);
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map5.MapWidth, map5.map);
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map5.MapWidth, map5.map);
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map5.MapWidth, map5.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map5.MapWidth, map5.MapHeight, map5.map);
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map5.map, map5.MapWidth, map5.MapHeight, map5.MaxMapLine,
			ScreenIn5.ScreenWidth, ScreenIn5.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map5.map, map5.MapWidth, map5.MapHeight, ScreenIn5.ScreenWidth, ScreenIn5.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人
		if (e2_12.alive)
			e2_12.FillEnemy(map5.map, map5.MapWidth);
		if (e2_13.alive)
			e2_13.FillEnemy(map5.map, map5.MapWidth);
		if (e2_15.alive)
			e2_15.FillEnemy(map5.map, map5.MapWidth);
		if (e2_14.alive)
			e2_14.FillEnemy(map5.map, map5.MapWidth);
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e2_12.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map5.MaxMapLine, map5.map, map5.MapWidth, NumOfEnemy);
			e2_13.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map5.MaxMapLine, map5.map, map5.MapWidth, NumOfEnemy);
			e2_14.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map5.MaxMapLine, map5.map, map5.MapWidth, NumOfEnemy);
			e2_15.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map5.MaxMapLine, map5.map, map5.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn5.ScreenWidth, ScreenIn5.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn5.ScreenWidth, ScreenIn5.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn5.ScreenWidth, ScreenIn5.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map5.MapWidth, map5.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn5.ScreenWidth * ScreenIn5.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn5.hConsole,
			Canvas.Canvas,
			ScreenIn5.ScreenWidth * ScreenIn5.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		WriteConsoleOutputAttribute(
			ScreenIn5.hConsole,
			Canvas.ColorBuffer,
			ScreenIn5.ScreenWidth * ScreenIn5.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		Sleep(1);
		if ((int)Player.PlayerX == 31 && (int)Player.PlayerY == 30 && GetAsyncKeyState((unsigned short)'F') & 0x8000 )
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			e2_12.HP = 6;
			e2_12.alive = 1;
			e2_13.HP = 6;
			e2_13.alive = 1;
			Player.HP = 5;
			e2_14.HP = 6;
			e2_14.alive = 1;
			e2_15.HP = 6;
			e2_15.alive = 1;
			NumOfEnemy = 4;
		}
	}
	e2_12.StopAutoMove();
	e2_13.StopAutoMove();
	e2_14.StopAutoMove();
	e2_15.StopAutoMove();
	CloseHandle(ScreenIn5.hConsole);



	//第六关
	ScreenInitial ScreenIn6(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn6.hConsole);
	ScreenIn6.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn6.SetConsoleBufferSize(ScreenIn6.ScreenWidth, ScreenIn6.ScreenHeight);
	ScreenIn6.SetConsoleWindowSize(ScreenIn6.ScreenWidth, ScreenIn6.ScreenHeight);
	SMALL_RECT windowSize6 = { 0, 0, ScreenIn6.ScreenWidth - 1, ScreenIn6.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn6.hConsole, TRUE, &windowSize6);
	Player.ChangeXY(3.0, 2.0);
	Player.ChangeA(-1.0);
	Map map6(32, 32);
	map6.ChangeMaxLine(map6.MapWidth, map6.MapHeight);
	map6.map += L"################################";
	map6.map += L"G                              G";
	map6.map += L"G                              G";
	map6.map += L"G                              G";
	map6.map += L"G            #####             G";
	map6.map += L"G         ###     ###          G";
	map6.map += L"G       ##         ##          G";
	map6.map += L"G      #     $@$     #         G";
	map6.map += L"G     #     #####     #        G";
	map6.map += L"G     #     #   #     #        G";
	map6.map += L"G     #     # K #     #        G";
	map6.map += L"G      #     ###     #         G";
	map6.map += L"G       ##         ##          G";
	map6.map += L"G         ###     ###          G";
	map6.map += L"G            #####             G";
	map6.map += L"G                              G";
	map6.map += L"G                              G";
	map6.map += L"G                              G";
	map6.map += L"G                              G";
	map6.map += L"G      ##               ##     G";
	map6.map += L"G     #  #             #  #    G";
	map6.map += L"G     #  #             #  #    G";
	map6.map += L"G      ##               ##     G";
	map6.map += L"G                              G";
	map6.map += L"G        M          W          G";
	map6.map += L"G                              G";
	map6.map += L"G                              G";
	map6.map += L"G                              G";
	map6.map += L"G                              G";
	map6.map += L"G                              $";
	map6.map += L"G                               ";
	map6.map += L"###############################$";
	//敌人
	NumOfEnemy = 4;
	Enemy2 e2_16(29, 3);
	Enemy2 e2_17(29, 11);
	Enemy3 e3_2(7, 28);
	Enemy3 e3_3(17, 28);
	e2_16.StartAutoMove(map6.map, map6.MapWidth);
	e2_17.StartAutoMove(map6.map, map6.MapWidth);
	e3_2.StartAutoMove(map6.map, map6.MapWidth);
	e3_3.StartAutoMove(map6.map, map6.MapWidth);
	auto t6 = chrono::system_clock::now();
	auto p6 = chrono::system_clock::now();
	while (1)
	{
		p6 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime3 = p6 - t6;
		t6 = p6;
		move.ElapsedTime = elapsedtime3.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.RKeyD(Player.PlayerA);
		move.RKeyA(Player.PlayerA);
		move.RKeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map6.MapWidth, map6.map);
		move.RKeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map6.MapWidth, map6.map);
		move.RKeyQ(Player.PlayerA, Player.PlayerX, Player.PlayerY, map6.MapWidth, map6.map);
		move.RKeyE(Player.PlayerA, Player.PlayerX, Player.PlayerY, map6.MapWidth, map6.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map6.MapWidth, map6.MapHeight, map6.map);
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map6.map, map6.MapWidth, map6.MapHeight, map6.MaxMapLine,
			ScreenIn6.ScreenWidth, ScreenIn6.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map6.map, map6.MapWidth, map6.MapHeight, ScreenIn6.ScreenWidth, ScreenIn6.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人
		if (e2_16.alive)
			e2_16.FillEnemy(map6.map, map6.MapWidth);
		if (e2_17.alive)
			e2_17.FillEnemy(map6.map, map6.MapWidth);
		if (e3_3.alive)
			e3_3.FillEnemy(map6.map, map6.MapWidth);
		if (e3_2.alive)
			e3_2.FillEnemy(map6.map, map6.MapWidth);
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e2_16.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map6.MaxMapLine, map6.map, map6.MapWidth, NumOfEnemy);
			e2_17.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map6.MaxMapLine, map6.map, map6.MapWidth, NumOfEnemy);
			e3_2.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map6.MaxMapLine, map6.map, map6.MapWidth, NumOfEnemy);
			e3_3.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map6.MaxMapLine, map6.map, map6.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn6.ScreenWidth, ScreenIn6.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn6.ScreenWidth, ScreenIn6.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn6.ScreenWidth, ScreenIn6.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map6.MapWidth, map6.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn6.ScreenWidth * ScreenIn6.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn6.hConsole,
			Canvas.Canvas,
			ScreenIn6.ScreenWidth * ScreenIn6.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		WriteConsoleOutputAttribute(
			ScreenIn6.hConsole,
			Canvas.ColorBuffer,
			ScreenIn6.ScreenWidth * ScreenIn6.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		Sleep(1);
		if ((int)Player.PlayerX == 31 && (int)Player.PlayerY == 30 && GetAsyncKeyState((unsigned short)'F') & 0x8000)
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			e2_16.HP = 6;
			e2_16.alive = 1;
			e2_17.HP = 6;
			e2_17.alive = 1;
			Player.HP = 5;
			e3_2.HP = 13;
			e3_2.alive = 1;
			e3_3.HP = 13;
			e3_3.alive = 1;
			NumOfEnemy = 4;
		}
	}
	e2_16.StopAutoMove();
	e2_17.StopAutoMove();
	e3_2.StopAutoMove();
	e3_3.StopAutoMove();
	CloseHandle(ScreenIn6.hConsole);





	//第七关
	ScreenInitial ScreenIn7(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn7.hConsole);
	ScreenIn7.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn7.SetConsoleBufferSize(ScreenIn7.ScreenWidth, ScreenIn7.ScreenHeight);
	ScreenIn7.SetConsoleWindowSize(ScreenIn7.ScreenWidth, ScreenIn7.ScreenHeight);
	SMALL_RECT windowSize7 = { 0, 0, ScreenIn7.ScreenWidth - 1, ScreenIn7.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn7.hConsole, TRUE, &windowSize7);
	Player.ChangeXY(3.0, 2.0);
	Player.ChangeA(-1.0);
	Map map7(32, 32);
	map7.ChangeMaxLine(map7.MapWidth, map7.MapHeight);
	map7.map += L"################################";
	map7.map += L"G                              G";
	map7.map += L"G                              G";
	map7.map += L"G                              G";
	map7.map += L"G            #####             G";
	map7.map += L"G         ###     ###          G";
	map7.map += L"G       ##         ##          G";
	map7.map += L"G      #     $@$     #         G";
	map7.map += L"G     #     #####     #        G";
	map7.map += L"G     #     #   #     #        G";
	map7.map += L"G                              G";
	map7.map += L"G                              G";
	map7.map += L"G       R                      G";
	map7.map += L"G       R                      G";
	map7.map += L"G       R     K                G";
	map7.map += L"G       R     K                G";
	map7.map += L"G       R     K                G";
	map7.map += L"G       R     K                G";
	map7.map += L"G             K                G";
	map7.map += L"G             K                G";
	map7.map += L"G     #  #             #  #    G";
	map7.map += L"G     #  #             #  #    G";
	map7.map += L"G      ##               ##     G";
	map7.map += L"G              &               G";
	map7.map += L"G        M     &    W          G";
	map7.map += L"G              &               G";
	map7.map += L"G              &               G";
	map7.map += L"G              &               G";
	map7.map += L"G              &               G";
	map7.map += L"G                              $";
	map7.map += L"G                               ";
	map7.map += L"###############################$";
	//敌人
	NumOfEnemy = 4;
	Enemy2 e2_18(28, 28);
	Enemy3 e3_4(19, 4);
	Enemy3 e3_5(7, 28);
	Enemy3 e3_6(19, 28);
	e2_18.StartAutoMove(map7.map, map7.MapWidth);
	e3_4.StartAutoMove(map7.map, map7.MapWidth);
	e3_5.StartAutoMove(map7.map, map7.MapWidth);
	e3_6.StartAutoMove(map7.map, map7.MapWidth);
	auto t7 = chrono::system_clock::now();
	auto p7 = chrono::system_clock::now();
	while (1)
	{
		p7 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime3 = p7 - t7;
		t7 = p7;
		move.ElapsedTime = elapsedtime3.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.KeyQ(Player.PlayerA);
		move.KeyE(Player.PlayerA);
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map7.MapWidth, map7.map);
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map7.MapWidth, map7.map);
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map7.MapWidth, map7.map);
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map7.MapWidth, map7.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map7.MapWidth, map7.MapHeight, map7.map);
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map7.map, map7.MapWidth, map7.MapHeight, map7.MaxMapLine,
			ScreenIn7.ScreenWidth, ScreenIn7.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map7.map, map7.MapWidth, map7.MapHeight, ScreenIn7.ScreenWidth, ScreenIn7.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人
		if (e2_18.alive)
			e2_18.FillEnemy(map7.map, map7.MapWidth);
		if (e3_4.alive)
			e3_4.FillEnemy(map7.map, map7.MapWidth);
		if (e3_6.alive)
			e3_6.FillEnemy(map7.map, map7.MapWidth);
		if (e3_5.alive)
			e3_5.FillEnemy(map7.map, map7.MapWidth);
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e2_18.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map7.MaxMapLine, map7.map, map7.MapWidth, NumOfEnemy);
			e3_4.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map7.MaxMapLine, map7.map, map7.MapWidth, NumOfEnemy);
			e3_5.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map7.MaxMapLine, map7.map, map7.MapWidth, NumOfEnemy);
			e3_6.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map7.MaxMapLine, map7.map, map7.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn7.ScreenWidth, ScreenIn7.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn7.ScreenWidth, ScreenIn7.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn7.ScreenWidth, ScreenIn7.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map7.MapWidth, map7.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn7.ScreenWidth * ScreenIn7.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn7.hConsole,
			Canvas.Canvas,
			ScreenIn7.ScreenWidth * ScreenIn7.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		WriteConsoleOutputAttribute(
			ScreenIn7.hConsole,
			Canvas.ColorBuffer,
			ScreenIn7.ScreenWidth * ScreenIn7.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		Sleep(1);
		if ((int)Player.PlayerX == 31 && (int)Player.PlayerY == 30 && GetAsyncKeyState((unsigned short)'F') & 0x8000 )
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			e2_18.HP = 6;
			e2_18.alive = 1;
			e3_4.HP = 13;
			e3_4.alive = 1;
			Player.HP = 5;
			e3_5.HP = 13;
			e3_5.alive = 1;
			e3_6.HP = 13;
			e3_6.alive = 1;
			NumOfEnemy = 4;
		}
	}
	e2_18.StopAutoMove();
	e3_4.StopAutoMove();
	e3_5.StopAutoMove();
	e3_6.StopAutoMove();
	CloseHandle(ScreenIn7.hConsole);





	//第八关
	ScreenInitial ScreenIn8(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn8.hConsole);
	ScreenIn8.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn8.SetConsoleBufferSize(ScreenIn8.ScreenWidth, ScreenIn8.ScreenHeight);
	ScreenIn8.SetConsoleWindowSize(ScreenIn8.ScreenWidth, ScreenIn8.ScreenHeight);
	SMALL_RECT windowSize8 = { 0, 0, ScreenIn8.ScreenWidth - 1, ScreenIn8.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn8.hConsole, TRUE, &windowSize8);
	Player.ChangeXY(3.0, 2.0);
	Player.ChangeA(-1.0);
	Map map8(32, 32);
	map8.ChangeMaxLine(map8.MapWidth, map8.MapHeight);
	map8.map += L"###MWMMRRWKM##RGGKK##&&@@##KKGR#";
	map8.map += L"G                              G";
	map8.map += L"G                              G";
	map8.map += L"K                              &";
	map8.map += L"K                              &";
	map8.map += L"K                              &";
	map8.map += L"K                              &";
	map8.map += L"K                              &";
	map8.map += L"K                              &";
	map8.map += L"K                              &";
	map8.map += L"K                              &";
	map8.map += L"G                              G";
	map8.map += L"G                              G";
	map8.map += L"G                              G";
	map8.map += L"G                              G";
	map8.map += L"R                              G";
	map8.map += L"R                              W";
	map8.map += L"R                              W";
	map8.map += L"R                              W";
	map8.map += L"R                              W";
	map8.map += L"R                              W";
	map8.map += L"R                              W";
	map8.map += L"R                              W";
	map8.map += L"R                              G";
	map8.map += L"G                              G";
	map8.map += L"G                              G";
	map8.map += L"G                              G";
	map8.map += L"G                              G";
	map8.map += L"G                              G";
	map8.map += L"G                              $";
	map8.map += L"G                               ";
	map8.map += L"###MMMMMM######RRR######MMMM###$";
	//敌人
	NumOfEnemy = 10;
	Enemy2 e2_19(28, 3);
	Enemy2 e2_20(28, 5);
	Enemy2 e2_21(28, 8);
	Enemy2 e2_22(28, 10);
	Enemy2 e2_23(28, 13);
	Enemy3 e3_7(8, 19);
	Enemy3 e3_8(7, 21);
	Enemy3 e3_9(7, 23);
	Enemy3 e3_10(7, 25);
	Enemy3 e3_11(7, 28);
	e2_19.StartAutoMove(map8.map, map8.MapWidth);
	e2_20.StartAutoMove(map8.map, map8.MapWidth);
	e2_21.StartAutoMove(map8.map, map8.MapWidth);
	e2_22.StartAutoMove(map8.map, map8.MapWidth);
	e2_23.StartAutoMove(map8.map, map8.MapWidth);
	e3_7.StartAutoMove(map8.map, map8.MapWidth);
	e3_8.StartAutoMove(map8.map, map8.MapWidth);
	e3_9.StartAutoMove(map8.map, map8.MapWidth);
	e3_10.StartAutoMove(map8.map, map8.MapWidth);
	e3_11.StartAutoMove(map8.map, map8.MapWidth);
	auto t8 = chrono::system_clock::now();
	auto p8 = chrono::system_clock::now();
	while (1)
	{
		p8 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime3 = p8 - t8;
		t8 = p8;
		move.ElapsedTime = elapsedtime3.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.KeyQ(Player.PlayerA);
		move.KeyE(Player.PlayerA);
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MapWidth, map8.map);
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MapWidth, map8.map);
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MapWidth, map8.map);
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MapWidth, map8.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MapWidth, map8.MapHeight, map8.map);
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map8.map, map8.MapWidth, map8.MapHeight, map8.MaxMapLine,
			ScreenIn8.ScreenWidth, ScreenIn8.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map8.map, map8.MapWidth, map8.MapHeight, ScreenIn8.ScreenWidth, ScreenIn8.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人
		if (e2_19.alive)
			e2_19.FillEnemy(map8.map, map8.MapWidth);
		if (e2_20.alive)
			e2_20.FillEnemy(map8.map, map8.MapWidth);
		if (e2_21.alive)
			e2_21.FillEnemy(map8.map, map8.MapWidth);
		if (e2_22.alive)
			e2_22.FillEnemy(map8.map, map8.MapWidth);
		if (e2_23.alive)
			e2_23.FillEnemy(map8.map, map8.MapWidth);
		if (e3_7.alive)
			e3_7.FillEnemy(map8.map, map8.MapWidth);
		if (e3_8.alive)
			e3_8.FillEnemy(map8.map, map8.MapWidth);
		if (e3_9.alive)
			e3_9.FillEnemy(map8.map, map8.MapWidth);
		if (e3_10.alive)
			e3_10.FillEnemy(map8.map, map8.MapWidth);
		if (e3_11.alive)
			e3_11.FillEnemy(map8.map, map8.MapWidth);
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e2_19.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			e2_20.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			e2_21.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			e2_22.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			e2_23.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			e3_7.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			e3_8.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			e3_9.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			e3_10.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			e3_11.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map8.MaxMapLine, map8.map, map8.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn8.ScreenWidth, ScreenIn8.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn8.ScreenWidth, ScreenIn8.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn8.ScreenWidth, ScreenIn8.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map8.MapWidth, map8.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn8.ScreenWidth * ScreenIn8.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn8.hConsole,
			Canvas.Canvas,
			ScreenIn8.ScreenWidth * ScreenIn8.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		WriteConsoleOutputAttribute(
			ScreenIn8.hConsole,
			Canvas.ColorBuffer,
			ScreenIn8.ScreenWidth * ScreenIn8.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		Sleep(1);
		if ((int)Player.PlayerX == 31 && (int)Player.PlayerY == 30 && GetAsyncKeyState((unsigned short)'F') & 0x8000 )
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			e2_19.HP = 6;
			e2_19.alive = 1;
			e2_20.HP = 6;
			e2_20.alive = 1;
			e2_21.HP = 6;
			e2_21.alive = 1;
			e2_22.HP = 6;
			e2_22.alive = 1;
			e2_23.HP = 6;
			e2_23.alive = 1;
			e3_7.HP = 13;
			e3_7.alive = 1;
			e3_8.HP = 13;
			e3_8.alive = 1;
			e3_9.HP = 13;
			e3_9.alive = 1;
			Player.HP = 5;
			e3_10.HP = 13;
			e3_10.alive = 1;
			e3_11.HP = 13;
			e3_11.alive = 1;
			NumOfEnemy = 10;
		}
	}
	e2_19.StopAutoMove();
	e2_20.StopAutoMove();
	e2_21.StopAutoMove();
	e2_22.StopAutoMove();
	e2_23.StopAutoMove();
	e3_7.StopAutoMove();
	e3_8.StopAutoMove();
	e3_9.StopAutoMove();
	e3_10.StopAutoMove();
	e3_11.StopAutoMove();
	CloseHandle(ScreenIn8.hConsole);







	//第九关
	ScreenInitial ScreenIn9(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn9.hConsole);
	ScreenIn9.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn9.SetConsoleBufferSize(ScreenIn9.ScreenWidth, ScreenIn9.ScreenHeight);
	ScreenIn9.SetConsoleWindowSize(ScreenIn9.ScreenWidth, ScreenIn9.ScreenHeight);
	SMALL_RECT windowSize9 = { 0, 0, ScreenIn9.ScreenWidth - 1, ScreenIn9.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn9.hConsole, TRUE, &windowSize9);
	Player.ChangeXY(3.0, 2.0);
	Player.ChangeA(-1.0);
	Map map9(64, 32);
	map9.ChangeMaxLine(map9.MapWidth, map9.MapHeight);
	map9.map += L"################################################################";
	map9.map += L"#                        KKKKK       KKKKK                     #";
	map9.map += L"#    RGR              KKK     KKK KKK     KKK                  #";
	map9.map += L"#     G            KK            K            KK               #";
	map9.map += L"#     G           K                             K              #";
	map9.map += L"#     G           K                             K              #";
	map9.map += L"#     G            KK                         KK               #";
	map9.map += L"#     G              KK                     KK                 #";
	map9.map += L"#     G                KK                 KK                   #";
	map9.map += L"#     G                  KK             KK                     #";
	map9.map += L"#     G                    KK         KK                       #";
	map9.map += L"#     K                      KK     KK                         #";
	map9.map += L"#     K                        RRRRR                           #";
	map9.map += L"#    GKG                         K                             #";
	map9.map += L"#                                                              #";
	map9.map += L"#                                                              #";
	map9.map += L"#                                                              #";
	map9.map += L"#                                                              #";
	map9.map += L"#         MM                                                   #";
	map9.map += L"#      KK   MM        RKKKKK     K           R  WWWWKKWWWWWKW  #";
	map9.map += L"#    KK       K     KK      K    K           R        W        #";
	map9.map += L"#    K             K         R   K           R        W        #";
	map9.map += L"#    R            W           W  K           R        W        #";
	map9.map += L"#     M           W              K           R        W        #";
	map9.map += L"#      MMMM       W              K           R        W        #";
	map9.map += L"#          MM     W              K           R        W        #";
	map9.map += L"#            M    G              K           R        W        #";
	map9.map += L"#   R         M    G          W  K           R        W        #";
	map9.map += L"#    R        M     G        W    W         W         W        #";
	map9.map += L"#     R      M       G      W      W       W          W        $";
	map9.map += L"#      MMMMMM         MMMMMM        WWWWWWW                     ";
	map9.map += L"###############################################################$";
	//敌人
	NumOfEnemy = 0;
	auto t9 = chrono::system_clock::now();
	auto p9 = chrono::system_clock::now();
	while (1)
	{
		p9 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime3 = p9 - t9;
		t9 = p9;
		move.ElapsedTime = elapsedtime3.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.KeyQ(Player.PlayerA);
		move.KeyE(Player.PlayerA);
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map9.MapWidth, map9.map);
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map9.MapWidth, map9.map);
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map9.MapWidth, map9.map);
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map9.MapWidth, map9.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map9.MapWidth, map9.MapHeight, map9.map);
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map9.map, map9.MapWidth, map9.MapHeight, map9.MaxMapLine,
			ScreenIn9.ScreenWidth, ScreenIn9.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map9.map, map9.MapWidth, map9.MapHeight, ScreenIn9.ScreenWidth, ScreenIn9.ScreenHeight, Player.PlayerX, Player.PlayerY);
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			weapon.Attachline(Canvas.Canvas, ScreenIn9.ScreenWidth, ScreenIn9.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn9.ScreenWidth, ScreenIn9.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn9.ScreenWidth, ScreenIn9.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map9.MapWidth, map9.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn9.ScreenWidth * ScreenIn9.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn9.hConsole,
			Canvas.Canvas,
			ScreenIn9.ScreenWidth * ScreenIn9.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		WriteConsoleOutputAttribute(
			ScreenIn9.hConsole,
			Canvas.ColorBuffer,
			ScreenIn9.ScreenWidth * ScreenIn9.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		Sleep(1);
		if ((int)Player.PlayerX == 63 && (int)Player.PlayerY == 30 && GetAsyncKeyState((unsigned short)'F') & 0x8000 )
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			Player.HP = 5;
		}
	}
	CloseHandle(ScreenIn9.hConsole);



	//第十关
	ScreenInitial ScreenIn10(390, 130);
	SetConsoleActiveScreenBuffer(ScreenIn10.hConsole);
	ScreenIn10.SetConsoleFontSize(10, 5, L"MS Gothic");
	ScreenIn10.SetConsoleBufferSize(ScreenIn10.ScreenWidth, ScreenIn10.ScreenHeight);
	ScreenIn10.SetConsoleWindowSize(ScreenIn10.ScreenWidth, ScreenIn10.ScreenHeight);
	SMALL_RECT windowSize10 = { 0, 0, ScreenIn10.ScreenWidth - 1, ScreenIn10.ScreenHeight - 1 };
	SetConsoleWindowInfo(ScreenIn10.hConsole, TRUE, &windowSize10);
	Player.ChangeXY(3.0, 2.0);
	Player.ChangeA(-1.0);
	Map map10(32, 32);
	map10.ChangeMaxLine(map10.MapWidth, map10.MapHeight);
	map10.map += L"################################";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G        KKKKKKKKKKK           G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G        RRRRRRRRRRR           G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G        WWWWWWWWWWW           G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G         MMMMMMMMMM           G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G        &&&&&&&&&&            G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G         @@@@@@@@@            G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G                              G";
	map10.map += L"G                              $";
	map10.map += L"G                               ";
	map10.map += L"###############################$";
	//敌人
	NumOfEnemy = 4;
	Enemy4 e4(16, 28);
	Enemy3 e31(16, 9);
	Enemy3 e32(16, 13);
	Enemy3 e33(16, 17);
	e4.StartAutoMove(map10.map, map10.MapWidth);
	e31.StartAutoMove(map10.map, map10.MapWidth);
	e32.StartAutoMove(map10.map, map10.MapWidth);
	e33.StartAutoMove(map10.map, map10.MapWidth);
	auto t10 = chrono::system_clock::now();
	auto p10 = chrono::system_clock::now();
	while (1)
	{
		p10 = chrono::system_clock::now();
		chrono::duration<float>elapsedtime3 = p10 - t10;
		t10 = p10;
		move.ElapsedTime = elapsedtime3.count();
		HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
		DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_MOUSE_INPUT;
		SetConsoleMode(hStdin, fdwMode);
		move.KeyQ(Player.PlayerA);
		move.KeyE(Player.PlayerA);
		move.KeyW(Player.PlayerA, Player.PlayerX, Player.PlayerY, map10.MapWidth, map10.map);
		move.KeyS(Player.PlayerA, Player.PlayerX, Player.PlayerY, map10.MapWidth, map10.map);
		move.KeyA(Player.PlayerA, Player.PlayerX, Player.PlayerY, map10.MapWidth, map10.map);
		move.KeyD(Player.PlayerA, Player.PlayerX, Player.PlayerY, map10.MapWidth, map10.map);
		if ((GetAsyncKeyState((unsigned short)'R') & 0x8000) && move.NumOfSkill == 0)
			move.Skill(Player.PlayerA, Player.PlayerX, Player.PlayerY, map10.MapWidth, map10.MapHeight, map10.map);
		int MiceIs = move.GetMouseHorizontalDirection();
		if (MiceIs == -1)
			move.MiceL(Player.PlayerA);
		if (MiceIs == 1)
			move.MiceR(Player.PlayerA);
		Player.CheckA();
		Canvas.CanvasFilling(map10.map, map10.MapWidth, map10.MapHeight, map10.MaxMapLine,
			ScreenIn10.ScreenWidth, ScreenIn10.ScreenHeight, Player.PlayerX, Player.PlayerY, Player.PlayerA, Player.FOV);
		Canvas.MiniMap(map10.map, map10.MapWidth, map10.MapHeight, ScreenIn10.ScreenWidth, ScreenIn10.ScreenHeight, Player.PlayerX, Player.PlayerY);
		//敌人
		if (e4.alive)
			e4.FillEnemy(map10.map, map10.MapWidth);
		if (e31.alive)
			e31.FillEnemy(map10.map, map10.MapWidth);
		if (e32.alive)
			e32.FillEnemy(map10.map, map10.MapWidth);
		if (e33.alive)
			e33.FillEnemy(map10.map, map10.MapWidth);
		move.IsFire();
		if (move.fire)
		{
			PlaySound(L"LightSound.wav", NULL, SND_FILENAME | SND_ASYNC);
			e4.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map10.MaxMapLine, map10.map, map10.MapWidth, NumOfEnemy);
			e31.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map10.MaxMapLine, map10.map, map10.MapWidth, NumOfEnemy);
			e32.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map10.MaxMapLine, map10.map, map10.MapWidth, NumOfEnemy);
			e33.DeleEnemy(Player.PlayerA, Player.PlayerX, Player.PlayerY, map10.MaxMapLine, map10.map, map10.MapWidth, NumOfEnemy);
			weapon.Attachline(Canvas.Canvas, ScreenIn10.ScreenWidth, ScreenIn10.ScreenHeight, Canvas.ColorBuffer);
		}
		weapon.hand(Canvas.Canvas, ScreenIn10.ScreenWidth, ScreenIn10.ScreenHeight, Canvas.ColorBuffer);
		weapon.orb(Canvas.Canvas, ScreenIn10.ScreenWidth, ScreenIn10.ScreenHeight, Canvas.ColorBuffer);
		Player.CheckHP(map10.MapWidth, map10.map);
		DWORD dwBytesWritten = 0;
		Canvas.Canvas[ScreenIn10.ScreenWidth * ScreenIn10.ScreenHeight - 1] = '\0';
		WriteConsoleOutputCharacter(
			ScreenIn10.hConsole,
			Canvas.Canvas,
			ScreenIn10.ScreenWidth * ScreenIn10.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		WriteConsoleOutputAttribute(
			ScreenIn10.hConsole,
			Canvas.ColorBuffer,
			ScreenIn10.ScreenWidth * ScreenIn10.ScreenHeight,
			{ 0,0 },
			&dwBytesWritten
		);
		Sleep(1);
		if ((int)Player.PlayerX == 31 && (int)Player.PlayerY == 30 && GetAsyncKeyState((unsigned short)'F') & 0x8000 )
			break;
		if (Player.HP <= 0)
		{
			Player.PlayerX = 3.0; Player.PlayerY = 3.0;
			e4.HP = 20;
			e4.alive = 1;
			e31.HP = 13;
			e31.alive = 1;
			Player.HP = 5;
			e32.HP = 13;
			e32.alive = 1;
			e33.HP = 13;
			e33.alive = 1;
			NumOfEnemy = 4;
		}
	}
	e4.StopAutoMove();
	e3_4.StopAutoMove();
	e3_5.StopAutoMove();
	e3_6.StopAutoMove();
	CloseHandle(ScreenIn10.hConsole);


	HANDLE hDefault1 = GetStdHandle(STD_OUTPUT_HANDLE);
	bool keyPressed1 = false;
	DWORD written1;
	std::vector<std::wstring> story1 = {
	L"游戏结束，感谢游玩，大家敲代码的同时也要好好注意身体呀"
	};
	size_t currentLine1 = 0;
	while (true)
	{
		// 检测 F 键是否按下
		if (GetAsyncKeyState(0x46) & 0x8000)
		{
			if (!keyPressed1)
			{
				keyPressed1 = true;

				if (currentLine1 < story1.size())
				{
					// 输出当前行
					const wchar_t* text1 = story1[currentLine1].c_str();
					WriteConsoleW(hDefault1, text1, wcslen(text1), &written1, NULL);
					WriteConsoleW(hDefault1, L"\n", 1, &written1, NULL);
					currentLine1++;
				}
				else
				{
					// 所有行已输出，退出程序
					WriteConsoleW(hDefault1, L"\n", 13, &written1, NULL);
					break;
				}
			}
		}
		else
		{
			keyPressed = false; // 松开时清除状态
		}
		Sleep(10); // 防止CPU占用过高
	}




	move.runing = false;
	timerThread.join();

	return 0;
}