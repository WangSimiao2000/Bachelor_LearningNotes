#include <iostream>
#include <vector>

using namespace std;

int n, m, q;
vector<vector<int>> matrix;
vector<int> row_offset;

void doFunc1(int x, int y) {
  x--;
  y--;
  swap(matrix[x], matrix[y]);
}

void doFunc2(int x, int y) {
  x--;
  y = y % m;
  row_offset[x] = (row_offset[x] + m - y) % m;
}

void doFunc3(int x, int y) {
  x--;
  y--;
  int actual_col = (y + m - row_offset[x]) % m;
  cout << matrix[x][actual_col] << endl;
}

int main() {
  cin >> n >> m >> q;
  matrix.resize(n, vector<int>(m));
  row_offset.resize(n, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      matrix[i][j] = i * m + j + 1;
    }
  }
  for (int i = 0; i < q; i++) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1) {
      doFunc1(x, y);
    } else if (t == 2) {
      doFunc2(x, y);
    } else if (t == 3) {
      doFunc3(x, y);
    }
  }
  return 0;
}