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
        double averageSleep = 0, averagePulse = 0, averageWorkout = 0, averageSteps = 0;

    private:
        int totalPulse = 0, pulseCounter = 0;
        int totalSleep = 0, sleepCounter = 0;
        int totalWorkout = 0, workoutCounter = 0;
        int totalSteps = 0, stepsCounter = 0;

    public:
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
            pulseCounter++;
            averagePulse=totalPulse/pulseCounter;
            return averagePulse;
        }
        double addWorkout(int workout)
        {
            this->totalWorkout+=workout;
            sleepCounter++;
            averageWorkout=totalWorkout/workoutCounter;
            return averageWorkout;
        }
        double addSteps(int steps)
        {
            this->totalSteps+=steps;
            stepsCounter++;
            averageSteps=totalSteps/stepsCounter;
            return averageSteps;
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
};


map<string, User> users;
User active_user;
int logged_in = false;

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
    cout << "You have successfully registered";
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
    if (users.find(user_hash) == users.end())
    {
      // not found
      cout << "User not found\n";
    }
    else if(!logged_in)
    {
      // found
        active_user = users[user_hash];
        logged_in = true;
    }
    cout << "You have successfully logged in";
}

void LogOut()
{
    active_user = User();
    logged_in = false;
}

void AddSleep()
{
    if(active_user.email!="")
    {
        int sleephours;
        double avg_sleep;
        cout << "How much did you sleep?: ";
        cin >> sleephours;
        avg_sleep=active_user.addSleep(sleephours);
        cout << "Your average amount of sleep is: " << avg_sleep << endl;

        if (active_user.age < 18) {
        if (avg_sleep >= 8) {
          cout << "Your average amount of sleep for one week is good." << endl;
        } else {
          cout << "Your average amount of sleep for one week is bad." << endl;
        }
      } else {
        if (avg_sleep >= 7) {
          cout << "Your average amount of sleep for one week is good." << endl;
        } else {
          cout << "Your average amount of sleep for one week is bad." << endl;
        }
      }
    }
}

void addPulse()
{
    if(active_user.email!=""){
        int pulse;
        cout << "What was your pulse?" << endl;
        cin >> pulse;
        double averagePulse = active_user.addPulse(pulse);
        cout << "Your average pulse is: " << averagePulse;
        switch(active_user.age)
{
    case 1:;
    case 2:
        {
            if(averagePulse>130) cout<<"\nPulse is too high";
            else if(averagePulse<80) cout<<"\nPulse is too low";
            else cout<<"\nPulse is within acceptable values";
            break;
        }
    case 3:;
    case 4:
        {
            if(averagePulse>120) cout<<"\nPulse is too high";
            else if(averagePulse<80) cout<<"\nPulse is too low";
            else cout<<"\nPulse is within acceptable values";
            break;
        }
    case 5:;
    case 6:
        {
            if(averagePulse>115) cout<<"\nPulse is too high";
            else if(averagePulse<75) cout<<"\nPulse is too low";
            else cout<<"\nPulse is within acceptable values";
            break;
        }
    case 7:;
    case 8:;
    case 9:
        {
            if(averagePulse>110) cout<<"\nPulse is too high";
            else if(averagePulse<70) cout<<"\nPulse is too low";
            else cout<<"\nPulse is within acceptable values";

            break;
        }
    default :
        {
            if(averagePulse>100) cout<<"\nPulse is too high";
            else if(averagePulse<60) cout<<"\nPulse is too low";
            else cout<<"\nPulse is within acceptable values";
        }

    }
    }
}


int main()
{
    string input;
    cout << "List of commands: \n"; //to finish
    cout << "exit - exits the program\n";
    cout << "login - logs in an account\n";
    cout << "logout - log out of the active account\n";
    cout << "register - register\n";
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
        else if(input=="addpulse"){
            addPulse();
        }
        else if(input=="addsleep"){
            AddSleep();
        }
        cout << "\n";
        cin >> input;
    }

    return 0;
}

