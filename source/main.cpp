#include <iostream>
#include "graph.h"


using namespace std;




int main(int argc, char *argv[]) {
    Graph firstGraph(argv[1]);
    firstGraph.TravellingSalesman(0);

}