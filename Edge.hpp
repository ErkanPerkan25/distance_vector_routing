#ifndef __EDGE__HPP_
#define __EDGE__HPP_

#include <iostream>
#include <string>

class Edge{
private:
    std::string _router1;
    std::string _router2;
    int _cost;

public:
    Edge() : _router1(""), _router2(""), _cost(0) {}

    Edge(std::string router1, std::string router2, int cost) : _router1(router1), _router2(router2), _cost(cost) {}

    std::string getRouter1Name() const {return _router1;}
    std::string getRouter2Name() const {return _router2;}
    int getCost() const {return _cost;}

};

#endif
