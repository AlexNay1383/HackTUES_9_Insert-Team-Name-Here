#include <iostream>
#include <regex>
#include <map>
using namespace std;

bool email_is_valid(const string& email)
{
    const regex pattern(
        "(\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+");
    return regex_match(email, pattern);
}

class User
{
    public:
        string email = "";
        string password;
        int age;
        double averageSleep = 0, averagePulse = 0;

        double addSleep(int sleep)
        {
            this->totalSleep+=sleep;
            sleepCounter++;
            averageSleep=totalSleep/sleepCounter;
            return averageSleep;
        }
        double addPulse(int pulse)
        {
            this->totalPulse+=pulse;
            sleepCounter++;
            averagePulse=totalPulse/pulseCounter;
            return averagePulse;
        }


        User()
        {

        }
        User(string email, string password, int age)
        {
            this->email = email;
            this->password = password;
            this->age = age;
        }
        ~User()
        {

        }
    private:
        int totalPulse = 0, pulseCounter = 0;
        int totalSleep = 0, sleepCounter = 0;
};

map<string, User> users;
User active_user;

string Hash(string str)
{
   hash<string> hasher;
   const auto output = hasher(str);

   return to_string(output);
}

void Register()
{
    string email, password;
    int age;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter age: ";
    cin >> age;

    password = Hash(password);

    User user(email, password, age);
    string user_hash = Hash(email + password);

    users[user_hash] = user;
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
    if (users.find(user_hash) == users.end()) {
      // not found
      cout << "User not found\n";
    } else {
      // found
        active_user = users[user_hash];
    }

}

void LogOut()
{
    active_user = User();
}

int main()
{
    string input;
    cout << ""; //to finish
    cin >> input;

    for(int i=0; i < input.length();i++)
    {        char a = tolower(input[i]);
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
        cout << "\n";
        cin >> input;
    }

    return 0;
}
