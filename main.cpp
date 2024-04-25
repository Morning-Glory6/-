#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <stack>
#include <queue>
#include <cassert>
using namespace std;
pair<int, int> f[60][60];
int mp[60][60];
int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };
pair<int, int> find(pair<int, int> u) 
{
    return f[u.first][u.second] = f[u.first][u.second] == u ? u : find(f[u.first][u.second]);
}
int flag[60][60], ans[60][60];
void dfs_solve(int N, int M, int s, int t) {
    stack<pair<int, int>> stk;
    memset(flag, 0, sizeof(flag));
    flag[1][s] = 1;
    stk.push(make_pair(1, s));
    while (true) {
        pair<int, int> top = stk.top();
        int fd = 0, x = top.first, y = top.second;
        if (x == N && y == t) {
            for (int i = 0; i <= N + 1; i++) {
                for (int j = 0; j <= M + 1; j++) {
                    ans[i][j] = mp[i][j];
                }
            }
            while (stk.size()) {
                pair<int, int> top = stk.top();
                stk.pop();
                ans[top.first][top.second] = 2;
            }
            for (int i = 0; i <= N + 1; i++) {
                for (int j = 0; j <= M + 1; j++) {
                    if (i == 0) {
                        cout << "#O"[j == s];
                    }
                    else if (i == N + 1) {
                        cout << "#O"[j == t];
                    }
                    else if (!ans[i][j]) {
                        cout << '#';
                    }
                    else {
                        cout << " O"[ans[i][j] == 2];
                    }
                }
                cout << endl;
            }
            return;
        }
        for (int i = 0; i <= 3 && !fd; i++) {
            if (x + dx[i] >= 1 && x + dx[i] <= N && y + dy[i] >= 1 && y + dy[i] <= M && !flag[x + dx[i]][y + dy[i]] && mp[x + dx[i]][y + dy[i]]) {
                fd = 1;
                flag[x + dx[i]][y + dy[i]] = 1;
                stk.push(make_pair(x + dx[i], y + dy[i]));
            }
        }
        if (fd) continue;
        stk.pop();
    }
}
void bfs_solve(int N, int M, int s, int t) {
    queue<pair<int, int>> q;
    q.push(make_pair(1, s));
    memset(flag, 0, sizeof(flag));
    flag[1][s] = 1;
    while (true) {
        pair<int, int> top = q.front();
        int x = top.first, y = top.second;
        q.pop();
        for (int i = 0; i <= 3; i++) {
            if (x + dx[i] >= 1 && x + dx[i] <= N && y + dy[i] >= 1 && y + dy[i] <= M && !flag[x + dx[i]][y + dy[i]] && mp[x + dx[i]][y + dy[i]]) {
                flag[x + dx[i]][y + dy[i]] = flag[x][y] + 1;
                q.push(make_pair(x + dx[i], y + dy[i]));
                if (x + dx[i] == N && y + dy[i] == t) {
                    for (int i = 0; i <= N + 1; i++) {
                        for (int j = 0; j <= M + 1; j++) {
                            ans[i][j] = mp[i][j];
                        }
                    }
                    x = N, y = t;
                    ans[x][y] = 2;
                    while (x != 1 || y != s) {
                        for (int i = 0; i <= 3; i++) {
                            if (x + dx[i] >= 1 && x + dx[i] <= N && y + dy[i] >= 1 && y + dy[i] <= M && flag[x][y] == flag[x + dx[i]][y + dy[i]] + 1) {
                                x += dx[i];
                                y += dy[i];
                                ans[x][y] = 2;
                                break;
                            }
                        }
                    }
                    for (int i = 0; i <= N + 1; i++) {
                        for (int j = 0; j <= M + 1; j++) {
                            if (i == 0) {
                                cout << "#O"[j == s];
                            }
                            else if (i == N + 1) {
                                cout << "#O"[j == t];
                            }
                            else if (!ans[i][j]) {
                                cout << '#';
                            }
                            else {
                                cout << " O"[ans[i][j] == 2];
                            }
                        }
                        cout << endl;
                    }
                    return;
                }
            }
        }
    }
}

int main() {
    srand((unsigned)time(NULL));
    int N, M;
    cout << "������N(5~50):";
    cin >> N;
    if (cin.fail()) {
        cin.clear();  // ��������־
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ������뻺����
        N = 50;
    }
    else if (N < 5 || N > 50) {
        N = 50;
    }
    cout << "������M(5~50):";
    cin >> M;
    if (cin.fail()) {
        cin.clear();  // ��������־
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ������뻺����
        M = 50;
    }
    else if (M < 5 || M > 50) {
        M = 50;
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            f[i][j] = make_pair(i, j);
        }
    }
    int s = rand() % N + 1, t = rand() % M + 1;  // ���,�յ�
    memset(mp, 0, sizeof(mp));
    mp[1][s] = mp[N][t] = -1;
    while (find(make_pair(1, s)) != find(make_pair(N, t))) {
        int x = rand() % N + 1, y = rand() % M + 1;
        if (mp[x][y]) continue;
        mp[x][y] = 1;
        for (int i = 0; i <= 3; i++) {
            if (x + dx[i] >= 1 && x + dx[i] <= N && y + dy[i] >= 1 && y + dy[i] <= M && mp[x + dx[i]][y + dy[i]]) {
                pair<int, int> fu = find(make_pair(x, y)), fv = find(make_pair(x + dx[i], y + dy[i]));
                f[fu.first][fu.second] = fv;
            }
        }
    }
    for (int i = 0; i <= N + 1; i++) {
        for (int j = 0; j <= M + 1; j++) {
            if (i == 0) {
                cout << "# "[mp[i + 1][j] == -1];
            }
            else if (i == N + 1) {
                cout << "# "[mp[i - 1][j] == -1];
            }
            else if (!mp[i][j]) {
                cout << '#';
            }
            else {
                cout << ' ';
            }
        }
        cout << endl;
    }
    while (1) {
        cout << endl;
        cout << "1.DFS����Թ�" << endl;
        cout << "2.BFS����Թ�" << endl;
        cout << "0.�˳�" << endl;
        cout << "��ѡ��:";
        int cases;
        while (1) {
            cin >> cases;
            if (cin.fail()) {
                cin.clear();  // ��������־
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ������뻺����
                cout << "������Ч������������:";
            }
            else if (cases < 0 || cases > 2) {
                cout << "���볬����Χ������������:";
            }
            else {
                break;
            }
        }
        if (!cases) break;
        else if (cases == 1) dfs_solve(N, M, s, t);
        else bfs_solve(N, M, s, t);
    }
    return 0;
}
