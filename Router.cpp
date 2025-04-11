#include "Router.hpp"
#include <string>

using namespace std;

Router::Router(const string &name){
    _name = name;
    _nextHops.push_back(name);
    _cost.push_back(0);
}

string
Router::getNextHop(){

}
