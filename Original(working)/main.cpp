#include <iostream>
#include <regex>
#include <map>
#include <bits/stdc++.h>

using namespace std;

string encryptyfunc(int key,string text)
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

bool email_is_valid(string email)
{
    string userEmailRegex = "([_a-z0-9-]+@[a-z0-9-]+.[a-z0-9-]{2,4})";
    return regex_match(email, regex(userEmailRegex));
}

class User
{
    public:
        string email = "";
        string password;
        int age;
        double averageSleep = 0, averagePulse = 0, averageWorkout = 0, averageSteps = 0, averageWater = 0 ;

    private:
        int totalPulse = 0, pulseCounter = 0;
        int totalSleep = 0, sleepCounter = 0;
        int totalWorkout = 0, workoutCounter = 0;
        int totalSteps = 0, stepsCounter = 0;
        int totalWater = 0, waterCounter = 0;
    public:
         double addWater(int water)
        {
          this->totalWater+=water;
          waterCounter++;
          averageWater=totalWater/waterCounter;
          return averageWater;
        }
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
            workoutCounter++;
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
    string email, password, email1;
    int age;
    cout << "Enter email: ";
    cin >> email;
    bool isValid = email_is_valid(email);

    while(!isValid)
    {
        cout << " is invalid email" << endl;
        cout << "Enter email: ";
        cin >> email;
        isValid = email_is_valid(email);
    }
    int encKey = email.size();

    cout << "Enter password: ";
    cin >> password;
    cout << "Enter age: ";
    cin >> age;

    password = Hash(password);

    User user(email, password, age);
    string user_hash = Hash(email + password);

    users[user_hash] = user;

    fstream file;
    file.open("Users/"+user_hash+".txt",ios::out);
    if(!file)
    {
        cout<<"Error in creating file!!!";
    }
    string ageStr = to_string(age);
    ageStr = "age" + ageStr;
    file << encryptyfunc(encKey,ageStr);
    file.close();
    ifstream fileReader;
    fileReader.open("Users/"+user_hash+".txt");
    cout << "You have successfully registered."<<endl;
    cout << "Now you can login or exit"<<endl;
    cout << "List of commands:"<< endl;
    cout << "login - logs into an account,"<<endl;
    cout << "exit - exits the program."<<endl;
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
        cout << "New commands you can use: "<<endl;
        cout << "addsleep - adds sleep,"<<endl;
        cout << "addsteps - adds steps,"<<endl;
        cout << "addpulse - adds pulse,"<<endl;
        cout << "addwater - adds water,"<<endl;
        cout << "addworkout - adds workout."<<endl;
    }
}

void LogOut()
{
    active_user = User();
    logged_in = false;
    cout << "You have successfully logged out."<<endl;
}

void AddWater()
{
  if(active_user.email!="")
  {
    int water;
    double avg_water;
    cout << "How much water you consumed in liters?: ";
    cin >> water;
    avg_water=active_user.addWater(water);
    cout << "Your average consumed water is: " << avg_water << endl;
    if (avg_water >= 2)
    {
      cout << "Your consumed water is enough. \nWell done!" << endl;
    } else
    {
       cout << "Your consumed water isn't enough. \nDrink more water!" << endl;
    }
  }
}
void AddWorkout()
{
  if(active_user.email!="")
  {
    int workout;
    double avg_workout;
    cout << "How many workouts did you do?: ";
    cin >> workout;
    avg_workout=active_user.addWorkout(workout);
    cout << "Your average workouts are: " << avg_workout << endl;
    if(active_user.age < 5)
    {
     if(avg_workout >= 1)
     {
       cout << "Your average amount of workouts is good. \nKeep going!" << endl;
     }
    }
     else if(active_user.age >= 5 || active_user.age <=12 && active_user.age >=60 )
      {
        if(avg_workout >=2)
        {
          cout << "Your average amount of workouts is good. \nKeep going!" << endl;
        } else
        {
        cout << "Your average amount of workouts is bad. \nTry harder!" << endl;
        }
      }
    else if (active_user.age > 12 || active_user.age < 60)
    {
      if(avg_workout >=3)
    {
      cout << "Your average amount of workouts is good. \nKeep going!" << endl;
    } else
    {
      cout << "Your average amount of workouts is bad. \nTry harder!" << endl;
    }
      }
  }
}
void AddSleep()
{
    if(active_user.email!="")
    {
        int sleephours;
        double avg_sleep;
        cout << "How much did you sleep?:"<<endl;
        cin >> sleephours;
        avg_sleep=active_user.addSleep(sleephours);
        cout << "Your average amount of sleep is: " << avg_sleep << endl;

        if (active_user.age < 18) {
        if (avg_sleep >= 8) {
          cout << "Your average amount of sleep is good." << endl;
        } else {
          cout << "Your average amount of sleep is bad.\nSleep more. Feel better!" << endl;
        }
      } else {
        if (avg_sleep >= 7) {
          cout << "Your average amount of sleep is good." << endl;
        } else {
          cout << "Your average amount of sleep is bad.\nSleep more. Feel better!" << endl;
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
            if(averagePulse>130) cout<<"\nPulse is too high. \nBe calmer!";
            else if(averagePulse<80) cout<<"\nPulse is too low. \nBe more active!";
            else cout<<"\nPulse is within acceptable range.";
            break;
        }
    case 3:;
    case 4:
        {
            if(averagePulse>120) cout<<"\nPulse is too high. \nBe calmer!";
            else if(averagePulse<80) cout<<"\nPulse is too low. \nBe more active!";
            else cout<<"\nPulse is within acceptable range.";
            break;
        }
    case 5:;
    case 6:
        {
            if(averagePulse>115) cout<<"\nPulse is too high. \nBe calmer!";
            else if(averagePulse<75) cout<<"\nPulse is too low. \nBe more active!";
            else cout<<"\nPulse is within acceptable range.";
            break;
        }
    case 7:;
    case 8:;
    case 9:
        {
            if(averagePulse>110) cout<<"\nPulse is too high. \nBe calmer!";
            else if(averagePulse<70) cout<<"\nPulse is too low. \nBe more active!";
            else cout<<"\nPulse is within acceptable range.";

            break;
        }
    default :
        {
            if(averagePulse>100) cout<<"\nPulse is too high. \nBe calmer!";
            else if(averagePulse<60) cout<<"\nPulse is too low. \nBe more active!";
            else cout<<"\nPulse is within acceptable range.";
        }

    }
    }
}
void addSteps(){
    if(active_user.email!="")
    {
        int steps;
        double averageSteps=0;
        cout << "How many steps do you get?:\n";
        cin >> steps;
        averageSteps=active_user.addSteps(steps);
        cout << "Your average steps are: " << averageSteps << endl;
        if (active_user.age < 5) {
            if (averageSteps >= 2000) {
              cout << "Your average amount of steps is good. " << endl;
            } else {
              cout << "Your average amount of steps is not enough. Keep walking!" << endl;
            }
        }
        else if (active_user.age >5 && active_user.age <=13) {
            if (averageSteps >= 8000) {
              cout << "Your average amount of steps is good." << endl;
            } else {
              cout << "Your average amount of steps is not enough. Keep walking!" << endl;
            }
       }
       else if (active_user.age >13 && active_user.age <=45) {
            if (averageSteps >= 10000) {
              cout << "Your average amount of steps is good." << endl;
            } else {
              cout << "Your average amount of steps is not enough. Keep walking!" << endl;
            }
       }
       else if (active_user.age >45 && active_user.age <=60) {
            if (averageSteps >= 8000) {
              cout << "Your average amount of steps is good." << endl;
            } else {
              cout << "Your average amount of steps is not enough. Keep walking!" << endl;
            }
       }
       else if (active_user.age >60) {
            if (averageSteps >= 6000) {
              cout << "Your average amount of steps is good." << endl;
            } else {
              cout << "Your average amount of steps is not enough. Keep walking" << endl;
            }
       }
     }
}


int main()
{
    string input;
    cout << "First you have to register or exit." << endl;
    cout << "List of commands:"<< endl;
    cout << "register - register,"<<endl;
    cout << "exit - exits the program."<<endl;
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
         else if(input=="addworkout"){
            AddWorkout();
        }
        else if(input=="addwater"){
            AddWater();
        }
        else if(input=="addsteps"){
            addSteps();
        }
        cout << "\n";
        cin >> input;
    }

    return 0;
}
