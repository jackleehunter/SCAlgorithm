
#include "sc_slink_list.h"
#include <string>
#include <iostream>

class TestData {
public:
    
    int idx_;
    std::string description_;
};

int main(int argc, char* argv[])
{
    typedef sc::algorithm::slinklist::SCSLinkList<TestData> LinkList;

    LinkList s;
    for (int i = 0; i != 10; ++i)
    {
        TestData d;
        d.idx_ = i;
        d.description_ = "aaaa";
        s.push_back(d);
    }

    std::cout << "push back." << std::endl;
    for (LinkList::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
        std::cout << "idx: " << (*itr).idx_ << " description: " << (*itr).description_ << "." << std::endl;
    }

    for (LinkList::iterator itr = s.begin(); itr != s.end(); )
    {
        if ((*itr).idx_ == 2)
        {
            itr = s.erase(itr);
        }
        else
        {
            ++itr;
        }
    }

    std::cout << "erase show:" << std::endl;
    for (LinkList::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
        std::cout << "idx: " << (*itr).idx_ << " description: " << (*itr).description_ << "." << std::endl;
    }

    for (LinkList::iterator itr = s.begin(); itr != s.end(); )
    {
        if ((*itr).idx_ == 9)
        {
            itr = s.erase(itr);
        }
        else
        {
            ++itr;
        }
    }

    std::cout << "erase tail show:" << std::endl;
    for (LinkList::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
        std::cout << "idx: " << (*itr).idx_ << " description: " << (*itr).description_ << "." << std::endl;
    }

    s.pop_back();
    std::cout << "pop_back show:" << std::endl;
    for (LinkList::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
        std::cout << "idx: " << (*itr).idx_ << " description: " << (*itr).description_ << "." << std::endl;
    }

    LinkList::iterator pre_itr;
    for (LinkList::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
        if ((*itr).idx_ == 5)
        {
            pre_itr = itr;
        }
    }

    TestData insert_data;
    insert_data.idx_ = 100;
    insert_data.description_ = "helloworld.";

    s.insert(pre_itr, insert_data);
    std::cout << "insert show:" << std::endl;
    for (LinkList::iterator itr = s.begin(); itr != s.end(); ++itr)
    {
        std::cout << "idx: " << (*itr).idx_ << " description: " << (*itr).description_ << "." << std::endl;
    }
    return 0;
}