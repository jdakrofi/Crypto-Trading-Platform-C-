#pragma once
#include <iostream>
#include <string>
#include <map>
#include "OrderBookEntry.h"
#include "CSVReader.h"
using namespace std;


class Wallet
{

    public:
        Wallet();
        /** insert currency into the wallet */
        void insertCurrency(string type, double amount);

        /** remove currency from the wallet */
        bool removeCurrency(string type, double amount);

        /** checks if the wallet contains a certain amount of currency */
        bool containsCurrency(string type, double amount);

        /** checks if the wallet can cope with this ask or bid. */
        bool canFulfillOrder(const OrderBookEntry& order);

        /** update the contents of the wallet
         * assumes the order was made by the owner of the wallet.
        */
        void processSale(OrderBookEntry &sale);

        /** generates a string representation of the wallet */
        string toString();

    private:
        map<string, double> currencies;
};