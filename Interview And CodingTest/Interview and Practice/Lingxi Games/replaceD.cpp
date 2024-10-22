#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n,x;
    vector<vector<int>> dp(21, vector<int>(191, 0));
    while (cin >> n) {
        dp[0][0] = 1;
        dp[1][0] = 1;
        for(int i = 2; i <= n; i++) {
            dp[i][0] = 1;
            for(int j = 0; j <= i; j++) {
                for(int k = 0; k <= i*(i-1)/2; k++) {
                    x = i-j-1;
                    if(dp[x][k] == 1){
                        dp[i][(i-x)*x+k] = 1;
                    }
                }
            }
        }
        for(int i = 0; i <= n*(n-1)/2; i++) {
            if(dp[n][i] == 1) {
                cout << i << ",";
            }
        }

        cout << n*(n-1)/2 << endl;
    }
    return 0;
}