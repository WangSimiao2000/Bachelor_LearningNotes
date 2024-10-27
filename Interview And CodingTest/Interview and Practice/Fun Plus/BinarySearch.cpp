#include <vector>
using namespace std;

int prize(vector<int>& res, int target)
{
    int left  = 0;
    int right = res.size() - 1;

    while (left <= right)
    {
        int mid = left + (right - left) / 2; // 避免溢出
        if (res[mid] >= target)
        {
            right = mid - 1; // 尝试在左半边找更早的时间
        }
        else
        {
            left = mid + 1; // 在右半边继续查找
        }
    }

    // left指向第一个大于等于target的位置
    return (left < res.size() && res[left] >= target) ? left + 1 : -1; // 加1以返回1-based的时间
}

int main()
{
    vector<int> res    = {1, 2, 3, 4, 5};
    int         target = 3;
    int         ans    = prize(res, target);
    return 0;
}
