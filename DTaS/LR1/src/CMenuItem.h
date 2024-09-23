#ifndef MYMENU_CPP_CMENUITEM_H
#define MYMENU_CPP_CMENUITEM_H
#include <string>
#include <functional>

using Func = std::function<int()>;

class CMenuItem
{
public:
    CMenuItem(std::string, Func);
    Func m_func{};
    std::string m_item_name{};
    std::string getName();
    void print();
    int run();
};

#endif // MYMENU_CPP_CMENUITEM_H