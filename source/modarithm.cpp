inline void add(int& a, int x) {
    a += x;
    if (a >= MD) a -= MD;
}

inline void sub(int& a, int x) {
    a -= x;
    if (a < 0) a += MD;
}

inline int mult(int a, int b) {
    ll res = a * 1LL * b;
    if (res >= MD) {
        res %= MD;
    }
    return res;
}
