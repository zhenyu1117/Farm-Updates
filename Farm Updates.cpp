#include <cstdio>

int N, Q, M;
int ax[200020], ay[200020];
int t[200020], x[200020];
int inactive_farm[200020], inactive_road[200020];
int fa[100010], ans[100010];

int find(int x) {
    if (fa[x] != x) {
        fa[x] = find(fa[x]);
    }
    return fa[x];
}

int main() {
    scanf("%d %d\n", &N, &Q);
    M = 0;
    for (int i = 1; i <= Q; i++) {
        char c;
        scanf("%c ", &c);
        if (c == 'D') {
            t[i] = 1;
            scanf("%d\n", x+i);
            inactive_farm[x[i]] = 1;
        }
        if (c == 'A') {
            t[i] = 2;
            M++;
            scanf("%d %d\n", ax+M, ay+M);
            x[i] = M;
        }
        if (c == 'R') {
            t[i] = 3;
            scanf("%d\n", x+i);
            inactive_road[x[i]] = 1;
        }
    }

    for (int i = 1; i <= N; i++) {
        fa[i] = i;
    }

    for (int i = 1; i <= M; i++) {
        if (inactive_road[i] == 0) {
            int fx = find(ax[i]);
            int fy = find(ay[i]);
            if (inactive_farm[fx] == 0) {
                fa[fy] = fx;
            } else {
                fa[fx] = fy;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        if (inactive_farm[i] == 0) {
            ans[i] = Q;
        }
    }

    for (int i = Q; i >= 1; i--) {
        if (t[i] == 1) {
            int fx = find(x[i]);
            if (inactive_farm[fx] == 1) {
                inactive_farm[fx] = 0;
                ans[fx] = i-1;
            }
        }
        if (t[i] == 3) {
            int fx = find(ax[x[i]]);
            int fy = find(ay[x[i]]);
            if ((inactive_farm[fx] == 1) && (inactive_farm[fy] == 1)) {
                fa[fy] = fx;
            } else if ((inactive_farm[fx] == 1) && (inactive_farm[fy] == 0)) {
                inactive_farm[fx] = 0;
                ans[fx] = i-1;
            } else if ((inactive_farm[fx] == 0) && (inactive_farm[fy] == 1)) {
                inactive_farm[fy] = 0;
                ans[fy] = i-1;
            }
        }
    }

    for (int i = 1; i <= N; i++) {
        if (ans[i] == 0) {
            ans[i] = ans[find(i)];
        }
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
