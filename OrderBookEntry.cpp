#include "OrderBookEntry.h"
#include <string>
using namespace std;
OrderBookEntry::OrderBookEntry(string _timestamp,
                               string _product,
                               OrderBookType _orderType,
                               double _price,
                               double _amount,
                               string _username) : timestamp{_timestamp},
                                                 product{_product},
                                                 orderType{_orderType},
                                                 price{_price},
                                                 amount{_amount},
                                                 username{_username} {};

OrderBookType OrderBookEntry::stringToOrderBookType(string s){
    if(s=="ask")
        return OrderBookType::ask;
    if(s=="bid")
        return OrderBookType::bid;

    return OrderBookType::unknown;
}

bool OrderBookEntry::compareByTimeStamp(OrderBookEntry &obe1, OrderBookEntry &obe2){
    
    return obe1.timestamp < obe2.timestamp;
}

bool OrderBookEntry::compareByPriceAsc(OrderBookEntry &obe1, OrderBookEntry &obe2){

    return obe1.price > obe2.price;
}

bool OrderBookEntry::compareByPriceDesc(OrderBookEntry &obe1, OrderBookEntry &obe2){

    return obe1.price > obe2.price;
}