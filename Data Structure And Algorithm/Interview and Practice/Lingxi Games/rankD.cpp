#include <iostream>
#include <iterator>
#include <set>
#include <vector>
using namespace std;

int main() {
    int length;
    cin >> length;
    vector<int> arr(length);
    for(int i = 0; i < length; i++) {
        cin >> arr[i];        
    }
    set<int> uniqueNums(arr.begin(), arr.end());
    if(uniqueNums.size() < 3){
        cout << *uniqueNums.rbegin();
    }
    else {
        auto it = uniqueNums.rbegin();
        advance(it, 2);
        cout << *it;
    }
    return 0;    
}