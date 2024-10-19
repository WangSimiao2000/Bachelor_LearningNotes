#include <vector>
using namespace std;

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 计算三维点是否投影在三角形内部
     * @param P float浮点型vector 
     * @param A float浮点型vector 
     * @param B float浮点型vector 
     * @param C float浮点型vector 
     * @return bool布尔型
     */
    bool IsPointProjectInTriangle(vector<float>& P, vector<float>& A, vector<float>& B, vector<float>& C) {
        // write code here
        vector<float> AB = vectorSub(B, A);
        vector<float> AC = vectorSub(C, A);
        vector<float> AP = vectorSub(P, A);
        vector<float> normal = crossProduct(AB, AC); // 法向量

        // P点到平面的距离
        float distance;
        distance = dotProduct(AP, normal) / getVectorLength(normal);

        // 投影点
        vector<float> P1(3);
        P1[0] = P[0] - distance * normal[0];
        P1[1] = P[1] - distance * normal[1];
        P1[2] = P[2] - distance * normal[2];

        bool flag = (sameSide(A, B, C, P1) && sameSide(B, C, A, P1) && sameSide(C, A, B, P1));
        
        return flag;
    }

    // 叉乘
    vector<float> crossProduct(const vector<float>& A, const vector<float>& B) {
        vector<float> res(3);
        res[0] = A[1] * B[2] - A[2] * B[1];
        res[1] = A[2] * B[0] - A[0] * B[2];
        res[2] = A[0] * B[1] - A[1] * B[0];
        return res;
    }

    // 点乘
    float dotProduct(const vector<float>& A, const vector<float>& B) {
        float res = A[0] * B[0] + A[1] * B[1] + A[2] * B[2];
        return res;
    }

    // 向量长度
    float getVectorLength(const vector<float>& A) {
        float res = sqrt(dotProduct(A, A));
        return res;
    }

    // 向量相减
    vector<float> vectorSub(const vector<float>& A, const vector<float>& B) {
        vector<float> res(3);
        res[0] = A[0] - B[0];
        res[1] = A[1] - B[1];
        res[2] = A[2] - B[2];
        return res;
    }

    // 判断点是否在边同侧
    bool sameSide(vector<float>& A, vector<float>& B, vector<float>& C, vector<float>& P) {
        vector<float> AB = vectorSub(B, A);
        vector<float> AC = vectorSub(C, A);
        vector<float> AP = vectorSub(P, A);
        vector<float> c1 = crossProduct(AB, AC);
        vector<float> c2 = crossProduct(AB, AP);
        // 排除点在边上的情况
        if(getVectorLength(c2) == 0){
            return false;
        }
        if(dotProduct(c1, c2) >= 0){
            return true;
        }
        return false;
    }

};