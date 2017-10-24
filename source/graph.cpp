//
// Created by wenderson on 29/09/17.
//

#include "graph.h"

Graph::Graph(const char str[]) {
    std::ifstream file(str);
    int value;

    if(file.is_open()) {

        file >> size;
        adjacencyMatrix = new int* [size];

        for(int i = 0; i < size; i++) {
            adjacencyMatrix[i] = new int [size]();
        }

        for(int i = 0; i < size; i++) {
            for(int j = 0; j < size; j++) {
                file >> value;
                adjacencyMatrix[i][j] = value;
            }
        }



    }

}

Graph::Graph(unsigned int sizeIn) {
    size = sizeIn;
    adjacencyMatrix = new int* [size];
    for(int i = 0; i < size; i++) {
        adjacencyMatrix[i] = new int [size]();
    }
}


bool Graph::Compare(void* i, void* j) {

    return ( (Vertex*) i )->ID == ( (Vertex*) j )->ID ? true : false;
}

Graph Graph::Prim(int root) {
    if(root >= 0 && root < size) {




        std::vector<Vertex> vertexes(size);
        for (int i = 0; i < size; i++) {
            vertexes[i].ID = i;
        }

        MinHeap<Vertex> vertexHeap;
        vertexHeap.Insert(vertexes[root], 0);

        for(int i = 0; i < size; i++){
            if(i != root)
                vertexHeap.Insert(vertexes[i], INT_MAX);
        }

        vertexes.clear();

        HeapElement<Vertex>* pSonNode;
        HeapElement<Vertex> fatherNode;

        while( !vertexHeap.Empty() ){

            fatherNode = vertexHeap.Extract();

            for(int i = 0; i < size; i++) {
                if(adjacencyMatrix[fatherNode.element.ID][i] > 0) {

                    int sonNodeHeapIndex = vertexHeap.SearchOnHeap(Vertex(i), pSonNode, Compare);

                    if (sonNodeHeapIndex >= 0 && adjacencyMatrix[fatherNode.element.ID][i] < pSonNode->priority) {
                        pSonNode->element.IDFather = fatherNode.element.ID;

                        vertexHeap.DecreaseKey(sonNodeHeapIndex, adjacencyMatrix[fatherNode.element.ID][i]);
                    }
                }

            }

            vertexes.push_back(fatherNode.element);
        }

        Graph returnGraph(size);

        int j, k;
        std::cout << std::endl;

        for(int i = 0; i < vertexes.size(); i++){

            j = vertexes[i].IDFather;
            k = vertexes[i].ID;
            //std::cout << "Vertex: " << vertexes[i].ID << " Parent: " << vertexes[i].IDFather << std::endl;
            if(j != -1) {
                returnGraph.adjacencyMatrix[j][k] = adjacencyMatrix[j][k];
                returnGraph.adjacencyMatrix[k][j] = adjacencyMatrix[k][j];
            }


        }

        return returnGraph;



    }
    return Graph(1);

}

void PrintGraph(const Graph& g, const int pd){
    int sum = 0;
    for(int i = 0; i < g.Size(); i++) {
        for (int j = 0; j < g.Size(); j++) {
            std::cout << std::fixed << std::setfill('0') << std::setw(pd)
                      << g.adjacencyMatrix[i][j] << " ";
            sum += g.adjacencyMatrix[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "Sum: " << sum/2 << std::endl;
}

Graph Graph::Dijkstra(int root) {
    if(root >= 0 && root < size) {

        std::vector<Vertex> vertexes(size);
        for (int i = 0; i < size; i++) {
            vertexes[i].ID = i;
        }

        MinHeap<Vertex> vertexHeap;
        vertexHeap.Insert(vertexes[root], 0);

        for(int i = 0; i < size; i++){
            if(i != root)
                vertexHeap.Insert(vertexes[i], INT_MAX);
        }

        vertexes.clear();

        HeapElement<Vertex>* pSonNode;
        HeapElement<Vertex> fatherNode;
        int weight;

        while( !vertexHeap.Empty() ){

            fatherNode = vertexHeap.Extract();

            for(int i = 0; i < size; i++) {
                if(adjacencyMatrix[fatherNode.element.ID][i] > 0) {

                    int sonNodeHeapIndex = vertexHeap.SearchOnHeap(Vertex(i), pSonNode, Compare);

                    if (sonNodeHeapIndex >= 0) {
                        weight = adjacencyMatrix[fatherNode.element.ID][i] + fatherNode.priority;

                        if(weight < pSonNode->priority) {
                            pSonNode->element.IDFather = fatherNode.element.ID;

                            vertexHeap.DecreaseKey(sonNodeHeapIndex, weight);
                        }
                    }
                }

            }

            vertexes.push_back(fatherNode.element);
        }

        Graph returnGraph(size);

        int j, k;
        std::cout << std::endl;

        for(int i = 0; i < vertexes.size(); i++){

            j = vertexes[i].IDFather;
            k = vertexes[i].ID;
            //std::cout << "Vertex: " << vertexes[i].ID << " Parent: " << vertexes[i].IDFather << std::endl;
            if(j != -1) {
                returnGraph.adjacencyMatrix[j][k] = adjacencyMatrix[j][k];
                returnGraph.adjacencyMatrix[k][j] = adjacencyMatrix[k][j];
            }


        }

        return returnGraph;



    }
    return Graph(1);

}

std::vector<std::set<int>> Graph::SubSets(const std::set<int> s){
    std::vector<std::set<int>> subSets;
    std::set<int> k;
    subSets.push_back(k);
    int anteriorSetLocation = 0;
    std::set<int> dynamicSet;

    for(int subSetSize = 1; subSetSize < s.size(); subSetSize++){

        while(subSets[anteriorSetLocation].size() < subSetSize){
            dynamicSet = subSets[anteriorSetLocation];
            if (dynamicSet.size() == 0){
                for(std::set<int>::iterator it = s.begin(); it != s.end(); it++){
                    dynamicSet = subSets[anteriorSetLocation];
                    dynamicSet.insert(*it);
                    subSets.push_back(dynamicSet);
                }
            }

            else{
                std::set<int>::iterator it = s.find(*(--dynamicSet.end()));
                it++;
                while(it != s.end()){
                    dynamicSet = subSets[anteriorSetLocation];
                    dynamicSet.insert(*it);
                    subSets.push_back(dynamicSet);
                    it++;
                }
            }
            anteriorSetLocation++;
        }


    }
    subSets.push_back(s);
    return subSets;
}

unsigned long long Graph::TravellingSalesman(int root) {
    int arSet[size-1];
    int counter = 0;

    for(int i = 0; i < size; i++){
        if(i != root){
            arSet[counter] = i;
            counter++;
        }
    }

    std::set<int> nodeSet(arSet, arSet+size-1);
    std::vector<std::set<int>> subSets(SubSets(nodeSet));
    std::map <std::pair<int,std::set<int>>, TravellingData> travellingMap;

    for(std::set<int>::iterator it = nodeSet.begin(); it != nodeSet.end(); it++)
        travellingMap[std::make_pair(*it, subSets[0])] = TravellingData(adjacencyMatrix[root][*it], root);

    std::set<int> differenceSubSet;
    std::set<int> currentSubSet;
    std::set<int> anteriorSubSet;
    unsigned long long minimumCost, currentCost;
    int parent;

    for(int i = 1; i < subSets.size(); i++){
        differenceSubSet.clear();

        currentSubSet = subSets[i];

        std::set_difference(nodeSet.begin(), nodeSet.end(), currentSubSet.begin(), currentSubSet.end(),
                            std::inserter(differenceSubSet, differenceSubSet.end()) );

        if(differenceSubSet.size() == 0){
            minimumCost = ULLONG_MAX;

            for(std::set<int>::iterator minimumIt = currentSubSet.begin(); minimumIt != currentSubSet.end(); minimumIt++){
                anteriorSubSet = currentSubSet;
                anteriorSubSet.erase(*minimumIt);
                currentCost = travellingMap[std::make_pair(*minimumIt, anteriorSubSet)].distance + adjacencyMatrix[*minimumIt][root];

                if(currentCost < minimumCost){
                    minimumCost = currentCost;
                    parent = *minimumIt;
                }
            }

            travellingMap[std::make_pair(root, currentSubSet)] = TravellingData(minimumCost, parent);

        }
        else{
            for(std::set<int>::iterator dSubSetIt = differenceSubSet.begin(); dSubSetIt != differenceSubSet.end(); dSubSetIt++){
                minimumCost = ULLONG_MAX;

                for(std::set<int>::iterator minimumIt = currentSubSet.begin(); minimumIt != currentSubSet.end(); minimumIt++){
                    anteriorSubSet = currentSubSet;
                    anteriorSubSet.erase(*minimumIt);
                    currentCost = travellingMap[std::make_pair(*minimumIt, anteriorSubSet)].distance + adjacencyMatrix[*minimumIt][*dSubSetIt];

                    if(currentCost < minimumCost){
                        minimumCost = currentCost;
                        parent = *minimumIt;
                    }
                }

                travellingMap[std::make_pair(*dSubSetIt, currentSubSet)] = TravellingData(minimumCost, parent);
            }
        }
    }

    std::set<int> s(nodeSet);
    std::vector<int> solution;
    std::cout << "Total distance to go through: " <<travellingMap[std::make_pair(root, s)].distance << std::endl;
    parent = root;
    int c = s.size();

    while(c >= 0) {
        solution.push_back(parent+1);
        parent = travellingMap[std::make_pair(parent, s)].parent;
        s.erase(parent);
        c--;
    }
    solution.push_back(parent+1);
    int i;
    std::cout << "Circuit to go through: ";
    for(i = solution.size() - 1; i > 0; i--)
        std::cout << solution[i] << " - ";
    std::cout << solution[i];

    return travellingMap[std::make_pair(root, nodeSet)].distance;
}
