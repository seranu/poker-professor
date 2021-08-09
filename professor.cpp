#include "dealer.hpp"
#include "equity_calculator.hpp"
#include <iostream>

using namespace professor;
using namespace std;

void do_single_hand_play()
{
    std::vector<Player> players;
    players.emplace_back("Serban");
    players.emplace_back("Tibi");
    Dealer d(players);
    d.doOneRound();
}

void do_equity_calculator()
{
    cout << "Enter hero cards:";
    std::string heroStr, villanStr, runsStr;
    std::getline(cin, heroStr);
    cout << "Enter villan cards:";
    std::getline(cin, villanStr);
    cout << "Enter number of runs:";
    std::getline(cin, runsStr);
    EquityCalculator calculator;
    auto result = calculator.calculateEquity(*Cards::fromString(heroStr), *Cards::fromString(villanStr), std::stoi(runsStr));
    cout << "Results: hereo: " << result.heroEquity << " villan: " << result.villainEquity << " draw: " << result.draw << "\n";
}

int main(int argc, char* argv[])
{


    const int kExit = 3, kContinue = 1;
    int option = kContinue;
    do
    {
        cout << "Welcome to poker professor. Chose mode:\n";
        cout << "1. Single hand play(two players)\n";
        cout << "2. Equity calculator(two players)\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        std::string choice;
        std::getline(cin, choice);
        if(choice == "1") {
            do_single_hand_play();
        } else if (choice == "2") {
            do_equity_calculator();
        } else if (choice == "3") {
            option = kExit;
        }
    } while (option != kExit);
    
    return 0;
}