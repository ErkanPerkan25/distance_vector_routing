#ifndef __ROUTER__HPP__
#define __ROUTER__HPP__

#include <iostream>
#include <string>
#include <vector>

class Router{
private:
    std::string _name;
    std::vector<std::string> _nextHops;
    std::vector<int> _cost;


public:
    Router() : _name(""), _nextHops(), _cost() {}

    Router(const std::string &name); 

    std::string getRouterName() {return _name;}

    std::string getNextHop();

};

#endif
