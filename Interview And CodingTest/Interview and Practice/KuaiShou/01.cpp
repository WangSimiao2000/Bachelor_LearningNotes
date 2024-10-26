#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>

using namespace std;

/*
给定多个只包括( ) { } [ ]的字符串，判断字符串是否有效，有效字符串必须满足：
左括号必须要有相同类型的有括号闭合
左括号必须以正确顺序闭合
每个有括号都有一个对应类型的左括号

输入：
第一行输入N表示有N条字符串
接下来N行每行是一串字符串且不为空

输出
N行输出，输出括号对数或False
*/

int main() {
    int N;
    cin >> N; // 读取字符串数量
    cin.ignore(); // 忽略换行符

    for (int i = 0; i < N; ++i) {
        string str;
        getline(cin, str); // 读取每一行字符串

        stack<char> s; // 创建栈
        unordered_map<char, char> bracketMap = {
            {')', '('},
            {'}', '{'},
            {']', '['}
        };

        int pairCount = 0; // 记录有效括号对数
        bool isValid = true; // 记录是否有效

        for (char ch : str) {
            // 如果是左括号，则入栈
            if (ch == '(' || ch == '{' || ch == '[') {
                s.push(ch);
            } 
            // 如果是右括号，检查栈顶
            else if (ch == ')' || ch == '}' || ch == ']') {
                // 栈为空或栈顶不匹配，则无效
                if (s.empty() || s.top() != bracketMap[ch]) {
                    isValid = false; // 标记为无效
                    break; // 跳出循环
                }
                s.pop(); // 匹配成功，出栈
                pairCount++; // 增加有效括号对数
            }
        }

        // 如果栈不为空，表示有未闭合的左括号
        if (!isValid || !s.empty()) {
            cout << "False" << endl; // 输出 False
        } else {
            cout << pairCount << endl; // 输出有效括号对数
        }
    }

    return 0;
}
