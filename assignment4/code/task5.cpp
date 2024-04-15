#include <set>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <typeinfo>
#include <cstdlib>
#include <random>
#include <type_traits>
#include <map>

using namespace std;

class BronKerbosch {
public:
    BronKerbosch(const vector<vector<int>>& adjacencyMatrix) 
        : adjMatrix(adjacencyMatrix) {}

    void findCliques() {
        set<int> R;
        set<int> P;
        set<int> X;

        for (int i = 0; i < adjMatrix.size(); ++i) {
            P.insert(i);
        }

        bronKerbosch(R, P, X);
    }

private:
    const vector<vector<int>>& adjMatrix;

    void bronKerbosch(set<int> R, set<int> P, set<int> X) {
        if (P.empty() && X.empty()) {
            printSet(R);
            return;
        }

        while (!P.empty()) {
            int vertex = *P.begin();
            set<int> neighborsP = getPossibleNeighbors(vertex, P);
            set<int> neighborsX = getPossibleNeighbors(vertex, X);

            bronKerbosch(unionSets(R, { vertex }), intersectionSets(P, neighborsP), intersectionSets(X, neighborsX));
            
            P.erase(vertex);
            X.insert(vertex);
        }
    }

    set<int> getPossibleNeighbors(int vertex, const set<int>& vertices) {
        set<int> neighbors;
        for (int v : vertices) {
            if (adjMatrix[vertex][v] == 1) {
                neighbors.insert(v);
            }
        }
        return neighbors;
    }

    set<int> unionSets(const set<int>& set1, const set<int>& set2) {
        set<int> result = set1;
        result.insert(set2.begin(), set2.end());
        return result;
    }

    set<int> intersectionSets(const set<int>& set1, const set<int>& set2) {
        set<int> result;
        for (int elem : set1) {
            if (set2.count(elem) > 0) {
                result.insert(elem);
            }
        }
        return result;
    }

    void printSet(const set<int>& s) {
        if (!s.empty()) {
            ostringstream oss;
            auto it = s.begin();
            oss << "{" << *it++;
            while (it != s.end()) {
                oss << ", " << *it++;
            }
            oss << "}";
            cout << oss.str() << endl;
        }
    }
};

int main() {
    vector<vector<int>> adjacencyMatrix;
    string line;

    while (getline(cin, line) && !line.empty()) {
        vector<int> row;
        istringstream iss(line);
        int val;
        while (iss >> val) {
            row.push_back(val);
        }
        adjacencyMatrix.push_back(row);
    }

    BronKerbosch bronKerbosch(adjacencyMatrix);
    bronKerbosch.findCliques();

    return 0;
}
