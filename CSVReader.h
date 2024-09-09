#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>

using namespace std;
class CSVReader{

    public:
        CSVReader();
        // stateless function
        static vector<OrderBookEntry> readCSV(string csvfile);
        static vector<string> tokenise(string csvline, char separator);
        static OrderBookEntry stringsToOBE(string timestamp, string product, OrderBookType OrderBookType, string priceString, string amountString);

    private:
        static OrderBookEntry stringsToOBE(vector<string> tokens);
};