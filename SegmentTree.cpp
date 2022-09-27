template<class T>
struct SegmentTree {
    const int n;
    std::vector<T> a;
    SegmentTree(int n) : n(n), a(4 * n) {}
    SegmentTree(std::vector<T> init) : SegmentTree(init.size()) {
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                a[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        a[p] = std::max(a[2 * p], a[2 * p + 1]);
    }
    void update(int p, int l, int r, int x, T v) {
        if (r - l == 1) {
            a[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            update(2 * p, l, m, x, v);
        } else {
            update(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void update(int x, T v) {
        update(1, 0, n, x, v);
    }
    T rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return 0;
        }
        if (x <= l && r <= y) {
            return a[p];
        }
        int m = (l + r) / 2;
        return std::max(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    T rangQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};