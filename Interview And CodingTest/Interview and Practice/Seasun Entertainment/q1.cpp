#include <cctype>
#include <stack>
#include <string>
using namespace std;
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param expr string字符串 
     * @return double浮点型
     */
    double EvaluateExpr(string expr) {
        // write code here
        stack<double> values; // 数字
        stack<char> ops; // 符号
        int n = expr.length();
        for(int i = 0 ; i < n ; i++){
            if(isspace(expr[i])) continue;

            if(isdigit(expr[i]) || expr[i] == '.'){
                double value = 0;
                int decimalPointCount = 0;// 小数点个数
                bool isFraction = false; // 是否是小数
                // 提取数字
                while (i < n && (isdigit(expr[i]) || expr[i] == '.')){
                    // 小数点
                    if(expr[i] == '.'){
                        isFraction = true;
                        decimalPointCount = 1;                    
                    } 
                    // 小数
                    else if (isFraction) {
                        value += (expr[i] - '0') / pow(10, decimalPointCount);
                        decimalPointCount++;
                    }
                    // 整数 
                    else {
                        value = value * 10 + (expr[i] - '0');
                    }
                    i++;// 下一个字符
                }
                i--;// 回退一个字符
                values.push(value);// 入栈
            }

            // 左括号
            else if(expr[i] == '('){
                ops.push(expr[i]);
            } 
            // 右括号
            else if(expr[i] == ')'){
                // 计算括号内的表达式
                while(!ops.empty() && ops.top() != '('){
                    double b = values.top();
                    values.pop();
                    double a = values.top();
                    values.pop();
                    char op = ops.top();
                    ops.pop();
                    switch (op) {
                        case '+':
                            values.push(a + b);
                            break;
                        case '-':
                            values.push(a - b);
                            break;
                        case '*':
                            values.push(a * b);
                            break;
                        case '/':
                            values.push(a / b);
                            break;
                    }
                }
                // 弹出左括号
                if(!ops.empty()){
                    ops.pop();
                }
            }
            // 运算符
            else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'){
                while (!ops.empty() &&
                       (ops.top() == '*' || ops.top() == '/' || (ops.top() == '+' || ops.top() == '-') && 
                       (expr[i] == '+' || expr[i] == '-'))) {
                    double b = values.top();
                    values.pop();
                    double a = values.top();
                    values.pop();
                    char op = ops.top();
                    ops.pop();
                    switch (op) {
                        case '+':
                            values.push(a + b);
                            break;
                        case '-':
                            values.push(a - b);
                            break;
                        case '*':
                            values.push(a * b);
                            break;
                        case '/':
                            values.push(a / b);
                            break;
                    }
                }
                ops.push(expr[i]);
            }
        }
        // 剩下的
        while (!ops.empty()) {
            double b = values.top();
            values.pop();
            double a = values.top();
            values.pop();
            char op = ops.top();
            ops.pop();
            switch (op) {
                case '+':
                    values.push(a + b);
                    break;
                case '-':
                    values.push(a - b);
                    break;
                case '*':
                    values.push(a * b);
                    break;
                case '/':
                    values.push(a / b);
                    break;
            }        
        }

        return values.top();
    }
};