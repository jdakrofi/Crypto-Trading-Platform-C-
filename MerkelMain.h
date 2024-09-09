/*
* The MerkelMain class represents the application itself, and it deals with user input and menu printing.
* MerkelMain: process orders/instructions
*/
#pragma once
#include "Wallet.h"
#include "OrderBookEntry.h"
#include <vector>
#include <map>
#include "OrderBook.h"

using namespace std;
class MerkelMain
{
public:
    MerkelMain() = default;
    /** Call this to start the sim*/
    void init();

private:
    //void loadOrderBook();
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);

    string currentTime;

    //OrderBook orderBook{"TestData.csv"};
    
    OrderBook orderBook{"ExchangeData.csv"};
    //vector<OrderBookEntry> orders;
    Wallet wallet;
};