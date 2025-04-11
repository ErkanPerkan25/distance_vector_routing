#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include "Edge.hpp"
#include "Router.hpp"


using namespace std;

int main(int argc, char *argv[]){
    if(argc!=2){
        cerr << "<USAGE>: ./exe <data-file>"<< endl;
        return 1;
    }

    ifstream file(argv[1]);

    string router1;
    string router2;
    int cost;

    vector<Edge> edges;
    vector<string> nodes;

    if (file.is_open()) {
        while (file.good()) {
            file >> router1;
            file >> router2;
            file >> cost;
            
            Edge edge(router1,router2,cost);
            edges.push_back(edge);

            nodes.push_back(router1);
            nodes.push_back(router2);
        } 


        file.close();
    }

    int count = 0;

    // don't know if im allowed to do this    
    sort(nodes.begin(), nodes.end());
    nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

    vector<Router> routers;

    for(auto i : nodes){
        Router router(i);
        routers.push_back(router);
    }

    char command;
    cout << "> ";

    cin >> command; 

    while(command != 'q'){
        if(command == 'q'){
            return 1;
        }
        else if(command == 'p'){
            string router;
            cin >> router;

            for(auto i : routers){
                if(i.getRouterName() == router){
                }
            }

        }

        cout << "> ";
        cin >> command; 
    }

    return 0;
}
