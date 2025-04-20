#include <algorithm>
#include <csignal>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include "Edge.hpp"


using namespace std;

#define MAX_NUM 1e8 

struct vectorInfo{
    string destiantion;
    int cost;
};

struct edge{
    string source;
    string destiantion;
    int cost;
};

vector<vectorInfo> bellmans(int numVertices, vector<edge> edges, vector<string> nodes, int source_index, vector<vectorInfo> table){
    int dist[numVertices];
    for(int i=0; i < numVertices; i++){
        dist[i] = MAX_NUM;
    }
    dist[source_index] = 0;

    for(int i=0; i < numVertices; i++){

        for(edge e : edges){
            int src_index;
            int dst_index;
            string src = e.source;
            string dst = e.destiantion;

            for(int j=0; j < nodes.size(); j++){
                if(nodes[j] == src){
                    src_index = j;
                }
                else if(nodes[j] == dst){
                    dst_index = j;
                }
            }


           if(dist[src_index] != 1e8 && dist[src_index] + e.cost < dist[dst_index]){
                dist[dst_index] = dist[src_index] + e.cost;
                vectorInfo newEdge;
                newEdge.destiantion = dst;
                newEdge.cost = dist[dst_index];

                table.push_back(newEdge);
            }

        }
    }

    for(auto i : dist){
        cout << i << endl;
    }

    return table;
}


int main(int argc, char *argv[]){
    if(argc!=2){
        cerr << "<USAGE>: ./exe <data-file>"<< endl;
        return 1;
    }

    ifstream file(argv[1]);

    string router1;
    string router2;
    int cost;

    map<string, vector<vectorInfo>> network;

    vector<edge> edges;
    vector<string> nodes;

    int index=0;
    if (file.is_open()) {
        while (file.good()) {
            file >> router1;
            file >> router2;
            file >> cost;

            nodes.push_back(router1);
            nodes.push_back(router2);
            
            edge edge;
            edge.source = router1;
            edge.destiantion = router2;
            edge.cost = cost;
            edges.push_back(edge);

        } 

        file.close();
    }

    sort(nodes.begin(), nodes.end());
    auto it = unique(nodes.begin(), nodes.end());
    nodes.erase(it, nodes.end());

    for(int i=0; i < nodes.size(); i++){
            vectorInfo in;
            in.destiantion = nodes[i];
            in.cost = 0;
            vector<vectorInfo> rTable;
            rTable.push_back(in);

            network.insert({nodes[i], rTable});
    }

    int numVertices = nodes.size();

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
            
            for(auto router : network){
                if (router.first == routerName) {
                    cout << "======"  << router.first << "======" << endl;
                    for (auto i : router.second) {
                        cout << i.destiantion << ":<" << i.destiantion << "," << i.cost << ">" << endl;
                    }
                    cout << "================" << endl;
                }
            }
            
        }
        else if (command == 'l') {
            for(auto router : network){
                cout << "======" << router.first << "======" << endl;
                for(auto i : router.second){
                    cout << i.destiantion << ":<" << i.destiantion << "," << i.cost << ">" << endl;
                }
                cout << "================" << endl;
            }
        }
        else if (command == 'u') {
            string routerName;
            cin >> routerName;
            
            int src;
            for(int i=0; i<nodes.size(); i++){
                if(nodes[i] == routerName){
                    src = i;
                }
            }

            vector<vectorInfo> newE = bellmans(numVertices, edges, nodes, src, network[routerName]);

            network[routerName] = newE;
        }

        cout << "> ";
        cin >> command; 
    }

    return 0;
}
