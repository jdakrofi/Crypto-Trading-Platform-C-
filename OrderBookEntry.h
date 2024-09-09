/*
* The OrderBookEntry represents a row in the order book data set (i.e. a single order in the order book). It can be a bid or an ask order.
* Class is used to create an object for each entry of the order book
*/

#pragma once
#include <string>
using namespace std;
enum class OrderBookType
{
    bid,
    ask,
    asksale,
    bidsale,
    unknown
};

class OrderBookEntry
{
public:
    OrderBookEntry(string _timestamp,
                   string _product,
                   OrderBookType _orderType,
                   double _price,
                   double _amount,
                   string _username = "dataset");
    
    static OrderBookType stringToOrderBookType(string s);
    static bool compareByTimeStamp(OrderBookEntry &obe1, OrderBookEntry &obe2);
    static bool compareByPriceAsc(OrderBookEntry &obe1, OrderBookEntry &obe2);
    static bool compareByPriceDesc(OrderBookEntry &obe1, OrderBookEntry &obe2);


    string timestamp;
    string product;
    OrderBookType orderType;
    double price;
    double amount;
    string username;
};