#include<iostream>
#include"Map.h"
using namespace std;

Map::Map(int w,int h)
{
	this->MapWidth = w;
	this->MapHeight = h;
	this->MaxMapLine = sqrt(w * w + h * h);
}

void Map::ChangeMaxLine(int w, int h)
{
	this->MaxMapLine = sqrt(w * w + h * h);
}
