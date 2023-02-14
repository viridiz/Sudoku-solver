#include<iostream>
#include<tuple>

using namespace std;

tuple<int, int> next_cell_to_process(int arr[9][9]) {
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (arr[i][j] == 0)
                return make_tuple(i, j);
    return make_tuple(-1, -1);
}

bool is_valid(int arr[9][9], int i, int j, int e) {
    for (int x = 0; x < 9; ++x)
        if (arr[i][x] == e)
            return false;
    for (int x = 0; x < 9; ++x)
        if (arr[x][j] == e)
            return false;
    int top_x = 3 * (i / 3);
    int top_y = 3 * (j / 3);
    for (int x = top_x; x < top_x + 3; ++x)
        for (int y = top_y; y < top_y + 3; ++y)
            if (arr[x][y] == e)
                return false;
    return true;
}

bool solve(int (&arr)[9][9], int i = 0, int j = 0) {
    i = get<0>(next_cell_to_process(arr));
    j = get<1>(next_cell_to_process(arr));
    if (i == -1)
        return true;
    for (int e = 1; e < 10; ++e)
        if (is_valid(arr, i, j, e)) {
            arr[i][j] = e;
            if (solve(arr, i, j))
                return true;
            arr[i][j] = 0;
        }
    return false;
}

int main() {
    int arr[9][9];
    for (auto &i: arr) {
        string s;
        cin >> s;
        for (int j = 0; j < 9; ++j)
            i[j] = (int) s[j] - 48;
    }
    solve(arr);
    for (auto &i: arr)
        for (int j = 0; j < 9; ++j)
            cout << i[j] << " \n"[j == 8];
    return 0;
}