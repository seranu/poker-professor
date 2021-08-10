#include "dealer.hpp"
#include "equity_calculator.hpp"
#include "hand_value.hpp"
#include "log.hpp"
#include "card.hpp"
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

void do_equity()
{
    EquityCalculator calculator;
    auto result = calculator.calculateEquity(*Cards::fromString("Ah Ac"), *Cards::fromString("Kd Ks"), 1000000);
    cout << "Results: hereo: " << result.heroEquity << " villan: " << result.villainEquity << " draw: " << result.draw << "\n";
}

std::vector<Card> allCards()
{
    const auto &allSuits = getAllSuits();
    const auto &allRanks = getAllCardRanks();
    decltype(allCards()) result;
    for(auto &suit: allSuits) {
        for(auto &rank: allRanks) {
            result.emplace_back(rank, suit);
        }
    }
    return result;
}
void benchmark_evaluator()
{
    auto cards = allCards();

    SCOPE_TIMER("Benchmark evaluator");
    int i = 0;
    while(i < 6000000) {
        for(int a = 0; a < 48; a++) {
          for(int b = a + 1; b < 49; b++) {
            for(int c = b + 1; c < 50; c++) {
              for(int d = c + 1; d < 51; d++) {
                for(int e = d + 1; e < 52; e++) {
                    HandValue::evaluateHand(Cards( cards[a].internalRepresentation()
                                    | cards[b].internalRepresentation()
                                    | cards[c].internalRepresentation()
                                    | cards[d].internalRepresentation()
                                    | cards[e].internalRepresentation()));
                  i++;
                  if (i == 6000000) {
                    return;
                  }
                }
              }
            }
          }
        }
    }
}

int main(int argc, char* argv[])
{

    do_equity();
    // benchmark_evaluator();
/*
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
*/    
    return 0;
}
