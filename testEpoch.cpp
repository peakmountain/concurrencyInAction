#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <chrono>
#include <memory>

using namespace std;

enum class StockStates
{
    PreOpen_Auction,
    Open,
    Intraday_Auction,
    Intraday_Close,
    Closing_Auction,
    Closed
};

enum class EventType
{
    NonEvent = 0,
    Event = 2
};

struct Order
{
    /*
    Order(unsigned int t, string name, StockStates state)
        :timestamp(t), stockName(name), nextState(state)
        {}
        */
    unsigned int timestamp;
    EventType eventType;
    string stockName;
    StockStates nextState;
};

string ConvertToName(const StockStates& state);

class StockEntity
{
public:
    StockEntity(string name, StockStates state = StockStates::Closed)
        :_name(name), _lastState(state)
        {
            intializeStateArray();
            intializeTransition();
        }

    void Update(const Order& order)
    {
        UpdateCurrentState();
        if (NextState(order))
        {
            cout << order.timestamp << "," << static_cast<int>(order.eventType) << "," << order.stockName << "," << ConvertToName(_lastState) << "," << ConvertToName(order.nextState) << "," << "Success" << std::endl;
        }
        else
        {
            cout << order.timestamp << "," << static_cast<int>(order.eventType) << "," << order.stockName << "," << ConvertToName(_lastState) << "," << ConvertToName(_lastState) << "," << "Failure" << std::endl;
        }
    }
private:
    void intializeStateArray()
    {
        auto timestamp0 = ConvertToMilliseconds( 8, 30);
        auto timestamp1 = ConvertToMilliseconds( 9, 30);
        auto timestamp2 = ConvertToMilliseconds(12,  0);
        auto timestamp3 = ConvertToMilliseconds(12, 30);
        auto timestamp4 = ConvertToMilliseconds(13, 30);
        auto timestamp5 = ConvertToMilliseconds(14, 00);
        auto timestamp6 = ConvertToMilliseconds(15, 30);
        auto timestamp7 = ConvertToMilliseconds(16, 00);
        auto timestamp8 = ConvertToMilliseconds(24, 00);

        _stateArray.push_back(timestamp0);
        _stateArray.push_back(timestamp1);
        _stateArray.push_back(timestamp2);
        _stateArray.push_back(timestamp3);
        _stateArray.push_back(timestamp4);
        _stateArray.push_back(timestamp5);
        _stateArray.push_back(timestamp6);
        _stateArray.push_back(timestamp7);
        _stateArray.push_back(timestamp8);
    }

    void intializeTransition()
    {

    }

    unsigned ConvertToMilliseconds(int hour = 0, int min = 0, int sec = 0)
    {
        auto tp = chrono::system_clock::now();

        auto tnow = chrono::system_clock::to_time_t(tp);

        auto date = localtime(&tnow);
        date->tm_hour = hour;
        date->tm_min = min;
        date->tm_sec = sec;

        auto midnight = chrono::system_clock::from_time_t(std::mktime(date));

        auto milliseconds = chrono::duration_cast<chrono::milliseconds>(tp - midnight);

        return milliseconds.count();
    }

    StockStates ConvertIndexToState(int index)
    {
        StockStates state = StockStates::Closed;
        switch (index)
        {
            case 0:
                state = StockStates::Closed;
                break;
            case 1:
                state = StockStates::PreOpen_Auction;
                break;
            case 2:
                state = StockStates::Open;
                break;
            case 3:
                state = StockStates::Intraday_Auction;
                break;
            case 4:
                state = StockStates::Intraday_Close;
                break;
            case 5:
                state = StockStates::Intraday_Auction;
                break;
            case 6:
                state = StockStates::Open;
                break;
            case 7:
                state = StockStates::Closing_Auction;
                break;
            case 8:
            default:
                state = StockStates::Closed;
                break;

        }
        return state;
    }

    // update the _current state to the last valid state.
    // for example, at 8:40, the last valid state is Closed.
    void UpdateCurrentState()
    {
        auto now = ConvertToMilliseconds();

        for (int i = 0; i < _stateArray.size(); i++)
        {
            if (now < _stateArray[i])
            {
                _lastState = ConvertIndexToState((i - 1) % _stateArray.size());
            }
        }
    }

    bool NextState(const Order& order)
    {
        bool result = false;

        StockStates currentState;
        auto now = ConvertToMilliseconds();

        for (int i = 0; i < _stateArray.size(); i++)
        {
            if (now < _stateArray[i])
            {
                currentState = ConvertIndexToState(i);
                if (currentState == order.nextState)
                {
                    result = true;
                    break;
                }
            }
        }
        return result;
    }

    string _name;
    StockStates _lastState;
    vector<int> _stateArray;
};

string ConvertToName(const StockStates& state)
{
    string result = "Closed";

    switch (state)
    {
        case StockStates::PreOpen_Auction:
            result = "PreOpen_Auction";
            break;
        case StockStates::Open:
            result = "Open";
            break;
        case StockStates::Intraday_Auction:
            result = "Intraday_Auction";
            break;
        case StockStates::Closing_Auction:
            result = "Closing_Auction";
            break;
        case StockStates::Closed: // deliberately fall throght.
        default:
            result = "Closed";
            break;
    }
    return result;
}

StockStates ConvertToState(const string& strState)
{
    StockStates result = StockStates::Closed;

    if (strState == "PreOpen_Auction")
    {
        result = StockStates::PreOpen_Auction;
    }
    else if (strState == "Open")
    {
        result = StockStates::Open;
    }
    else if (strState == "Intraday_Auction")
    {
        result = StockStates::Intraday_Auction;
    }
    else if (strState == "Intraday_Close")
    {
        result = StockStates::Intraday_Close;
    }
    else if (strState == "Closing_Auction")
    {
        result = StockStates::Closing_Auction;
    }
    else
    {
        result = StockStates::Closed;
    }
    return result;
}

void GetOrder(const string& line, Order& order)
{
    string inputStr(line);
    auto pos = inputStr.find(",");
    string strTime = inputStr.substr(0, pos);  // string for timestamp.

    inputStr.erase(0, pos+1);
    pos = inputStr.find(",");
    string strType = inputStr.substr(0, pos); // string for eventtype.

    inputStr.erase(0, pos+1);
    pos = inputStr.find(",");
    string strName = inputStr.substr(0, pos); // string for name.

    inputStr.erase(0, pos+1);
    pos = inputStr.find(",");
    string strState = inputStr.substr(0, pos); // string for state.

    order.timestamp = atoi(strTime.c_str());
    order.eventType = (atoi(strType.c_str())) == 2 ? EventType::Event : EventType::NonEvent;
    order.stockName = strName;
    order.nextState = ConvertToState(strState);
}

void ParseOrders(ifstream& filename, vector<Order>& orders)
{
    if (!filename)
    {
        std::cout << "Can't open input file " << endl;
        exit(EXIT_FAILURE);
    }

    for (string line; getline(filename, line);)
    {
        Order order;
        GetOrder(line, order);
        if (order.eventType == EventType::Event)
        {
            orders.push_back(order);
        }
    }
}

int main(int argc, char *argv[]) {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    if (argc != 2)
    {
        cout << "Command format: ./command filename.txt" << endl;
        return 1;
    }

    ifstream filename(argv[1]);

    vector<Order> orders;

    // Parse the input file, and convert it to a list of orders.
    ParseOrders(filename, orders);

    /* debug purpose
    for (auto item : orders)
    {
        std::cout << "order :" << item.timestamp <<", " << static_cast<int>(item.eventType) << ", " << item.stockName << ", " << static_cast<int>(item.nextState) << std::endl;
    }
    */

    map<string, unique_ptr<StockEntity>> stocks;
    for (auto item : orders)
    {
        auto instance = stocks.find(item.stockName);

        // check whether the stock all exist in the list, if not insert it.
        if (instance == stocks.end())
        {
            //StockEntity stock(item.stockName);
            stocks.emplace(item.stockName, make_unique<StockEntity>(item.stockName));
        }

        stocks[item.stockName]->Update(item);
    }

    return 0;
}
