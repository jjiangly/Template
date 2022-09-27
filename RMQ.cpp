template<typename T>
struct RMQ {
    const int n;
    std::vector<int> lg;
    std::vector<std::vector<T>> a;
    RMQ(const std::vector<T> &init) : n(init.size()), lg(n + 1) {
        lg[1] = 0;
        for (int i = 2; i <= n; ++i) {
            lg[i] = lg[i / 2] + 1;
        }
        a.assign(n, std::vector<T> (lg[n] + 1));
        for (int j = 0; j <= lg[n]; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                a[i][j] = (!j ? init[i] : std::max(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]));
            }
        }
    }
    T rangeQuery(int l, int r) {
        if (l >= r) {
            return 0;
        }
        int k = lg[r - l];
        return std::max(a[l][k], a[r - (1 << k)][k]);
    }
};