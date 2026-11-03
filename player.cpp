#include <iostream>
#include <string>
using namespace std;

class Player
{
    string name;
    double initMoney;
    double currentMoney;

public:
    Player()
    {
        cout << "Enter your name : ";
        getline(cin, name);

        while (true)
        {
            cout << "Enter initial money you want to start with : ";
            if (cin >> initMoney && initMoney > 0)
            {
                cout << "Accepted" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid input" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        currentMoney = initMoney;
    }

    inline double getCurrentMoney()
    {
        return currentMoney;
    }

    void increaseCurrentMoney(double winAmt)
    {
        currentMoney += winAmt;
    }

    void decreaseCurrentMoney(double betAmt)
    {
        currentMoney -= betAmt;
    }

    void getDetails()
    {
        cout << "Name : " << name << endl;
        cout << "Wallet : ₹" << currentMoney << endl;
    }
};