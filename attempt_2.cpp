#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <winuser.h>
#include <time.h>
#include <fstream>
#include <string>
#include <map>
using namespace std;

HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

//Graphics
namespace Graphics
{
    enum COLOR
    {
        BLACK = 0,
        BLUE = FOREGROUND_BLUE,
        GREEN = FOREGROUND_GREEN,
        RED = FOREGROUND_RED,

        CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN,
        BROWN = FOREGROUND_RED | FOREGROUND_GREEN,
        PURPLE = FOREGROUND_RED | FOREGROUND_BLUE,
        GREY = 0 | FOREGROUND_INTENSITY,
        YELLOW = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        PINK = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        WHITE = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,

        LIGHT_GREY = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,
        LIGHT_BLUE = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
        LIGHT_CYAN = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        LIGHT_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        LIGHT_RED = FOREGROUND_RED | FOREGROUND_INTENSITY
    };

    void draw_char(char ch, int x, int y, COLOR foreground_color, COLOR background_color)
    {
        CHAR_INFO ch_info;
        ch_info.Char.AsciiChar = ch;
        ch_info.Attributes = foreground_color | (background_color << 4);

        COORD buf_size = {1, 1};
        COORD buf_coord = {0, 0};
        SMALL_RECT screen_pos = {x, y, x+1, y+1};
        WriteConsoleOutput(hConsoleOutput, &ch_info, buf_size, buf_coord, &screen_pos);
    }

    void draw_pixel(char ch, int x, int y, COLOR foreground_color, COLOR background_color)
    {
        draw_char(ch, x*2, y, foreground_color, background_color);
        draw_char(ch, x*2+1, y, foreground_color, background_color);
    }
}

class Day
{
    int value;

    void display_day()
    {

    }
};

//Sports data
class Activity
{
    public:
        Day day[30];

        void display_activity()
        {
            system("cls");
        }

};

//User
class User
{
    public:
        string username = "";
        string email = "";
        
        int age;
        int height;
        int weight;

        map<string, Activity> data;

        User()
        {

        }
        User(string email, string password)
        {
            this->email = email;
            this->password = password;
        }
        ~User()
        {

        }
    private:
        string password;

};


int main()
{

}