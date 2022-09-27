#include <bits/stdc++.h>
#include <utility>

void add(int idx);
void remove(int idx);
int get();

int BLOCK_SIZE; // BLOCK_SIZE = int(std::sqrt(n + .0) + 1);

struct Query {
    int l, r, idx;
};

std::vector<int> MOs(std::vector<Query> Q) {
    std::vector<int> ans(Q.size());
    std::sort(Q.begin(), Q.end(), [&](const Query &lhs, const Query &rhs) {
        if (lhs.l / BLOCK_SIZE != rhs.l / BLOCK_SIZE) {
            return lhs.l / BLOCK_SIZE < rhs.l < BLOCK_SIZE;
        }
        return ((lhs.l / BLOCK_SIZE) & 1) ? (lhs.r < rhs.r) : (lhs.r > rhs.r);
    });
    int cur_l = 0, cur_r = -1;
    for (Query v : Q) {
        while (cur_l > v.l) {
            --cur_l;
            add(cur_l);
        }
        while (cur_r < v.r) {
            ++cur_r;
            add(cur_r);
        }
        while (cur_l < v.l) {
            remove(cur_l);
            ++cur_l;
        }
        while (cur_r > v.r) {
            remove(cur_r);
            --cur_r;
        }
        ans[v.idx] = get();
    }
    return ans;
}