#include <stack>
#include <iostream>

using namespace std;

int main(){
    stack<int> stack;
    /* 元素入栈 */
    stack.push(1);
    stack.push(3);
    stack.push(2);
    stack.push(5);
    stack.push(4);

    /* 访问栈顶元素 */
    int top = stack.top();
    cout << "栈顶元素 top = " << top << endl;

    /* 元素出栈 */
    stack.pop(); // 无返回值
    cout << "出栈元素 pop = " << top << endl;

    /* 获取栈的长度 */
    int size = stack.size();
    cout << "栈的长度 size = " << size << endl;

    /* 判断是否为空 */
    bool empty = stack.empty();
    cout << "栈是否为空 = " << empty << endl;

    return 0;
}