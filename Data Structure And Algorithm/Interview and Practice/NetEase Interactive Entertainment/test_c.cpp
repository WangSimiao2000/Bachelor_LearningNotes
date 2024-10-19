#include <iostream>
#include <vector>
using namespace std;

struct Seal{
    int L, R, T, D;
    int remainTime;
    bool active;
    bool finished;
};

int main() {
    int n;
    cin >> n;

    vector<Seal> seals(n);

    for(int i = 0; i < n; i++){
        cin >> seals[i].L >> seals[i].R >> seals[i].T >> seals[i].D;
        seals[i].remainTime = seals[i].T;
        seals[i].active = false;
        seals[i].finished = false;
    }

    int S = 0;
    bool progress = true;

    while (progress) {
        progress = false;
        for(int i = 0 ; i < n; ++i){
            if(seals[i].finished) continue;
            // 圣印 i 激活中
            if(seals[i].active){
                // 圣印 i 激活中断
                if(!(seals[i].L < S && S < seals[i].R)){
                    seals[i].finished = false;
                    //cout << "圣印 " << i+1 << " 激活中断, 修练值 S = " << S << endl;
                } else{
                    seals[i].remainTime--;
                    if(seals[i].remainTime == 0){
                        S += seals[i].D;
                        seals[i].finished = true;
                        //cout<<"圣印 " << i+1 << " 激活完成, 修练值增加到 S = " << S << endl;
                    }                    
                    progress = true;
                }
            }
            // 圣印 i 未激活过
            else {
                // 圣印可以激活了
                if(seals[i].L <= S && S <= seals[i].R){
                    seals[i].active = true;
                    seals[i].remainTime = seals[i].T;
                    progress = true;
                    //cout<<"圣印 " << i+1 << " 开始激活, 修练值 S = " << S << endl;
                }
            }
        }
    }
    cout << S << endl;

    // 回车退出控制台
    //system("pause");
    return 0;
}