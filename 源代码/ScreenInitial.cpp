#include<iostream>
#include"ScreenInitial.h"
using namespace std;

ScreenInitial::ScreenInitial(int w, int h)
{
	this->ScreenWidth = w;
	this->ScreenHeight = h;
}

void ScreenInitial::SetConsoleBufferSize(int cols, int lines)
{
	if (this->hConsole == INVALID_HANDLE_VALUE) return;

	// 设置屏幕缓冲区大小（以字符为单位）
	COORD size = { (SHORT)cols, (SHORT)lines };
	SetConsoleScreenBufferSize(this->hConsole, size);
}

BOOL ScreenInitial::SetConsoleWindowSize(int width, int height) {

	SMALL_RECT rect = {
		0, 0,
		(SHORT)(width - 1),  // 右边界 = width - 1
		(SHORT)(height - 1)  // 下边界 = height - 1
	};

	return SetConsoleWindowInfo(this->hConsole, TRUE, &rect);
}

CONSOLE_FONT_INFOEX ScreenInitial::GetCurrentConsoleFont()
{
    CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };
    GetCurrentConsoleFontEx(this->hConsole, FALSE, &cfi);
    return cfi;
}

BOOL ScreenInitial::SetConsoleFontSize(int width, int height, const wchar_t* fontName)
{
    CONSOLE_FONT_INFOEX cfi = { sizeof(CONSOLE_FONT_INFOEX) };

    // 获取当前字体设置以保留其他属性
    GetCurrentConsoleFontEx(this->hConsole, FALSE, &cfi);

    // 设置字体尺寸
    cfi.dwFontSize.X = width;
    cfi.dwFontSize.Y = height;

    // 设置字体名称（必须是等宽字体才能生效）
    wcscpy_s(cfi.FaceName, fontName);  // 例如 L"Consolas"、L"Lucida Console"

    return SetCurrentConsoleFontEx(this->hConsole, FALSE, &cfi);
}

