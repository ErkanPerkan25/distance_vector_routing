#include <algorithm>
#include <csignal>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "Edge.hpp"


using namespace std;

struct vectorInfo{
    string destiantion;
    int cost;
};

struct router{
    string name;
    map<string, vectorInfo> routingTable; // destiantion -> destiantion and cost
    map<string, int> neigbours;
};

int main(int argc, char *argv[]){
    if(argc!=2){
        cerr << "<USAGE>: ./exe <data-file>"<< endl;
        return 1;
    }

    ifstream file(argv[1]);

    string router1;
    string router2;
    int cost;

    map<string, router> network;


    if (file.is_open()) {
        while (file.good()) {
            file >> router1;
            file >> router2;
            file >> cost;

            // if router does not exist, create it
            if(network.find(router1) == network.end()){
                router newRouter;
                vectorInfo table;

                table.destiantion = router1;
                table.cost = 0;

                newRouter.name = router1;
                newRouter.routingTable[router1] = table;

                network.insert({router1, newRouter});
            }

            if(network.find(router2) == network.end()){
                router newRouter;
                vectorInfo table;

                table.destiantion = router2;
                table.cost = 0;


                newRouter.name = router2;
                newRouter.routingTable[router2] = table;
                network.insert({router2, newRouter});
            }

            network[router1].neigbours[router2] = cost;
            network[router2].neigbours[router1] = cost;
        
        } 

        file.close();
    }

    char command;
    cout << "> ";

    cin >> command; 

    while(command != 'q'){
        if(command == 'q'){
            return 1;
        }
        else if(command == 'p'){
            string routerName;
            cin >> routerName;

            if(network.find(routerName) != network.end()){
                cout << "=======" << routerName << "=======" <<endl;
                for(auto i : network[routerName].routingTable){
                    cout << i.first << ":<" << i.second.destiantion << "," << i.second.cost << ">" << endl;
                }
                cout << "================" << endl;
            }
            
        }
        else if (command == 'l') {
            for(auto router : network){
                cout << "======" << router.first << "======" << endl;
                for(auto i : router.second.routingTable){
                    cout << i.first << ":<" << i.second.destiantion << "," << i.second.cost << ">" << endl;
                }
                cout << "================" << endl;
            }
        }
        else if (command == 'u') {
            string routerName;
            cin >> routerName;

            if (network.find(routerName) != network.end()) {
                for(auto i : network[routerName].neigbours){
                    if(network[routerName].routingTable.find(i.first) == network[routerName].routingTable.end()){
                        cout << "din't find it" << endl;
                        vectorInfo newT;
                        newT.destiantion = i.first;
                        newT.cost = i.second;

                        network[routerName].routingTable.insert({i.first, newT});
                    }
                    else{
                    }

                }
            }
            
        }

        cout << "> ";
        cin >> command; 
    }

    return 0;
}
