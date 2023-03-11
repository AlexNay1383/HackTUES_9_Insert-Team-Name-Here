#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <winuser.h>
#include <time.h>
#include <fstream>
#include <string>
#include <map>
#include <regex>
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

string Hash(string str)
{
   hash<string> hasher;
   const auto output = hasher(str);

   return to_string(output);
}

string encryptfunc(int key,string text)
{
    char temp;
    int i;
  for(i = 0; text[i] != '\0'; ++i){
    temp = text[i];
    if((temp >= 'a' && temp <= 'z')) {
      temp = temp + key;

      if(temp > 'z'){
        temp = temp - 'z' + 'a' - 1;
      }

      text[i] = temp;
    }
    else if(temp >= '0' && temp <= 'Z'){
      temp = temp + key;

      if(temp > 'Z'){
        temp = temp - 'Z' + '0' - 1;
      }

      text[i] = temp;
    }
  }
    return text;
}
string decryptfunc(int key,string text)
{
    char temp;
    int i;
  for(i = 0; text[i] != '\0'; ++i){
    temp = text[i];
    if((temp >= 'a' && temp <= 'z')){
      temp = temp - key;

      if(temp < 'a' && temp > '9'){
        temp = temp + 'z' - 'a' + 1;
      }

      text[i] = temp;
    }
    else if(temp >= '0' && temp <= 'Z'){
      temp = temp - key;

      if(temp < '0'){
        temp = temp + 'Z' - '0' + 1;
      }

      text[i] = temp;
    }
  }

  return text;

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
        string password = "";
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
};

map<string, User> users;
User active_user;
int logged_in = false;

//User homepage
bool email_is_valid(string email)
{
    string userEmailRegex = "([_a-z0-9-]+@[a-z0-9-]+.[a-z0-9-]{2,4})";
    return regex_match(email, regex(userEmailRegex));
}

void Register()
{
    string email, password, email1;

    cout << "Enter email: ";
    cin >> email;
    bool isValid = email_is_valid(email);

    while(!isValid)
    {
        cout << "\nInvalid email\n" << endl;
        cout << "Enter email: ";
        cin >> email;
        isValid = email_is_valid(email);
    }

    int encKey = email.size();

    cout << "Enter password: ";
    cin >> password;

    password = Hash(password);

    User user(email, password);
    string user_hash = Hash(email + password);

    users[user_hash] = user;

    fstream file;
    file.open("Users/"+user_hash+".txt",ios::out);
    if(!file)
    {
        cout<<"Error in creating file!!!";
    }
    file.close();
    ifstream fileReader;
    fileReader.open("Users/"+user_hash+".txt");
}

void LogIn()
{
    string email, password;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    password = Hash(password);

    string user_hash = Hash(email + password);
    ifstream file;
    file.open("Users/"+user_hash+".txt");
    if(!file)
    {
        cout << "User not found\n";
    }
    else if(!logged_in)
    {
        active_user = users[user_hash];
        logged_in = true;
        cout << "You have successfully logged in"<<endl;
    }
    
}

void LogOut()
{
    active_user = User();
    logged_in = false;
    cout << "\nYou have successfully logged out."<<endl;
}


//FUNCTION WITH STRUCTS ---------------------------------------------------------------------
void enterData()
{
    string act, message;
    int day;

    while(true)
    {
        cout << "What activity are you entering: ";
        cin >> act;
        if(act_valid(act)) break;
        cout << "\nPlease enter sleep, workout, pulse, steps or water\n";
    }
    while(true)
    {
        cout << "How many days ago did this activity happen(max up to 29 days ago): ";
        cin >> day;
        if(day < 30 && day >=0) break;
        cout << "\nPlease enter a valid value\n";
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
            message = "How much water did you drink today(in mililiters)?\n";
        cout << message;
        cin >> active_user.sport_info[act_index(act)][day].value;
        if(active_user.sport_info[act_index(act)][day].value >= 0) break;
        cout << "Please enter a positive integer";
    }
    active_user.sport_info[act_index(act)][day].entered = true;
}

void grade(int i, int& top, int& bottom)
{
    switch(i)
    {
        case 0:
            bottom = 420;
            top = 599;
            break;
        case 1:
            bottom = 20;
            top = 59;
            break;
        case 2:
            bottom = 60;
            top = 99;
            break;
        case 3:
            bottom = 4000;
            top = 17999;
            break;
        case 4:
            bottom = 1500;
            top = 3499;
            break;
    }
}


void display_bar(int x, int y, int br, COLOR col)
{
    for(int i=0;i<br;i++)
    {
        draw_pixel(' ', x, y, col, col);
        y--;
    }
}

void display(string str)
{
    system("cls");
    int top, bottom;
    grade(act_index(str), top, bottom);
    int pix_v = (top+top/2) / 20 + 1;
    int pix_br;
    COLOR col;
    int x = 1, y = 20;

    for(int i=0;i<DAYS;i++)
    {
        x++;
        pix_br = active_user.sport_info[act_index(str)][i].value / pix_v;

        if(active_user.sport_info[act_index(str)][i].value < bottom) col = RED;
        else if(active_user.sport_info[act_index(str)][i].value > top) col = BLUE;
        else col = GREEN;

        display_bar(x, y, pix_br, col);
    }

    print_str("Days", 28, y+2, WHITE, BLACK, 1);
    print_str("Value", 0, 7, WHITE, BLACK, 0);

    print_str("- Too Little", 3, 24, WHITE, BLACK, 1);
    print_str("- Good", 3, 25, WHITE, BLACK, 1);
    print_str("- Too Much", 3, 26, WHITE, BLACK, 1);
    draw_pixel(' ', 0, 24, RED, RED);
    draw_pixel(' ', 0, 25, GREEN, GREEN);
    draw_pixel(' ', 0, 26, BLUE, BLUE);
}


int main()
{
    string input;
    cout << "List of commands:\nregister - register\nlogin - log in an existing account\nlogout - log out of the current account\nexit - exits the program\nenter - enter information\nsave - save changes to information\ndisplay - display information";

    for(int i=0; i < input.length();i++)
    {
        char a = tolower(input[i]);
        input[i]=a;
    }
    while(input!="exit"){

        if(input=="login"){
            LogIn();
        }
        else if(input=="logout"){
            LogOut();
        }
        else if(input=="register"){
            Register();
        }
        else if(input=="enter"){
            cout << "\nenter \"leave\" to exit enter mode\n";
            do{
                cin >> input;
                
            }
        }
        else if()
        
        cout << "\n";
        cin >> input;
    }

    int temp;
    cin >> temp;

    return 0;
}

