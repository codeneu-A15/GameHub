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

         p.decreaseCurrentMoney(bet);
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

         cout << "Current balance : " << p.getCurrentMoney();

         int choice = 0;
         cout << "Enter 1 to play again : ";
         cin >> choice;
         if (choice != 0)
         {
            cout << "Entered with : " << intitalMoney;
            double diff = p.getCurrentMoney() - intitalMoney;
            if (diff < 0)
            {
               cout << "Total loss : " << diff << endl;
            }
            else
            {
               cout << "Total won : " << diff << endl;
            }
            return;
         }
      }
   }
};



struct stocks
{
   string name;
   double price;
};

class TradingSimul : public Game
{

   vector<stocks> s = {
       {"Tesla", 1422.20},
       {"Wipro", 2577.50},
       {"Suzlon", 1755.38},
       {"SpacePro", 3030.56},
   };

   vector<double> delta = {-35.55, -55.45, 60.33, 45.44, 80.99, -100.30, 115.44};

public:
   void playGame()
   {
      cout << "=== **TradingSilmul** ===\n\n";
      cout << "Choose a stock: \n";
      for (int i = 0; i < s.size(); ++i)
      {
         cout << i + 1 << ". " << s[i].name
              << " (₹" << s[i].price << ")\n";
      }

      int opt = 0;
      cin >> opt;
   }
};





class sumMax : public Game{


   vector<vector<int>> arrays = {

       {15, 25, 10, 5, 30, 20},

       {8, 25, 10, 40, 15, 30, 12},

       {10, 22, 8, 35, 12, 28, 14},

       {14, 30, 6, 25, 10, 35, 18},

       {12, 18, 8, 50, 10, 20, 13},

       {9, 24, 15, 40, 35, 12, 28, 11},

       {16, 12, 35, 10, 45, 22},

       {11, 26, 14, 32, 9, 28, 17, 30, 15},

       {5, 38, 15, 20, 18, 42, 7},

       {19, 32, 14, 25, 28, 12, 27, 17}};

   int computer_move(){

   }
 
   public:

      void playGame(Player &p){
          
         if(getValidBet(p) != 200){
            return;
         }

          int mode;
         while(1){
            cout<<"Enter mode you want to play : (1) Easy  (2) Hard \n";
            cin>>mode;
            if(mode ==1 || mode == 2){
                break;
            }
            else{
               cout<<"Enter valid key !!\n";
            }
         }

         while(1){
              srand(time(0));

              vector<int> gameArr= arrays[rand()%arrays.size()];
              int i = 0 , j = gameArr.size()-1;
          
              while(i <= j){
                  
              }
              
         }


      }

};