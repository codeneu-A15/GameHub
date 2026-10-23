#include <iostream>
#include <vector>
#include "player.cpp"
#include <string>
#include <ctime>
using namespace std;

class Game
{
protected:
   string gameName;
   double bet;

public:
   virtual void playGame(Player &p) = 0;

   int getValidBet(Player &p)
   {
      try
      {
         cout << "Enter your bet : ";
         cin >> bet;

         if (bet > p.getCurrentMoney())
         {
            throw 400;
         }
      }
      catch (int x)
      {
         cout << "Not enough money!!!";
         return 400;
      }

      return 200;
   }
};

class SlotMachine : public Game
{
   vector<string> symbols = {"💀", "🍒", "💰", "👑", "🔔"};

public:
   void playGame(Player &p) override
   {
       
      double intitalMoney = p.getCurrentMoney();

      while (1)
      {

         if (getValidBet(p) != 200)
         {
            return;
         }

         srand(time(0));

         string s1 = symbols[rand() % 5];
         string s2 = symbols[rand() % 5];
         string s3 = symbols[rand() % 5];

         cout << "\n   [ " << s1 << " | " << s2 << " | " << s3 << " ]\n";

         if (s1 == s2 && s2 == s3)
         {
            cout << "Congratulations you won!!!" << endl;
            p.increaseCurrentMoney(2 * bet);
            return;
         }

         if (s1 == s2 || s2 == s3 || s3 == s1)
         {
            cout << "You got 2 same." << endl;
            p.increaseCurrentMoney(1.5 * bet);
            return;
         }

         cout << "You lose!" << endl;

         cout << "Current balance : "<<p.getCurrentMoney();

         int choice = 0;
         cout << "Enter 1 to play again : ";
         cin>>choice;
         if(choice != 0){
            cout<<"Entered with : " <<intitalMoney;
            double diff = p.getCurrentMoney() - intitalMoney;
            if(diff < 0)  {
               cout<<"Total loss : "<<diff<<endl;
            }else {
               cout<<"Total won : "<<diff<<endl;
            }
            return;
         }
      }
   }
};