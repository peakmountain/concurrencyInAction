#pragma once
#include <mutex>
#include <iostream>

class Table
{
    public:
        Table(int id) : _id(id)
        {}
        std::mutex m;
        int GetId() {return _id;}
    private:
        int _id;

        friend std::ostream &operator<< (std::ostream &os, const Table& item)
        {
            os << "Table-" << item._id;
            return os;
        }
};
