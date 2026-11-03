#include <vector>
#include "player.cpp"
#include <climits>
#include <chrono>
#include <thread>
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
         cout << "Not enough money!!!" << endl;
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

      cout << "-----Slot Machine Simulator----\n";
      cout << "Match symbols to win big!🎰\n";
      cout << "3 same : 2x | 2 same : 1.5x\n";
      cout << "-----------------------------\n";
      while (1)
      {

         if (getValidBet(p) != 200)
         {
            return;
         }

         cout << "\n-----Spin Detail----------\n";
         cout << "Your Bet : ₹" << bet << endl;
         cout << "--------------------------\n\n";
         cout << "Spinning the reels😀\n\n";

         string s1 = symbols[rand() % symbols.size()];
         string s2 = symbols[rand() % symbols.size()];
         string s3 = symbols[rand() % symbols.size()];

         this_thread::sleep_for(chrono::seconds(2));

         cout << "-----------Slot Machine------------\n";
         cout << "   [ " << s1 << " | " << s2 << " | " << s3 << " ]\n";
         cout << "-----------------------------------\n";

         if (s1 == s2 && s2 == s3)
         {
            cout << "Result : Congratulations you got all same🥳" << endl;
            cout << "Net profit : ₹" << bet << endl;
            p.increaseCurrentMoney(2 * bet);
         }

         else if (s1 == s2 || s2 == s3 || s3 == s1)
         {
            cout << "Result : You got 2 same😀" << endl;
            cout << "Net profit : ₹" << bet * 0.5 << endl;
            p.increaseCurrentMoney(1.5 * bet);
         }
         else
         {
            cout << "Result : You lose!😔" << endl;
            cout << "Net loss : ₹" << bet << " 😨" << endl;
         }

         cout << "-----------------------------------------------------\n";
         cout << "Current balance : ₹" << p.getCurrentMoney() << endl;
         cout << "-----------------------------------------------------\n";
         int choice = 0;
         cout << "Enter 1 to play again (or any other number to exit) : ";
         cin >> choice;

         if (choice != 1)
         {
            break;
         }
      }

      cout << "\n-------------Exit details-------------------\n";
      cout << "Entered with : ₹" << intitalMoney << endl;
      cout << "Exited with  : ₹" << p.getCurrentMoney() << endl;
      double diff = p.getCurrentMoney() - intitalMoney;
      if (diff < 0)
      {
         cout << "Total loss : ₹" << diff << " 😔" << endl;
      }
      else
      {
         cout << "Total profit : ₹" << diff << " 🤑" << endl;
      }
      cout << "--------------------------------------------\n";
      this_thread::sleep_for(chrono::seconds(2));
   }
};

class CoinGame : public Game
{

   vector<vector<int>> arrays = {
       {47, 16, 24, 3, 38, 15, 30, 19, 22},
       {19, 32, 14, 25, 28, 12, 27, 17},
       {14, 30, 6, 25, 10, 35, 18},
       {7, 41, 14, 20, 15, 8, 23},
       {6, 2, 44, 26, 48, 17, 49},
       {12, 18, 8, 50, 10, 20, 13},
       {27, 15, 9, 20, 24, 22, 23, 14},
       {5, 38, 15, 20, 18, 42, 7},
       {15, 1, 12, 1, 1, 13, 32, 13, 22},
       {30, 42, 22, 7, 9, 46},
       {30, 43, 4, 10, 11, 2, 32, 43, 21},
       {44, 39, 30, 7, 28, 33, 12},
       {11, 26, 14, 32, 9, 28, 17, 30, 15},
       {35, 37, 33, 14, 7, 20},
       {22, 18, 42, 9, 31, 44, 50},
       {10, 22, 8, 35, 12, 28, 14},
       {15, 25, 10, 5, 30, 20},
       {31, 28, 27, 24, 43, 22, 33, 25, 35},
       {9, 24, 15, 40, 35, 12, 28, 11},
       {8, 25, 10, 40, 15, 30, 12},
       {23, 2, 8, 25, 38, 32, 26},
       {22, 37, 2, 33, 42, 40, 28, 39, 1},
       {16, 12, 35, 10, 45, 22},
       {18, 47, 42, 6, 32, 29, 25, 19},
       {8, 26, 46, 38, 43, 33},
       {2, 30, 37, 9, 38, 19, 1},
       {39, 41, 18, 17, 14, 48, 31},
       {48, 32, 34, 19, 1, 50}};

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
      cout << " -------Coin Game------\n";
      cout << "Pick coins from either end.🪙\n";
      cout << "Highest total wins.🏆\n";
      cout << "Easy win : 1.5x | Hard win : 2.5x\n";
      cout << "--------------------------\n";
      computer_score = 0;
      player_score = 0;

      if (getValidBet(p) != 200)
      {
         return;
      }

      int mode;
      while (1)
      {
         cout << "Enter mode you want to play : (1) Easy  (2) Hard : ";
         cin >> mode;
         if (mode == 1 || mode == 2)
         {
            break;
         }
         else
         {
            cout << "Enter valid key😡\n";
         }
      }

      vector<int> gameArr = arrays[rand() % arrays.size()];
      int i = 0, j = gameArr.size() - 1;
      bool computer_turn = false;

      vector<vector<int>> dp(gameArr.size(), vector<int>(gameArr.size(), INT_MIN));

      cout << "\n-----Game Detail----------\n";
      string emo = mode == 1 ? "😒" : "💪";
      cout << "Selected Mode : " << (mode == 1 ? "Easy" : "Hard") << emo << endl;
      cout << "Total Coins : " << gameArr.size() << endl;
      cout << "--------------------------\n\n";
      this_thread::sleep_for(chrono::seconds(1));

      cout << "-----------Coin game starts😀------------\n";
      this_thread::sleep_for(chrono::seconds(1));

      while (i <= j)
      {
         cout << "Coins left : [ ";
         for (int start = i; start <= j; start++)
         {
            cout << gameArr[start] << " ";
         }
         cout << "]" << endl;

         if (computer_turn)
         {
            this_thread::sleep_for(chrono::seconds(1));
            int k = computer_move(mode, i, j, gameArr, dp);
            string message = k == i ? "first" : "last";
            int score = k == i ? gameArr[i++] : gameArr[j--];
            computer_score += score;
            cout << "Computer choice : " << message << " element (" << score << ") 🤖" << endl;
         }
         else
         {
            char choice;
            while (1)
            {
               cout << "Choose i for first and j for last : ";
               cin >> choice;

               if (choice == 'i' || choice == 'j')
                  break;
               else
                  cout << "Enter valid option😡" << endl;
            }

            int score = choice == 'i' ? gameArr[i++] : gameArr[j--];
            player_score += score;
            cout << "Your choice : " << (choice == 'i' ? "first" : "last") << " element (" << score << ") " << endl;
         }

         cout << "Scoreboard | Computer score : " << computer_score << " | Your Score : " << player_score << endl;
         cout << "-------------------------------------\n";
         computer_turn = !computer_turn;
      }
      cout << "\n";

      cout << "-------------Final Score-------------------\n";
      cout << "Final Computer Score : " << computer_score << endl;
      cout << "Final Player Score   : " << player_score << endl;

      if (computer_score > player_score)
      {
         cout << "Result : You Lost😔" << endl;
      }
      else if (computer_score == player_score && mode == 2)
      {
         cout << "Result : Draw , You won : ₹" << bet * .5 << " 🤩" << endl;
         p.increaseCurrentMoney(bet * 1.5);
      }
      else if (computer_score == player_score)
      {
         cout << "Result : Draw , You got your money refunded🙂" << endl;
         p.increaseCurrentMoney(bet);
      }
      else
      {
         cout << "Result : You won🥳" << endl;

         double f = mode == 1 ? 1.5 : 2.5;
         p.increaseCurrentMoney(bet * f);
      }
      cout << "--------------------------------------------\n";
      this_thread::sleep_for(chrono::seconds(2));
   }
};

struct stocks
{
   string name;
   double price;
};

class StockPriceSimulator : public Game
{

   vector<stocks> s = {
       {"Reliance", 2850.40},
       {"TCS", 3920.15},
       {"Infosys", 1745.60},
       {"HDFC Bank", 1620.30},
       {"Wipro", 2577.50},
       {"Tata Motors", 985.20},
       {"Zomato", 735.85},
       {"Suzlon", 1755.38},
       {"Tesla", 1422.20},
       {"SpacePro", 3030.56},
   };

   vector<double> delta = {
       -35.55, -55.45, 60.33, 45.44, 80.99, -10.30, 15.44,
       -12.20, 25.75, -48.10, 70.60, -90.35, 15.40, 33.25,
       -65.80, 52.15, -20.90, 45.50, -75.25, 40.10, -8.65,
       58.30, -110.70, 22.45, 85.20, -30.15, 12.80, -58.60,
       66.90, -42.35, 10.10, -18.50, 30.65, -85.40, 50.25};

   int choice;
   int day;
   stocks selectedStock;
   int initialPrice;

public:
   void playGame(Player &p) override
   {
      cout << "----Stock Price Simulator-----\n";
      if (p.getCurrentMoney() < 735.85)
      {
         cout << "You don't have enough money to buy any stock 😔" << endl;
         return;
      }

      cout << "  Choose a stock \n";
      cout << "---------Stocks----------\n";
      for (int i = 0; i < s.size(); ++i)
      {
         cout << i + 1 << ". " << s[i].name
              << " (₹" << s[i].price << ")\n";
      }
      cout << "--------------------------\n";

      while (1)
      {
         cout << "Enter number corresponding to stock : ";
         cin >> choice;

         if (choice <= 0 || choice > 10)
         {
            cout << "Enter valid option😡";
         }
         else if (p.getCurrentMoney() < s[choice - 1].price)
         {
            cout << "You don't have enough money to buy this stock 😔" << endl;
         }
         else
         {
            p.decreaseCurrentMoney(s[choice - 1].price);
            selectedStock = s[choice - 1];
            initialPrice = selectedStock.price;
            cout << "You have successfully purchased the stock🤩" << endl;
            break;
         }
      }

      while (1)
      {
         cout << "Enter your exit day (10-60): ";
         cin >> day;

         if (day < 10 || day > 60)
         {
            cout << "Enter a valid date😡😡😡" << endl;
         }
         else
         {
            break;
         }
      }
      cout << "\n-----Transaction Detail----------\n";
      cout << "Your stock is : " << selectedStock.name << endl;
      cout << "Your stock price is : ₹" << selectedStock.price << endl;
      cout << "Your exit day is : " << day << endl;
      cout << "--------------------------------------\n\n";
      cout << "Stock price simulator starts😀😀😀\n\n";
      this_thread::sleep_for(chrono::seconds(1));
      cout << "-----------Daywise chart------------\n";
      this_thread::sleep_for(chrono::seconds(1));
      for (int d = 0; d < day; d++)
      {
         double priceDelta = delta[rand() % (delta.size())];
         selectedStock.price += priceDelta;
         if (selectedStock.price <= 0)
         {
            cout << "Your stock crashed 📉" << endl;
            cout << "Can't continue know 😞" << endl;
            break;
         }
         string emo = priceDelta > 0 ? "🤑" : "😨";
         cout << "Day : " << d + 1 << "| current price : " << selectedStock.price << "| change : " << priceDelta << emo << endl;
         this_thread::sleep_for(chrono::seconds(1));
      }
      cout << "-------------------------------------\n\n";

      cout << "-------------Exit details-------------------\n";
      cout << "Stock Sold for : ₹" << selectedStock.price << endl;

      if (selectedStock.price > 0)
         p.increaseCurrentMoney(selectedStock.price);

      double diff = selectedStock.price - initialPrice;

      if (diff > 0)
      {
         cout << "Net profit : ₹" << diff << endl;
      }
      else
      {
         cout << "Net loss : ₹" << diff << endl;
      }
      cout << "----------------------------------------\n";
      this_thread::sleep_for(chrono::seconds(2));
   }
};