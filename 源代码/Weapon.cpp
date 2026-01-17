#include"Weapon.h"
using namespace std;

void Weapon::hand(wchar_t*& Canvas, int canvasWidth, int canvasHeight, WORD*& ColorBuffer)
{
    const wchar_t* hand[] =
    {
     L"                 *|*                                                                                             *|*                 ",
     L"               000|888                                                                                         888|000               ",
     L"           0000000|88888                                                                                     88888|0000000           ",
     L"        0000000000|8888888                                                                                 8888888|0000000000        ",
     L"     0000000000000|888888888                                                                             888888888|0000000000000     ",
     L"   000000000000000|88888888888                                                                         88888888888|000000000000000   ",
     L"   000000000000000|88888888888                                                                         88888888888|000000000000000   ",
     L"   000000000000000|88888888888                                                                         88888888888|000000000000000   ",
     L"  000000000000000|88888888888                                                                           88888888888|000000000000000  ",
     L"  000000000000000|88888888888                                                                           88888888888|000000000000000  ",
     L"  000000000000000|88888888888                                                                           88888888888|000000000000000  ",
     L"  000000000000000|88888888888                                                                           88888888888|000000000000000  ",
     L"  000000000000000|88888888888                                                                           88888888888|000000000000000  ",
     L" 000000000000000|888888888888                                                                           888888888888|000000000000000 ",
     L" 000000000000000|88888888888                                                                             88888888888|000000000000000 ",
     L" 000000000000000|88888888888                                                                             88888888888|000000000000000 ",
     L" 000000000000000|88888888888                                                                             88888888888|000000000000000 ",
     L" 000000000000000|88888888888                                                                             88888888888|000000000000000 ",
     L" 000000000000000|88888888888                                                                             88888888888|000000000000000 ",
     L"000000000000000|888888888888                                                                             888888888888|000000000000000",
     L"000000000000000|888888888888                                                                             888888888888|000000000000000",
     L"000000000000000|888888888888                                                                             888888888888|000000000000000",
     L"000000000000000|888888888888                                                                             888888888888|000000000000000",
     L"000000000000000|88888888888                                                                               88888888888|000000000000000",
     L"000000000000000|88888888888                                                                               88888888888|000000000000000"
    };

    int orbHeight = sizeof(hand) / sizeof(hand[0]);
    int orbWidth = wcslen(hand[0]);

    // 放在画布下方中心
    int startX = (canvasWidth - orbWidth) / 2;
    int startY = canvasHeight - orbHeight; 

    for (int y = 0; y < orbHeight; y++)
    {
        for (int x = 0; x < orbWidth; x++)
        {
            int canvasX = startX + x;
            int canvasY = startY + y;
            int t = canvasY * canvasWidth + canvasX;
            if (hand[y][x]!=' ')
            {
                Canvas[t] = hand[y][x];
                ColorBuffer[t] = 229;
            }
        }
    }
}
void Weapon::orb(wchar_t*& Canvas, int canvasWidth, int canvasHeight, WORD*& ColorBuffer)
{
    const wchar_t* orb[] = 
    {                                                                     
        L"               ~~       #######       ~~               ",
        L"            ..**     #############     **..            ",
        L"         ..*       ##################      *..         ",
        L"       ..*     #########################     *..       ",
        L"     ..~     #############################     ~..     ",
        L"    ..*     ###############################     *..    ",
        L"    ..*     ###############################     *..    ",
        L"     ..~     #############################     ~..     ",
        L"       ..*     #########################     *..       ",
        L"         ..*      ###################      *..         ",
        L"            ..**     #############     **..            ",
        L"               ~~       #######       ~~               "
    };

    int orbHeight = sizeof(orb) / sizeof(orb[0]);
    int orbWidth = wcslen(orb[0]);

    // 放在画布下方中心
    int startX = (canvasWidth - orbWidth) / 2;
    int startY = canvasHeight - orbHeight-1;// 上留一行边距

    for (int y = 0; y < orbHeight; y++)
    {
        for (int x = 0; x < orbWidth; x++)
        {
            int canvasX = startX + x;
            int canvasY = startY + y;
            int t = canvasY * canvasWidth + canvasX;
            if (orb[y][x] != ' ')
            {
                Canvas[t] = orb[y][x];
                ColorBuffer[t] = 145;
            }
        }
    }
}

void Weapon::Attachline(wchar_t*& Canvas, int canvasWidth, int canvasHeight, WORD*& ColorBuffer)
{
    const wchar_t* beamFrame50[] = {
     L"                                      |                                     ",
     L"                                      |                                     ",
     L"                                      |                                     ",
     L"                                      |                                     ",
     L"                                      |                                     ",
     L"                                      |                                     ",
     L"                                      |                                     ",
     L"                                      |                                     ",
     L"                                      *                                     ",
     L"                                     / \\                                    ",
     L"                                    /   \\                                   ",
     L"                                   /     \\                                  ",
     L"                                  /       \\                                 ",
     L"                                 /         \\                                ",
     L"                                /           \\                               ",
     L"                               /             \\                              ",
     L"                              /               \\                             ",
     L"                        =====/                 \\=====                       ",
     L"                       /                             \\                      ",
     L"                      /                               \\                     ",
     L"                     /                                 \\                    ",
     L"                    /                                   \\                   ",
     L"                   /                                     \\                  ",
     L"                  /                                       \\                 ",
     L"                 /                                         \\                ",
     L"                /                                           \\               ",
     L"               /                                             \\              ",
     L"              /                                               \\             ",
     L"             /                                                 \\            ",
     L"            /                                                   \\           ",
     L"           /                                                     \\          ",
     L"          /                                                       \\         ",
     L"         /                                                         \\        ",
     L"        /                                                           \\       ",
     L"       /                                                             \\      ",
     L"      /                                                               \\     ",
     L"     /                                                                 \\    ",
     L"    /                                                                   \\   ",
     L"   /                                                                     \\  ",
     L"  /                                                                       \\ "
    };

    int orbHeight = sizeof(beamFrame50) / sizeof(beamFrame50[0]);
    int orbWidth = wcslen(beamFrame50[0]);

    // 放在画布下方中心
    int startX = (canvasWidth - orbWidth) / 2;
    int startY = canvasHeight - orbHeight - 25;// 上留一行边距

    for (int y = 0; y < orbHeight; y++)
    {
        for (int x = 0; x < orbWidth; x++)
        {
            int canvasX = startX + x;
            int canvasY = startY + y;
            int t = canvasY * canvasWidth + canvasX;
            if (beamFrame50[y][x] != ' ')
            {
                Canvas[t] = beamFrame50[y][x];
                ColorBuffer[t] = 145;
            }
        }
    }
}