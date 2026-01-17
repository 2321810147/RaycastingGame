#include<iostream>
#include"Enemy.h"
using namespace std;
std::mutex mapMutex;  // 只在一个 cpp 文件中定义
Enemy::Enemy(int a, int b)
{
    this->x = a;
    this->y = b;
}
void Enemy::Changexy(int a, int b,int h)
{
    this->x = a;
    this->y = b;
    this->HP = h;
}
void Enemy::DeleEnemy(float PlayerA, float PlayerX, float PlayerY,float MaxMapLine,wstring&Map,int MapWidth, int& NumOfEnemy)
{
    float dx = (float)this->x - PlayerX;
    float dy = (float)this->y - PlayerY;
    float dist = sqrt(dx * dx + dy * dy);
    float angleToEnemy = atan2f(dy,dx);
    float diff = fabs(PlayerA - angleToEnemy);
    if (diff < 0.1f && dist < MaxMapLine)
    {
        this->HP =this->HP-5;
        if (this->HP <= 0)
        {
            this->alive = false;
            Map[y * MapWidth + x] = ' ';
            NumOfEnemy--;
        }
    }
}
void Enemy::FillEnemy(wstring &Map,int MapWidth)
{
    if(Map[y * MapWidth + x] != 'E')
    Map[y*MapWidth+x]='E';
}
void Enemy::StartAutoMove(std::wstring& Map, int MapWidth) {
    running = true;

    autoMoveThread = std::thread([this, &Map, MapWidth]() {
        this->AutoMove(Map, MapWidth);
        });
}
void Enemy::AutoMove(std::wstring& Map, int MapWidth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dirDist(0, 3); // 0=上, 1=下, 2=左, 3=右

    while (alive && running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int dx = 0, dy = 0;
        switch (dirDist(gen)) {
        case 0: dy = -1; break; // 上
        case 1: dy = 1; break;  // 下
        case 2: dx = -1; break; // 左
        case 3: dx = 1; break;  // 右
        }

        int newX = x + dx;
        int newY = y + dy;

        if (newX >= 0 && newX < MapWidth &&
            newY >= 0 && newY < Map.size() / MapWidth &&
            this->alive) {

            std::lock_guard<std::mutex> lock(mapMutex);

            wchar_t& dest = Map[newY * MapWidth + newX];
            if (dest == L' '|| dest == L'O') {
                Map[y * MapWidth + x] = L' ';
                x = newX;
                y = newY;
                Map[y * MapWidth + x] = L'E';
            }
        }
    }
}
void Enemy::StopAutoMove() {
    running = false;  // 停止线程循环

    if (autoMoveThread.joinable()) {
        autoMoveThread.join();  // 等待线程结束
    }
}

//小兵，E
Enemy1::Enemy1(int a, int b) : Enemy(a, b) {
    this->HP = 4; // 覆盖父类的初始血量
}

void Enemy1::AutoMove(std::wstring& Map, int MapWidth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dirDist(0, 3); // 0=上, 1=下, 2=左, 3=右

    while (alive && running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int dx = 0, dy = 0;
        switch (dirDist(gen)) {
        case 0: dy = 0; break; // 上
        case 1: dy = 0;  break; // 下
        case 2: dx = 0; break; // 左
        case 3: dx = 0;  break; // 右
        }

        int newX = x + dx;
        int newY = y + dy;

        if (newX >= 0 && newX < MapWidth &&
            newY >= 0 && newY < Map.size() / MapWidth &&
            this->alive) {

            std::lock_guard<std::mutex> lock(mapMutex);

            // 检查目标点是否为空，避免冲突
            wchar_t& dest = Map[newY * MapWidth + newX];
            if (dest == L' ' || dest == L'O') {
                Map[y * MapWidth + x] = L' ';
                x = newX;
                y = newY;
                Map[y * MapWidth + x] = L'E';
            }
        }
    }
}
void Enemy1::FillEnemy(wstring& Map, int MapWidth)
{
    if (Map[y * MapWidth + x] != 'E')
        Map[y * MapWidth + x] = 'E';
}
//大兵，N
Enemy2::Enemy2(int a, int b) : Enemy(a, b) {
    this->HP = 6; // 覆盖父类的初始血量
}
void Enemy2::AutoMove(std::wstring& Map, int MapWidth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dirDist(0, 3); // 0=上, 1=下, 2=左, 3=右

    while (alive && running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int dx = 0, dy = 0;
        switch (dirDist(gen)) {
        case 0: dy = -1; break; // 上
        case 1: dy = 1;  break; // 下
        case 2: dx = -1; break; // 左
        case 3: dx = 1;  break; // 右
        }

        int newX = x + dx;
        int newY = y + dy;

        if (newX >= 0 && newX < MapWidth &&
            newY >= 0 && newY < Map.size() / MapWidth &&
            this->alive) {

            std::lock_guard<std::mutex> lock(mapMutex);

            // 检查目标点是否为空，避免冲突
            wchar_t& dest = Map[newY * MapWidth + newX];
            if (dest == L' ' || dest == L'O') {
                Map[y * MapWidth + x] = L' ';
                x = newX;
                y = newY;
                Map[y * MapWidth + x] = L'N';
            }
        }
    }
}
void Enemy2::FillEnemy(wstring& Map, int MapWidth)
{
    if (Map[y * MapWidth + x] != 'N')
        Map[y * MapWidth + x] = 'N';
}
//精锐,Y
Enemy3::Enemy3(int a, int b) : Enemy(a, b) {
    this->HP = 13; // 覆盖父类的初始血量
}
void Enemy3::AutoMove(std::wstring& Map, int MapWidth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dirDist(0, 3); // 0=上, 1=下, 2=左, 3=右

    while (alive && running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int dx = 0, dy = 0;
        switch (dirDist(gen)) {
        case 0: dy = -2; break; // 上
        case 1: dy = 2;  break; // 下
        case 2: dx = -2; break; // 左
        case 3: dx = 2;  break; // 右
        }

        int newX = x + dx;
        int newY = y + dy;

        if (newX >= 0 && newX < MapWidth &&
            newY >= 0 && newY < Map.size() / MapWidth &&
            this->alive) {

            std::lock_guard<std::mutex> lock(mapMutex);

            // 检查目标点是否为空，避免冲突
            wchar_t& dest = Map[newY * MapWidth + newX];
            if (dest == L' ' || dest == L'O') {
                Map[y * MapWidth + x] = L' ';
                x = newX;
                y = newY;
                Map[y * MapWidth + x] = L'Y';
            }
        }
    }
}
void Enemy3::FillEnemy(wstring& Map, int MapWidth)
{
    if (Map[y * MapWidth + x] != 'Y')
        Map[y * MapWidth + x] = 'Y';
}
//Boss,B
Enemy4::Enemy4(int a, int b) : Enemy(a, b) {
    this->HP = 20; // 覆盖父类的初始血量
}
void Enemy4::AutoMove(std::wstring& Map, int MapWidth) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dirDist(0, 3); // 0=上, 1=下, 2=左, 3=右

    while (alive && running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        int dx = 0, dy = 0;
        switch (dirDist(gen)) {
        case 0: dy = -3; break; // 上
        case 1: dy = 3;  break; // 下
        case 2: dx = -3; break; // 左
        case 3: dx = 3;  break; // 右
        }

        int newX = x + dx;
        int newY = y + dy;

        if (newX >= 0 && newX < MapWidth &&
            newY >= 0 && newY < Map.size() / MapWidth &&
            this->alive) {

            std::lock_guard<std::mutex> lock(mapMutex);

            // 检查目标点是否为空，避免冲突
            wchar_t& dest = Map[newY * MapWidth + newX];
            if (dest == L' ' || dest == L'O') {
                Map[y * MapWidth + x] = L' ';
                x = newX;
                y = newY;
                Map[y * MapWidth + x] = L'B';
            }
        }
    }
}
void Enemy4::FillEnemy(wstring& Map, int MapWidth)
{
    if (Map[y * MapWidth + x] != 'Y')
        Map[y * MapWidth + x] = 'Y';
}