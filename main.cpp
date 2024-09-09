#include <iostream>
#include <map>
#include <vector>
#include "MerkelMain.h"
#include "CSVReader.h"
#include "Wallet.h"

using namespace std;

//float average(float x, float y);

int main(){
    MerkelMain app{};
    app.init();

   /* Wallet wallet;
    wallet.insertCurrency("BTC", 5);
    wallet.insertCurrency("USDT", 10000);
    cout << wallet.toString() << endl;
    wallet.removeCurrency("USDT", 1000);
    cout << wallet.toString() << endl;*/

    //CSVReader::readCSV("ExchangeData.csv");

    return 0;
}