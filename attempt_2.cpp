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

struct Point
{
    int x = 0;
    int y = 0;

    Point()
    {

    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    ~Point()
    {

    }
};

Point pointer(0, 0);

bool valid_act(string str)
{
    if(str == "sleep" || str == "workout" || str == "pulse" || str == "steps" || str == "water")
    {
        return true;
    }
    return false;
}

int index_act(string str)
{
    int i=0;
    if(str == "sleep") i++;
    if(str == "sleep" || str == "workout") i++;
    if(str == "sleep" || str == "workout" || str == "pulse") i++;
    if(str == "sleep" || str == "workout" || str == "pulse" || str == "steps") i++;
    return i;
}

struct Info
{
    int value;
    bool entered = false;
};

struct Data
{
    Info info[ACTIVITIES][DAYS];

    void display(string activity)
    {
        for(int i=0;i<DAYS;i++)
        {
            //display info[act][i]

        }
    }
    void display(int day)
    {
        for(int i=0;i<ACTIVITIES;i++)
        {
            //display info[i][day]
        }
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

        Data data;

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

void enterData()
{
    string act, message;

    cout << "What activity are you entering: ";
    cin >> act;

    if(valid_act(act))
    {
        if(act == "sleep" || act == "workout")
            message = "How many hours did you " + act + " today?\n";
        if(act == "pulse")
            message = "How high was your pulse today?\n";
        if(act == "steps")
            message = "How many steps did you make today?\n";
        if(act == "water")
            message = "How much water did you drink today?\n";
        cout << message;
        cin >> active_user.data.info[index_act(act)][0].value;
        active_user.data.info[index_act(act)][0].entered = true;
    }
    else cout << "Invalid activity. Choose from sleep, workout, pulse, steps and water";
}


int main()
{
    enterData();

    return 0;
}
