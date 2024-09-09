#include "Wallet.h"

using namespace std;

Wallet::Wallet()
{
}

void Wallet::insertCurrency(string type, double amount){

    double balance;
    if(amount<0)
        throw exception{};

    if (currencies.count(type) == 0)
        balance = 0;
    else
        balance = currencies[type];

    balance += amount;

    currencies[type] = balance;
}

bool Wallet::removeCurrency(string type, double amount){
    if(amount < 0)
        return false;
    
    if(currencies.count(type) == 0)
        return false;
    
    else{
        if (containsCurrency(type, amount)){
            currencies[type] -=amount;
            return true;
        }
        else
            return false;
    }
}

bool Wallet::containsCurrency(string type, double amount){

    if (currencies.count(type) == 0) 
        return false;
        
    else
        return currencies[type] >= amount;
}

string Wallet::toString(){

    string s;
    for(pair<string, double> pair : currencies){
        string currency = pair.first;
        double amount = pair.second;
        s +=  currency + " amount : " + to_string(amount) + "\n";
    }

    return s;
}

bool Wallet::canFulfillOrder(const OrderBookEntry& order){

    vector<string> curr_pair = CSVReader::tokenise(order.product, '/');
    double amount;
    string currency;
    //ask
    if (order.orderType == OrderBookType::ask)
    {
        amount = order.amount;
        currency = curr_pair[0];
        cout << "Wallet::canFulfillOrder " << currency << " : " << amount << endl;
        return containsCurrency(currency, amount);
    }

    if(order.orderType == OrderBookType::bid){
        amount = order.amount * order.price;
        currency = curr_pair[1];
        cout << "Wallet::canFulfillOrder " << currency << " : " << amount << endl;
        return containsCurrency(currency, amount );
    }

    return false;
}

void Wallet::processSale(OrderBookEntry & sale){

    vector<string> curr_pair = CSVReader::tokenise(sale.product, '/');
    
    double outgoingAmount;
    double incomingAmount;
    string outgoingCurrency;
    string incomingCurrency;
    //ask
    if (sale.orderType == OrderBookType::asksale)
    {
        outgoingAmount = sale.amount;
        outgoingCurrency = curr_pair[0];
        incomingAmount = sale.amount * sale.price;
        incomingCurrency = curr_pair[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }

    if (sale.orderType == OrderBookType::bidsale)
    {
        incomingAmount = sale.amount;
        incomingCurrency = curr_pair[0];
        outgoingAmount = sale.amount * sale.price;
        outgoingCurrency = curr_pair[1];

        currencies[incomingCurrency] += incomingAmount;
        currencies[outgoingCurrency] -= outgoingAmount;
    }
}