#include <vector>
#include <list>
#include <iostream>

using std::vector;
using std::list;
using std::cout;
using std::endl;

int main() {
    list<vector<int>> lofv{};

    for (int i = 0; i < 5; ++i) {
        vector<int> v{};
        for (int j = 0; j < 2; ++j) {
            v.push_back(j);
        }
        lofv.push_back(v);
    }
    
    cout << "List:" << endl;
    for (auto &v : lofv) {
        cout << "Vector: ";
        for (auto &i : v) {
            cout << i << " ";
        }
        cout << endl;
    }
}
