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

void solveDeliveryProblem(int n, int k, int l, const vector<int>& cities) {
    int beamer_count = 0;
    int cata_count = 0;

    for (int i = 0; i < n; ++i) {
        if (cities[i] == 1) {  
            beamer_count++;
        } else if (cities[i] == 2) {  
            cata_count++;
        } else {  
            if (beamer_count > 0 && l > 0) {  
                cata_count++;
            } else if (cata_count > 0 && k > 0) {  
                beamer_count++;
            }
        }
    }

    if (beamer_count == 0) {
        cout << "beamer:-1" << endl;
    } else {
        cout << "beamer:" << beamer_count << endl;
    }

    if (cata_count == 0 || beamer_count == 0) {  
        cout << "cata:-1" << endl;
    } else {
        cout << "cata:-1" << endl;
    }
}

int main() {
    int n, k, l;
    cin >> n >> k >> l;

    vector<int> cities(n);
    for (int i = 0; i < n; ++i) {
        cin >> cities[i];
    }

    solveDeliveryProblem(n, k, l, cities);

    return 0;
}
