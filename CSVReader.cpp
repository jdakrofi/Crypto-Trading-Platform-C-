#include "CSVReader.h"
#include <iostream>
#include <fstream>

using namespace std;
CSVReader::CSVReader()
{
}

vector<OrderBookEntry> CSVReader::readCSV(string csvFilename){
    vector<OrderBookEntry> entries;
    ifstream csvFile{csvFilename};
    string line;
    char separator = ',';
    vector<string> tokens;

    if(csvFile.is_open()){
        while (getline(csvFile, line))
        {
            try{
                tokens = tokenise(line, separator);
                OrderBookEntry obe = stringsToOBE(tokens);
                entries.push_back(obe);
            }catch(const exception& e){
                cout << "CSVReader::readCSV bad data" << endl;
            }
            
        }
        cout << "CSVReader::readCSV read " << entries.size() << " entries" << endl;
        csvFile.close();
    }

    return entries;
}

vector<string> CSVReader::tokenise(string csvline, char separator){
    vector<string> tokens;
    signed int start, end;
    string token;
    start = csvline.find_first_not_of(separator, 0);
    do{
        end = csvline.find_first_of(separator, start);
        if(start==csvline.length() || start==end)
            break;
        
        if(end>=0)
            token = csvline.substr(start, end - start);
        else
        {
            token = csvline.substr(start, csvline.length() - start);
        }

        tokens.push_back(token);
        start = end + 1;

    } while (end != string::npos);
    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(vector<string> tokens){
    //Bad line. Not useful data
    double price, amount;
    if (tokens.size() != 5)
    {
        cout << "Bad line" << endl;
        throw exception{};
    }

    try
    {
        price = stod(tokens[3]);
        amount = stod(tokens[4]);
       // cout << price << " : " << amount << endl;
    }
    catch (const exception &e)
    {
        // cout << "CSVReader::stringsToOBE(vector<string> tokens) Bad float!"" << tokens[3] << endl;
        // cout << "CSVReader::stringsToOBE(vector<string> tokens) Bad float!" << tokens[4] << endl;
        throw;
    }

    OrderBookEntry obe{tokens[0], tokens[1], OrderBookEntry::stringToOrderBookType(tokens[2]), price, amount};
    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(string timestamp, string product, OrderBookType OrderBookType, string priceString, string amountString){

    double price, amount;
    try
    {
        price = stod(priceString);
        amount = stod(amountString);
        // cout << price << " : " << amount << endl;
    }
    catch (const exception &e)
    {
        cout << " CSVReader::stringsToOBE(t, p, o, p, a) Bad float!" << priceString << endl;
        cout << " CSVReader::stringsToOBE(t, p, o, p, a) Bad float!" << amountString << endl;
        throw;
    }

    OrderBookEntry obe{timestamp, product, OrderBookType, price, amount};
    return obe;
}