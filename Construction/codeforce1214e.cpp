#include <bits/stdc++.h>
#define MAX_SIZE 200011
using namespace std;
int n;
// di, id
vector<pair<int, int>> vertex;

int main() {
    int i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        int d;
        scanf("%d", &d);
        vertex.emplace_back(d, i * 2 + 1);
    }

    sort(vertex.begin(), vertex.end(), greater<pair<int, int>>());

    for (i = 1; i < (int) vertex.size(); ++i) {
        printf("%d %d\n", vertex[i-1].second, vertex[i].second);
    } 

    n = (int) vertex.size();
    for (i = 0 ; i < n; ++i) {
        printf("%d %d\n", vertex[i].second + 1, vertex[i + vertex[i].first - 1].second);
        if (i + vertex[i].first == (int) vertex.size()) {
            vertex.emplace_back(0, vertex[i].second + 1);
        }
    }
    return 0;
}