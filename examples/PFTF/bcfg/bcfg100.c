
#define N 100

extern void assert(int x);

int foo(int x) {
    
    int y = 0;
    if (x==0) {
        y = x - N;  // BUG
    } else {
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
        if (y<N) {
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
            y = y + 1;
        }
    }
    assert(y==N);
}