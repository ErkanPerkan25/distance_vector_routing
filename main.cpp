#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
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

    struct info{
        string name;
        int cost;
    };

    map<string, vector<info>> routers;


    if (file.is_open()) {
        while (file.good()) {
            file >> router1;
            file >> router2;
            file >> cost;
            
            Edge edge(router1,router2,cost);
            edges.push_back(edge);

            info data;
            data.name = router1;
            data.cost = 0;
            vector<info> table;
            table.push_back(data);


            routers.insert({router1, table});
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

            for(auto router : routers) {
                if (router.first == routerName) {
                    cout << "======" << routerName << "======" << endl;
                    for (int i=0; i < router.second.size(); i++) {
                        cout << router.second.at(i).name << ":<" << router.second.at(i).name << "," << router.second.at(i).cost << ">" << endl;
                    }
                    cout << "================" << endl;
                }
            }
             
        }
        else if (command == 'l') {
            for (auto router : routers) {
                cout << "======" << router.first << "======" << endl;
                for (int i=0; i < router.second.size(); i++) {
                    cout << router.second.at(i).name << ":<" << router.second.at(i).name << "," << router.second.at(i).cost << ">" << endl;
                }
                cout << "================" << endl;
            }
        }
        else if (command == 'u') {
            string routerName;
            cin >> routerName;

            for(auto router : routers){
                if (router.first == routerName) {
                    for (auto edge : edges) {
                        if(edge.getRouter1Name() == router.first) {
                            info tableData; 
                            tableData.name = edge.getRouter2Name();
                            tableData.cost = edge.getCost();


                            routers[routerName].push_back(tableData);
                        }
                    }
                }
            }

        }

        cout << "> ";
        cin >> command; 
    }

/*
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
                    cout << i.getNextHop(router) << endl;;
                }
            }

        }
        else if (command == 'l') {
            for (auto i : routers) {
                cout << i.getNextHop(i.getRouterName()) << endl;
            } 
        }
        else if (command == 'u') {
            string router; 
            cin >> router;

            for(auto i : edges){
                if(i.getRouter1Name() == router){
                    string otherRouter = i.getRouter2Name();                    
                    int cost = i.getCost();

                    for(auto j : routers){
                        if (j.getRouterName() == router) {
                            j.addNewHop(otherRouter, cost);
                        }
                    }
                }
            }

        }

        cout << "> ";
        cin >> command; 
    }

*/
    return 0;
}
