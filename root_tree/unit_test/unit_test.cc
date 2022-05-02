#include "sc_rtree.h"
#include <string>
#include <iostream>

class RtDevice {
public:
    RtDevice() : RtDevice(-1, "") {}
    RtDevice(int id, const std::string& d) : device_id_(id), description_(d) {}
    ~RtDevice() {}

    int DeviceId() {return device_id_;}
    const std::string& Description() const {return description_;}
private:
    int device_id_;
    std::string description_;
};

class RtDeviceOfKey {
public:
    int operator() (RtDevice& v) {
        return v.DeviceId();
    }
};

int main(int argc, char* argv[])
{
    typedef sc::algorithm::rtree::SCRTree<int, RtDevice, RtDeviceOfKey> RootTree;
    RootTree t;
    
    RtDevice d_1(0, "aaaaa");
    std::pair<RootTree::iterator, bool> ret = t.insert(t.begin(), d_1);
    if (!ret.second)
    {
        std::cout << "insert failed. object: " << d_1.DeviceId() << ":" << d_1.Description() << std::endl;
        return -1;
    }

    std::cout << "sizeof RtDevice: " << sizeof(RtDevice) << std::endl;

    RtDevice d_2(10, "bbbbb");
    t.insert(0, d_2);
    
    RtDevice d_3(11, "bbbbb");
    t.insert(0, d_3);

    std::cout << "find begin." << std::endl;
    RootTree::iterator fitr = t.find(11);
    if (fitr == t.end())
    {
        std::cout << "Can't not find 11" << std::endl;
        return -1;
    }
    std::cout << "find end, OK" << std::endl;

    RtDevice d_31(101, "bbbbb");
    t.insert(11, d_31);
    RtDevice d_32(102, "bbbbb");
    t.insert(11, d_32);
    RtDevice d_33(103, "bbbbb");
    t.insert(11, d_33);

    for (int i = 0; i != 7; ++i)
    {
        int key = 10200 + i + 1;
        RtDevice d_32x(key, "ccccc");
        t.insert(102, d_32x);
    }

    std::cout << "Current tree size: " << t.size() << ", max deepth: " << t.MaxDeepth() << "." << std::endl;

    int count = 0;
    for (RootTree::iterator itr = t.begin(); itr != t.end(); ++itr)
    {
        std::cout << (*itr).DeviceId() << ":" << (*itr).Description() << " ";
    }
    std::cout << std::endl;

    t.erase(102);

    for (RootTree::iterator itr = t.begin(); itr != t.end(); ++itr)
    {
        std::cout << (*itr).DeviceId() << ":" << (*itr).Description() << " ";
    }
    std::cout << std::endl;

    return 0;
}