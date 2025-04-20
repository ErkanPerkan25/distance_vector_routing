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
    Edge() : _router1(""), _router2(""), _cost(1e8) {}

    Edge(std::string router1, std::string router2, int cost) : _router1(router1), _router2(router2), _cost(cost) {}

    // Accessor and Modifers
    const  std::string &getRouter1Name() const {return _router1;}
    std::string &getRouter1Name() {return _router1;}
    
    const std::string &getRouter2Name() const {return _router2;}
    std::string &getRouter2Name() {return _router2;}

    const int &getCost() const {return _cost;}
    int &getCost() {return _cost;}

};

#endif
