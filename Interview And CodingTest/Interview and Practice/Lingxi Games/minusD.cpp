#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for(int i = 0;i < n; ++i){
        cin >> nums[i];
    }

    unordered_map<int, int> count;
    int maxlength = 0;

    for(int i=0; i < n;++i){
        count[nums[i]]++;
    }

    for(unordered_map<int, int>::iterator it = count.begin(); it != count.end(); ++it){
        int currLength = it->second;
        if (count.find(it->first + 1) != count.end()) {
            currLength += count[it->first+1];
        }
        maxlength = max(maxlength,currLength);
    }
    cout << maxlength;

    return 0;
}