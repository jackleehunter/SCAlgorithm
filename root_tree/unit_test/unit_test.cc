#include "sc_rtree.h"

int main(int argc, char* argv[])
{
    class TestKeyOfValue {
    public:
        int operator() (int n) {
            return n;
        }
    };
    sc::algorithm::rtree::SCRTree<int, int, TestKeyOfValue> t;
    t.insert(10, 10);
    return 0;
}