#include <iostream>
#include <string>
using namespace std;

class Player
{
    string name;
    double initMoney;
    double currentMoney;

public:

    Player(){

        cout<<"Enter player name : ";
        getline(cin , name);

        cout<<"Enter intial money you want to enter with : ";
        cin>>initMoney;

        currentMoney = initMoney;
    }

    inline double getCurrentMoney(){
        return currentMoney;
    }

    void increaseCurrentMoney(double winAmt){
          currentMoney += winAmt;
    }

    void decreaseCurrentMoney(double betAmt){
          currentMoney -= betAmt;
    }
    
};