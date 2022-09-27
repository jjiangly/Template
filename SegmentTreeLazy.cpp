template<typename T>
struct SegmentTreeLazy {
    const int n;
    std::vector<T> a, add, set;
    SegmentTreeLazy(int n) : n(n), a(4 * n), add(4 * n, 0), set(4 * n, -1) {}
    SegmentTreeLazy(std::vector<T> init) : SegmentTreeLazy(init.size()) {
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
    void app(int p, int l, int r) {
        int m = (l + r) / 2;
        if (set[p] != -1) {
            set[2 * p] = set[2 * p + 1] = set[p];
            a[2 * p] = a[2 * p + 1] = set[p];
            add[2 * p] = add[2 * p + 1] = 0;
            set[p] = -1;
        } else if (add[p]) {
            if (set[2 * p] == -1) {
                add[2 * p] += add[p];
            } else {
                set[2 * p] += add[p];
                add[2 * p] = 0;
            }
            if (set[2 * p + 1] == -1) {
                add[2 * p + 1] += add[p];
            } else {
                set[2 * p + 1] += add[p];
                add[2 * p + 1] = 0;
            }
            a[2 * p] += add[p];
            a[2 * p + 1] += add[p];
            add[p] = 0;
        }
    }
    void update(int p, int l, int r, int x, int y, T v, bool f) {
        if (l >= y || r <= x) {
            return;
        }
        if (x <= l && r <= y) {
            if (f) {
                a[p] = v;
                set[p] = v;
                add[p] = 0;
            } else {
                a[p] += v;
                if (set[p] == -1) {
                    add[p] += v;
                } else {
                    set[p] += v;
                }
            }
            return;
        }
        app(p, l, r);
        int m = (l + r) / 2;
        update(2 * p, l, m, x, y, v);
        update(2 * p + 1, m, r, x, y, v);
        pull(p, l, r);
    }
    void update(int l, int r, T v) {
        update(1, 0, n, l, r, v);
    }
    T rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return 0;
        }
        if (x <= l && r <= y) {
            return a[p];
        }
        app(p, l, r);
        int m = (l + r) / 2;
        return std::max(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    T rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
};