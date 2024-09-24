#ifndef MYMENU_CPP_CMENUITEM_H
#define MYMENU_CPP_CMENUITEM_H
#include <string>

namespace ExpressionTree
{
    class CMenuItem
    {
    public:
        typedef int(*Func)();
        CMenuItem(std::string, Func);
        Func m_func{};
        std::string m_item_name{};
        std::string getName();
        void print();
        int run();
    };
}

#endif //MYMENU_CPP_CMENUITEM_H