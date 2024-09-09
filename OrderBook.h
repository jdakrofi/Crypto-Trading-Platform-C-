/*
* The OrderBook class presents a high level interface on all the orders in the order book data set, 
* This includes query functions to find out which products are in the data set, and to retrieve a subset of the orders using filters.
* Stores order book entries. Acts as a database.
*/
#pragma once
#include "CSVReader.h"
#include <string>
#include <vector>


using namespace std;
class OrderBook
{
    public:
    /** Constructor, reading a csv data file*/
    OrderBook(string filename);
    /** Return vector of all known products in the dataset*/
    vector<string> getKnownProducts();
    /** return vector of Orders according to the sent filters*/
    vector<OrderBookEntry> getOrders(OrderBookType type,
                                     string product,
                                     string timestamp);

    void insertOrder(OrderBookEntry &order);
    /** returns the earliest time in the order book*/
    string getEarliestTime();
    /** returns the next time after the sent time in the order book
     * if there is no next_timestamp, the program wraps around
    */
    string getNextTime(string timestamp);

    vector<OrderBookEntry> matchAsksToBids(string product, string timestamp);

    // static because we are passing it a fixed set of orders
    static double getHighPrice(vector<OrderBookEntry>& orders);
    static double getLowPrice(vector<OrderBookEntry>& orders);
    

private:
    vector<OrderBookEntry> orders;
};