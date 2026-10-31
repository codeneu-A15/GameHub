#include <iostream>
#include <vector>
#include "player.cpp"
#include <string>
#include <ctime>
#include <climits>
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

class CoinGame : public Game
{

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

   int computer_score;
   int player_score;

   int optimalMoveCalc(int l, int r, vector<int> &gameArr, vector<vector<int>> &dp)
   {
      if (l > r)
      {
         return 0;
      }

      if (dp[l][r] != INT_MIN)
      {
         return dp[l][r];
      }

      int x = gameArr[l] - optimalMoveCalc(l + 1, r, gameArr, dp);
      int y = gameArr[r] - optimalMoveCalc(l, r - 1, gameArr, dp);

      return dp[l][r] = max(x, y);
   }

   int computer_move(int mode, int l, int r, vector<int> &gameArr, vector<vector<int>> &dp)
   {
      if (mode == 1)
      {
         return gameArr[l] >= gameArr[r] ? l : r;
      }

      int pickLeft = gameArr[l] - optimalMoveCalc(l + 1, r, gameArr, dp);
      int pickRight = gameArr[r] - optimalMoveCalc(l, r - 1, gameArr, dp);

      return pickLeft >= pickRight ? l : r;
   }

public:
   void playGame(Player &p)
   {
      computer_score = 0;
      player_score = 0;

      if (getValidBet(p) != 200)
      {
         return;
      }

      int mode;
      while (1)
      {
         cout << "Enter mode you want to play : (1) Easy  (2) Hard \n";
         cin >> mode;
         if (mode == 1 || mode == 2)
         {
            break;
         }
         else
         {
            cout << "Enter valid key !!\n";
         }
      }

      vector<int> gameArr = arrays[rand() % arrays.size()];
      int i = 0, j = gameArr.size() - 1;
      bool computer_turn = false;

      vector<vector<int>> dp(gameArr.size(), vector<int>(gameArr.size(), INT_MIN));

      while (i <= j)
      {
         for (int start = i; start <= j; start++)
         {
            cout << gameArr[start] << " ";
         }
         cout << endl;
         if (computer_turn)
         {

            int k = computer_move(mode, i, j, gameArr, dp);
            string message = k == i ? "first" : "last";
            cout << "Computer choice : " << message<<" element"<< endl;
            int score = k == i ? gameArr[i++] : gameArr[j--];
            computer_score += score;
         }
         else
         {
            char choice;
            while (1)
            {
               cout << "Choose  i for first and j for last" << endl;
               cin >> choice;

               if (choice == 'i' || choice == 'j')
                  break;
               else
                  cout << "Enter valid option" << endl;
            }

            int score = choice == 'i' ? gameArr[i++] : gameArr[j--];
            player_score += score;
         }

         cout << "Computer score : " << computer_score << endl;
         cout << "Your Score : " << player_score<<endl;
         computer_turn = !computer_turn;
      }

      if (computer_score > player_score)
      {
         cout << "You Lost😔😔😔" << endl;
      }
      else if (computer_score == player_score)
      {
         cout << "Draw" << endl;
         p.increaseCurrentMoney(bet);
      }
      else
      {
         cout << "You won🥳🥳🥳" << endl;

         int f = mode == 1 ? 2 : 4;
         p.increaseCurrentMoney(bet * f);
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
   }
};
