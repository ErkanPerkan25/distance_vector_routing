/**************************************************************************************
* Author: Eric Hansson
* Date: 04/22/2024
* File: dvr.cpp
* Purpose: To simulate updating routing tables of routers with the distance vector 
* routing approach
**************************************************************************************/
#include <csignal>
#include <fstream>
#include <iostream>
#include <map>


using namespace std;

// Struct for routing table information
struct vectorInfo{
    string destiantion;
    int cost;
};

// A structure of a router
struct router{
    string name;
    map<string, vectorInfo> routingTable; // destiantion -> destiantion and cost
    map<string, int> neigbours; // name of neigbours, and the cost to it
};

int main(int argc, char *argv[]){
    // Check if user put in a file, if not show usage error messsage
    if(argc!=2){
        cerr << "<USAGE>: ./exe <data-file>"<< endl;
        return 1;
    }

    // Read in the file
    ifstream file(argv[1]);

    // For reading in data
    string router1;
    string router2;
    int cost;

    // The network which contains routers
    map<string, router> network;

    // reads in the data from the file
    if (file.is_open()) {
        while (file.good()) {
            file >> router1;
            file >> router2;
            file >> cost;

            // if router does not exist, create it
            if(network.find(router1) == network.end()){
                // Create router and routing table for it
                router newRouter;
                vectorInfo table;

                // set information about the router it self for the table
                table.destiantion = router1;
                table.cost = 0;
                
                // Sets the name of the router and it's routing table
                newRouter.name = router1;
                newRouter.routingTable[router1] = table;

                // inserts the new router to the network
                network.insert({router1, newRouter});
            }

            // if router does not exist, create it
            if(network.find(router2) == network.end()){
                // Create router and routing table for it
                router newRouter;
                vectorInfo table;

                // set information about the router it self for the table
                table.destiantion = router2;
                table.cost = 0;


                // Sets the name of the router and it's routing table
                newRouter.name = router2;
                newRouter.routingTable[router2] = table;
                
                // inserts the new router to the network
                network.insert({router2, newRouter});
            }

            // Sets that the routers we read are neigbours because they have a link between them
            network[router1].neigbours[router2] = cost;
            network[router2].neigbours[router1] = cost;
        
        } 

        file.close();
    }

    // Usage for commands
    char command;
    cout << "> ";

    // Reads in command by user
    cin >> command; 

    // As long as not quiting the program, keep giving command line
    while(command != 'q'){
        // If 'p', exit program
        if(command == 'q'){
            return 1;
        }
        // On 'p' and router name it will print out specific router and it's routing table
        else if(command == 'p'){
            string routerName;
            cin >> routerName;

            // Checks if exists
            if(network.find(routerName) != network.end()){
                // prints out routing table of the router
                cout << "=======" << routerName << "=======" <<endl;
                for(auto i : network[routerName].routingTable){
                    cout << i.first << ":<" << i.second.destiantion << "," << i.second.cost << ">" << endl;
                }
                cout << "================" << endl << endl;
            }
            
        }
        // On 'l', print all routers and their routing tables
        else if (command == 'l') {
            for(auto router : network){
                cout << "======" << router.first << "======" << endl;
                for(auto i : router.second.routingTable){
                    cout << i.first << ":<" << i.second.destiantion << "," << i.second.cost << ">" << endl;
                }
                cout << "================" << endl << endl;
            }
        }
        // On 'u', update router's routing table
        else if (command == 'u') {
            // reads in router name
            string routerName;
            cin >> routerName;
            
            // checks if router exits
            if (network.find(routerName) != network.end()) {    
                // goes through the routers neigbours
                for(auto i  : network[routerName].neigbours){
                    
                    // goes through eachs neigbours routing table
                    for (auto j : network[i.first].routingTable){
                        // if the table has the  
                        if(i.first == routerName){
                            continue;
                        }
                    
                        // new cost to the destiantion from neighbour
                        int newCost =  i.second + j.second.cost; 

                        // If this hop does not exits in the source routers or the cost to the hop is lower than other
                        // then add it to the routing table of the source node
                        if(network[routerName].routingTable.find(j.first) == network[routerName].routingTable.end() || newCost < network[routerName].routingTable.find(j.first)->second.cost){
                        
                            vectorInfo newT;
                            newT.destiantion = i.first;
                            newT.cost = newCost;

                            //network[routerName].routingTable.insert({j.first, newT});
                            network[routerName].routingTable[j.first] = {i.first, newCost};
                        }

                    }
                }
            }
            else {
                cout << "Router not found" << endl;
            }
            
        }
        
        // Reads the next command
        cout << "> ";
        cin >> command; 
    }

    return 0;
}
