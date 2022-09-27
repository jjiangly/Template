struct DSU {
    int comp;
    std::vector<int> par, siz;
    DSU(int n) : comp(n), par(n), siz(n, 1) {
        std::iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        while (x != par[x]) {
            x = par[x] = par[par[x]];
        }
        return x;
    }
    bool join(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            return false;
        }
        --comp;
        par[y] = x;
        siz[x] += siz[y];
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return siz[find(x)];
    }
    int count() {
        return comp;
    }
};