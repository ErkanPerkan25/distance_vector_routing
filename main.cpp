#include <fstream>
#include <iostream>

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

    if (file.is_open()) {
        while (file.good()) {
            file >> router1;
            file >> router2;
            file >> cost;

            cout << router1 << " " << router2 << " " << cost << endl;
        } 
        file.close();
    }
    
    return 0;
}
