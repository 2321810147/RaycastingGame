#include<iostream>
#include"ScreenCanvas.h"
using namespace std;

ScreenCanvas::ScreenCanvas(int ScreenWidth, int ScreenHeight)
{
	this->Canvas = new wchar_t[ScreenWidth*ScreenHeight];
	this->ColorBuffer = new WORD[ScreenWidth * ScreenHeight];
	for (int i = 0; i < ScreenWidth * ScreenHeight; i++) {
		ColorBuffer[i] = 7; // 默认白色（Windows 控制台颜色）
	}
}


void ScreenCanvas::CanvasFilling(wstring& map,int MapWidth, int MapHeight, float MaxMapLine,
	int ScreenWidth, int ScreenHeight, float PlayerX, float PlayerY, float PlayerA,float FOV)
{
	//缓冲加载画面
	//以一列列为单位生成整个画面
	for (int x = 0; x < ScreenWidth; x++)
	{
		//对于每一列，计算投影射线在世界空间中的角度
		float fRayAngle = (PlayerA - FOV / 2.0f) +     //计算视野的 最左侧边界角度（玩家视角向左偏移一半的FOV）
			((float)x / (float)ScreenWidth) * FOV;		 //将当前像素列 x 转换为 屏幕宽度比例（范围 [0, 1]）

		float fDistanceToWall = 0.0;
		//标记是否碰到墙
		bool HitWall = false;
		bool bBoundary = false;

		//玩家空间中射线的单位向量
		float fEyeX = cosf(fRayAngle);
		float fEyeY = sinf(fRayAngle);

		int Kind = 0;

		while (!HitWall && fDistanceToWall < MaxMapLine)
		{
			fDistanceToWall += 0.1f;
			int TestX = (int)(PlayerX + fEyeX * fDistanceToWall);
			int TestY = (int)(PlayerY + fEyeY * fDistanceToWall);

			//当TestX或TestY超出地图外边界时
			if (TestX >= MapWidth || TestX < 0 || TestY >= MapHeight || TestY < 0)
			{
				HitWall = true;
				//设置最大距离
				fDistanceToWall = MaxMapLine;

			}
			//当射线在边界范围内时，进行测试查看射线所在的单元格是否为墙体方块
			else
			{
				wchar_t choice = map[TestY * MapWidth + TestX];
				switch (choice)
				{
					case L'#':
						{
							HitWall = true;
							//基于距离和视角的边界检测算法，用于判断玩家是否靠近某个边界或是否正对某个角度,判断命中点
							vector<pair<float, float>>p;//距离值,视角点积值(物理意义：表示视线与目标方向的夹角余弦值)
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							//将p数组中成对的元素按照距离值d从最近到最远的顺序进行排序
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
						}
						break;
					case L'@':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 2;
						}
						break;
					case L'$':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 3;
						}
						break;
					case L'M':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 4;
						}
						break;
					case L'&':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 5;
						}
						break;
					case L'W':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 6;
						}
						break;
					case L'G':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 7;
						}
						break;
					case L'R':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 8;
						}
						break;
					case L'K':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 9;
						}
						break;
					case L'E':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 10;
						}
						break;
					case L'N':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 11;
						}
						break;
					case L'Y':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 12;
						}
						break;
					case L'B':
						{
							HitWall = true;
							vector<pair<float, float>>p;
							for (int tx = 0; tx < 2; tx++)
							{
								for (int ty = 0; ty < 2; ty++)
								{
									float vy = (float)TestY + ty - PlayerY;
									float vx = (float)TestX + tx - PlayerX;
									float d = sqrt(vx * vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							}
							sort(p.begin(), p.end(),
								[](const pair <float, float>& left, const pair<float, float>& right) {return left.first < right.first; });
							float fBound = 0.005;
							if (acos(p[0].second) < fBound)bBoundary = true;
							if (acos(p[1].second) < fBound)bBoundary = true;
							Kind = 13;
						}
						break;
					default:
						break;
				}
			}

		}
		
		//计算到天花板和地板的距离
		int Ceiling = (float)(ScreenHeight / 2.0) - ScreenHeight / ((float)fDistanceToWall);
		int Floor = ScreenHeight - Ceiling;

		//设置不同灰度色块以实现视野远近下墙的渐变效果
		short Shade = ' ';
		if (fDistanceToWall <= MaxMapLine / 4.0f&&!Kind)
			Shade = 0x2588;
		else if (fDistanceToWall < MaxMapLine / 3.0f&&!Kind)
			Shade = 0x2593;
		else if (fDistanceToWall < MaxMapLine / 2.0f&&!Kind)
			Shade = 0x2592;
		else if (fDistanceToWall < MaxMapLine&&!Kind)
			Shade = 0x2591;
		else if (Kind)
		{
			switch (Kind)
			{
			case 2:
				Shade = '@';
				break;
			case 3:
				Shade = '$';
				break;
			case 4:
				Shade = 'M';
				break;
			case 5:
				Shade = '&';
				break;
			case 6:
				Shade = 'W';
				break;
			case 7:
				Shade = 'G';
				break;
			case 8:
				Shade = 'R';
				break;
			case 9:
				Shade = 'K';
				break;
			case 10:
				Shade = 'E';
				break;
			case 11:
				Shade = 'N';
				break;
			case 12:
				Shade = 'Y';
				break;
			case 13:
				Shade = 'B';
				break;
			default:
				break;
			}
		}
		else
			Shade = ' ';
		if (bBoundary)Shade = ' ';

		//填充每一列
		for (int y = 0; y < ScreenHeight; y++)
		{
			if (y < Ceiling)
			{
				int c = y * ScreenWidth + x;
				this->Canvas[c] = ' ';
				this->ColorBuffer[c] = 7;
			}
			else if (y > Ceiling && y <= Floor)
			{
				int t = y * ScreenWidth + x;
				this->Canvas[t] = Shade;
				if (!Kind)
					this->ColorBuffer[t] =7;
				else
				{
					switch (Kind)
					{
					case 2:
						this->ColorBuffer[t] = 47;
						break;
					case 3:
						this->ColorBuffer[t] = 46;
						break;
					case 4:
						this->ColorBuffer[t] = 230;
						break;
					case 5:
						this->ColorBuffer[t] = 235;
						break;
					case 6:
						this->ColorBuffer[t] = 174;
						break;
					case 7:
						this->ColorBuffer[t] = 180;
						break;
					case 8:
						this->ColorBuffer[t] = 150;
						break;
					case 9:
						this->ColorBuffer[t] = 190;
						break;
					case 10:
						this->ColorBuffer[t] = 240;
						break;
					case 11:
						this->ColorBuffer[t] = 60;
						break;
					case 12:
						this->ColorBuffer[t] = 80;
						break;
					case 13:
						this->ColorBuffer[t] = 70;
						break;
					default:
						break;
					}
				}
			}
			else
			{
				//设置不同灰度色块以实现视野远近下地板的渐变效果
				short Shade1 = ' ';
				float F = 1.0f - (((float)y - ScreenHeight / 2.0f) / ((float)ScreenHeight / 2.0f));
				if (F < 0.25)			Shade1 = '#';
				else if (F < 0.5)			Shade1 = 'x';
				else if (F < 0.75)			Shade1 = '-';
				else if (F < 0.9)			Shade1 = '.';
				else						Shade1 = ' ';
				int o = y * ScreenWidth + x;
				this->Canvas[o] = Shade1;
				this->ColorBuffer[o] = 7;
			}
		}

	}

	//准心
	this->Canvas[(ScreenHeight - 1) / 2 * ScreenWidth + ScreenWidth / 2] = 'o';
	this->Canvas[(ScreenHeight - 1) / 2 * ScreenWidth + ScreenWidth / 2 + 2] = 'o';
	this->Canvas[(ScreenHeight - 1) / 2 * ScreenWidth + ScreenWidth / 2 - 2] = 'o';
	this->Canvas[((ScreenHeight - 1) / 2 + 2) * ScreenWidth + ScreenWidth / 2] = 'o';
	this->Canvas[((ScreenHeight - 1) / 2 - 2) * ScreenWidth + ScreenWidth / 2] = 'o';

}

void ScreenCanvas::MiniMap(wstring map, int MapWidth, int MapHeight, int ScreenWidth, int ScreenHeight, float PlayerX, float PlayerY)
{
	for (int x = 0; x < MapWidth; x++)
	{
		for (int y = 0; y < MapHeight; y++)
		{
			int idx = (y + 1) * ScreenWidth + x;
			Canvas[idx] = map[y * MapWidth + x];
			wchar_t enemy = Canvas[idx];
			switch (enemy)
			{
			case 'B':
				ColorBuffer[idx] = 4;
				break;
			case 'Y':
				ColorBuffer[idx] = 4;
				break;
			case 'N':
				ColorBuffer[idx] = 4;
				break;
			case 'E':
				ColorBuffer[idx] = 4;
				break;
			default:
				ColorBuffer[idx] = 7; // 默认白色
				break;
			}
		}
	}

	//玩家在小地图的位置
	int playerIdx = ((int)PlayerY + 1) * ScreenWidth + (int)PlayerX;
	this->Canvas[playerIdx] = L'O';
	ColorBuffer[playerIdx] = 2; // 绿色（Windows 控制台颜色代码）
}

