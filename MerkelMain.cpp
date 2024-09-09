
#include "MerkelMain.h"
#include "CSVReader.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits>
using namespace std;

void MerkelMain::init(){
   // loadOrderBook();
    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);

    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

/*void MerkelMain::loadOrderBook(){
    orders=CSVReader::readCSV("ExchangeData.csv");
}*/

void MerkelMain::printMenu()
{
    cout << endl;
    cout << "========================" << endl;
    cout << "========================" << endl;
    // Printing out menu options
    cout << "1: Print help" << endl;
    cout << "2: Print Exchange Stats" << endl;
    cout << "3: Place an Ask" << endl;
    cout << "4: Place a Bid" << endl;
    cout << "5: Print wallet" << endl;
    cout << "6: Continue" << endl;
    cout << "========================" << endl;
    cout << "Current time is: " << currentTime << endl;
}

int MerkelMain::getUserOption()
{
    int userOption = 0;
    string line;
    cout << endl;
    cout << "Type a number from 1-6" << endl;
    getline(cin, line);

    try{
        userOption = stoi(line);
    }catch(const exception& e){
        //
    }
    
    cout << endl;
    return userOption;
}

void MerkelMain::printHelp()
{
    cout << "Help - your aim is to make money." << endl;
    cout << "Analyse the market and make bids" << endl;
    cout << "and offers. " << endl;
}

void MerkelMain::printMarketStats()
{
    for(string const p : orderBook.getKnownProducts()){
        cout << "Product: " << p << endl;
        vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        cout << "Number of Asks = " << entries.size() << endl;
        cout << "Max Ask Price: " << OrderBook::getHighPrice(entries) << endl;
        cout << "Min Ask Price: " << OrderBook::getLowPrice(entries) << endl;
        /*vector<OrderBookEntry> askEntries = orderBook.getOrders(OrderBookType::ask, p, currentTime);
        //vector<OrderBookEntry> bidEntries = orderBook.getOrders(OrderBookType::bid, p, currentTime);
        double minAsk = OrderBook::getLowPrice(askEntries);
        double maxBid = OrderBook::getHighPrice(bidEntries);
        cout << "Spread = " << (minAsk - maxBid) << endl;*/
    }
    cout << endl;
    // cout << "CSVReader::readCSV read " << orders.size() << " entries" << endl;
    // cout << endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // for(OrderBookEntry& obe :orders){
    //     if(obe.orderType == OrderBookType::bid) ++bids;
    //     if (obe.orderType == OrderBookType::ask)++asks;
    // }

    // cout << "Orderbook asks: " << asks << ", Orderbook bids : " << bids << endl;
}

void MerkelMain::enterAsk()
{
    cout << "Place an Ask - enter the product, price, amount eg. BTC/USD,5000,2" << endl;
    string input;
    // clear input stream buffer
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, input);

    vector<string> tokens = CSVReader::tokenise(input, ',');
    if(tokens.size() != 3){
        cout << " MerkelMain::enterAsk() Bad Input! " << input << endl;
    }
    else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(currentTime, tokens[0], OrderBookType::ask, tokens[1], tokens[2]);

            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {

                cout << "Wallet has sufficient funds " << endl;
                orderBook.insertOrder(obe);
            }

            else{

                cout << "Wallet has insufficient funds. " << endl;
            }
        }
        catch (const exception &e)
        {
            cout << "MerkelMain::enterAsk(). Object could not be created from Bad Input!" << endl;
        }
    }

    cout<< "You typed: " << input << endl;
    cout << endl;
}

void MerkelMain::enterBid()
{
    cout << "Place a Bid. What is the quantity you want to Buy and at what price" << endl;
    string input;
    getline(cin, input);
    vector<string> tokens = CSVReader::tokenise(input, ',');
    if(tokens.size() != 3){
        cout << "MerkelMain::enterBid()- Bad Input! " << input << endl;
    }
    else{
        try{
            OrderBookEntry obe = CSVReader::stringsToOBE(currentTime, tokens[0], OrderBookType::bid, tokens[1], tokens[2]);

            obe.username = "simuser";
            if(wallet.canFulfillOrder(obe)){
                cout << "Wallet has sufficient funds " << endl;
                orderBook.insertOrder(obe);
            }
            else{
                cout << "Wallet has sufficient funds " << endl;
            }
            
        }catch(const exception& e){
            cout << "MerkelMain::enterBid(). Object could not be created from Bad Input" << endl ;
        }
    }
    cout << endl;
}

void MerkelMain::printWallet()
{
    cout << "This is what you have in your wallet" << endl;
    cout << wallet.toString() << endl;
    cout << endl;
}

void MerkelMain::gotoNextTimeframe()
{
    cout << "Going to next frame" << endl;

    for(string& p : orderBook.getKnownProducts()){
        cout << "matching " << p << endl;
        vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        cout << "Sales: " << sales.size() << endl;
        
        for(OrderBookEntry &sale : sales){
            cout << "Sale price: " << sale.price << " amount: " << sale.amount << endl;
            if(sale.username ==  "simuser"){
                //update wallet
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
    cout << endl;
}

void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0)
    {
        cout << "Invalid input. Try again" << endl;
        cout << endl;
    }

    if (userOption == 1)
    {
        printHelp();
    }

    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeframe();
    }
    
}
