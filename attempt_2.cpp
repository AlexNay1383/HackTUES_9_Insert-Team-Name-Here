#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <winuser.h>
#include <time.h>
#include <fstream>
#include <string>
#include <map>
using namespace std;

#define ACTIVITIES 5
#define DAYS 30

HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

//GRAPHICS ----------------------------------------------------------------------------------
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

    void print_str(string str, int x, int y, COLOR foreground_color, COLOR background_color, int dir)
    {
        for(int i=0;i<str.size();i++)
        {
            draw_char(str[i], x, y, foreground_color, background_color);
            if(dir) x++;
            else y++;
        }
    }
}

using namespace Graphics;

//GLOBAL FUNCTIONS --------------------------------------------------------------------------
bool act_valid(string str)
{
    if(str == "sleep" || str == "workout" || str == "pulse" || str == "steps" || str == "water")
        return true;
    return false;
}

int act_index(string str)
{
    if(str == "sleep") return 0;
    if(str == "workout") return 1;
    if(str == "pulse") return 2;
    if(str == "steps") return 3;
    if(str == "water") return 4;
}

//STRUCTS -----------------------------------------------------------------------------------
struct Info
{
    int value;
    bool entered;

    Info()
    {
        value = 0;
        entered = false;
    }
    ~Info()
    {

    }
};

//User
class User
{
    public:
        string username = "";
        string email = "";

        Info sport_info[ACTIVITIES][DAYS];

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

User active_user;



//FUNCTION WITH STRUCTS ---------------------------------------------------------------------
void enterData()
{
    string act, message;

    while(true)
    {
        cout << "What activity are you entering: ";
        cin >> act;
        if(act_valid(act)) break;
    }
    while(true)
    {
        if(act == "sleep" || act == "workout")
            message = "How many minutes did you " + act + " today?\n";
        if(act == "pulse")
            message = "How high was your pulse today(in bpm)?\n";
        if(act == "steps")
            message = "How many steps did you make today?\n";
        if(act == "water")
            message = "How much water did you drink today(in liters)?\n";
        cout << message;
        cin >> active_user.sport_info[act_index(act)][0].value;
        if(active_user.sport_info[act_index(act)][0].value >= 0) break;
    }
    active_user.sport_info[act_index(act)][0].entered = true;
}

void display_bar(int x, int y, int br, COLOR col)
{
    for(int i=0;i<br;i++)
    {
        draw_pixel(' ', x, y, col, col);
        y--;
    }
}

void display(string str, int top, int bottom)
{
    int pix_v = (top+top/2) / 20 + 1;
    int pix_br;
    int x = -1, y = 20;

    //Color
    COLOR col;

    for(int i=0;i<DAYS;i++)
    {
        x++;
        pix_br = (top+top/2) / active_user.sport_info[act_index(str)][day].value;

        if(active_user.sport_info[act_index(str)][day].value < bottom) col = RED;
        else if(active_user.sport_info[act_index(str)][day].value > top) col = BLUE;
        else col = GREEN;

        display_bar(x, y, pix_br, col);
    }
}

void display(int day, int top, int bottom)
{
    
}


int main()
{
    active_user.sport_info[2][0].value;
    display("sleep", 50, 20);

    return 0;
}

