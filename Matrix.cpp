struct Mat {
    using T = long long;
    int n, m;
    std::vector<std::vector<T>> a;
    Mat() {}
    Mat(int n, int m) : n(n), m(m), a(n, std::vector<T> (m, 0)) {}
    void init() {
        assert(n == m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = i == j;
            }
        }
    }
    Mat operator * (const Mat &other) const {
        assert(m == other.n);
        Mat ans = Mat(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int t = 0; t < m; ++t) {
                    ans.a[i][j] += a[i][t] * other.a[t][j];
                }
            }
        }
        return ans;
    }
    Mat operator *= (const Mat &other) {
        return *this = (*this) * other;
    }
};

Mat pow(Mat a, int b) {
    assert(a.n == a.m);
    Mat ans = Mat(a.n, a.m);
    ans.init();
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            ans *= a;
        }
    }
    return ans;
}