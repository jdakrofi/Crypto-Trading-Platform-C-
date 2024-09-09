#include "OrderBook.h"
#include <map>
#include <algorithm>
using namespace std;

/** Constructor, reading a csv data file*/
OrderBook::OrderBook(string filename){
    
    orders = CSVReader::readCSV(filename);
}
/** Return vector of all known products in the dataset*/
vector<string> OrderBook::getKnownProducts(){
    vector<string> products;

    map<string, bool> prodMap;
    for(OrderBookEntry& obe : orders){
        prodMap[obe.product] = true;
    }

    for(auto const& prod : prodMap){
        products.push_back(prod.first);
    }

    return products;
}
/** return vector of Orders according to the sent filters*/
vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,string product,string timestamp){
    vector<OrderBookEntry> orders_sub;

    for (OrderBookEntry obe : orders){

        if(obe.orderType == type && obe.product == product && obe.timestamp == timestamp){
            orders_sub.push_back(obe);

        }
    }

    return orders_sub;
}

double OrderBook::getHighPrice(vector<OrderBookEntry>& orders){

    double max = orders[0].price;
    for (OrderBookEntry& obe : orders){
        if(obe.price > max)
            max = obe.price;
    }

    return max;
}

double OrderBook::getLowPrice(vector<OrderBookEntry>& orders) {
    double low = orders[0].price;
    for (OrderBookEntry& obe : orders){
        if(obe.price < low)
            low = obe.price;
    }

    return low;
}

string OrderBook::getEarliestTime(){

    return orders[0].timestamp; 
}

string OrderBook::getNextTime(string timestamp){
    
    string next_timestamp = "";
    for(OrderBookEntry& obe : orders){
        if(obe.timestamp > timestamp){
            next_timestamp = obe.timestamp;
            break;
        }
    }

    if (next_timestamp == ""){
        next_timestamp = orders[0].timestamp;
    }

    return next_timestamp;
}

void OrderBook::insertOrder(OrderBookEntry&order){
    orders.push_back(order);
    sort(orders.begin(), orders.end(),  OrderBookEntry::compareByTimeStamp);
}

vector<OrderBookEntry> OrderBook::matchAsksToBids(string product, string timestamp){
    vector<OrderBookEntry> asks = getOrders(OrderBookType::ask, product, timestamp);
    vector<OrderBookEntry> bids = getOrders(OrderBookType::bid, product, timestamp);
    vector<OrderBookEntry> sales;
    /*for (OrderBookEntry &obe : orders)
    {
        if(obe.timestamp == timestamp && obe.product == product){
            if(obe.orderType==OrderBookType::ask)
                asks.push_back(obe);
            if (obe.orderType == OrderBookType::bid)
                asks.push_back(obe);
        }
    }*/

    sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);

    //double sale_amount;
    for (OrderBookEntry &ask : asks)
    {
        for(OrderBookEntry &bid : bids){

            if (bid.price >= ask.price){

                OrderBookType type;
                string username;
                if (bid.username == "simuser"){
                    username = "simuser";
                    type = OrderBookType::bidsale;
                }

                if (ask.username == "simuser"){
                    username = "simuser";
                    type = OrderBookType::asksale;
                }

                if(bid.amount==ask.amount){
                    sales.push_back(OrderBookEntry{timestamp, product, type, ask.price, ask.amount, username});
                    bid.amount = 0;
                    break;
                }

                if (bid.amount > ask.amount)
                {
                    sales.push_back(OrderBookEntry{timestamp, product, type, ask.price, ask.amount, username});
                    bid.amount = bid.amount - ask.amount;
                    //ask.amount = 0;
                    break;
                }

                if (bid.amount < ask.amount && bid.amount >0)
                {
                    sales.push_back(OrderBookEntry{timestamp, product, type, ask.price, bid.amount, username});
                    ask.amount = ask.amount - bid.amount;
                    bid.amount = 0;
                    continue;
                }
            }
        }
    }

    return sales;
}