#include <iostream>
#include <map>
using namespace std;

class User
{
    public:
        string email;
        string password;
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

string Hash(string str)
{
   hash<string> hasher;
   const auto output = hasher(str);

   return to_string(output);
}

void Register()
{
    string email, password;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    password = Hash(password);

    User user(email, password);
    string user_hash = Hash(email + password);

    users[user_hash] = user;
    cout << users[user_hash].email << endl << users[user_hash].password << endl;
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
        cout << active_user.email << endl;
    }

}

int main()
{
    Register();
    LogIn();

    return 0;
}
