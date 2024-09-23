#ifndef MYMENU_CMENU_H
#define MYMENU_CMENU_H

#include "CMenuItem.h"
#include <cstddef>

class CMenu
{
public:
    CMenu();
    CMenu(std::string, CMenuItem *, size_t);
    int getSelect() const;
    bool getRunning();
    void setRunning(bool);
    std::string getTitle();
    size_t getCount() const;
    CMenuItem *getItems();
    void print();
    void printTitle();
    int runCommand();

private:
    int m_select{-1};
    size_t m_count{};
    bool m_running{true};
    std::string m_title{};
    CMenuItem *m_items{};
};

#endif // MYMENU_CMENU_H