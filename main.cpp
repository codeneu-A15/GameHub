#ifdef _WIN32
#include <windows.h>
#endif
#include "games.cpp"

using namespace std;

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    srand(time(0));

    cout << "-----Welcome to GameHub🙇-----\n\n";
    cout << "Fill your details" << endl;

    Player player;
    double startingMoney = player.getCurrentMoney();

    cout << "------Entry detail--------------\n";
    player.getDetails();
    cout << "---------------------------------\n";

    SlotMachine slot;
    CoinGame coin;
    StockPriceSimulator simul;
    this_thread::sleep_for(chrono::seconds(1));

    while (true)
    {
        cout << "\n-----------GameHub------------\n";
        cout << "Balance : " << player.getCurrentMoney() << "\n";
        cout << "--------------Games----------------\n";
        cout << "1. Slot Machine\n";
        cout << "2. Coin Game\n";
        cout << "3. Stock price simulator\n";
        cout << "4. Check Balance\n";
        cout << "0. Exit\n";
        cout << "------------------------------\n";
        cout << "Enter your choice : ";

        int choice;
        cin >> choice;

        if (choice == 0)
        {
            break;
        }

        if ((choice == 1 || choice == 2) && player.getCurrentMoney() <= 0)
        {
            cout << "\nYou are out of money! You can't play any more games.\n";
            break;
        }

        switch (choice)
        {
        case 1:
            slot.playGame(player);
            break;
        case 2:
            coin.playGame(player);
            break;
        case 3:
            simul.playGame(player);
            break;
        case 4:
            cout << "\nCurrent balance : " << player.getCurrentMoney() << endl;
            this_thread::sleep_for(chrono::seconds(2));
            break;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }
    }

    double diff = player.getCurrentMoney() - startingMoney;
    cout << "\n------------- Summary -------------\n";
    cout << "Started with  : " << startingMoney << endl;
    cout << "Final balance : " << player.getCurrentMoney() << endl;
    if (diff < 0)
        cout << "Total loss  : " << -diff << endl;
    else
        cout << "Total profit  : " << diff << endl;
    cout << "Thanks for playing!\n";

    return 0;
}