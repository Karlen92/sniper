
int foo(int x) {
    
    int y = 0;
    if (x==0) {
        y = x - 42;  // BUG
    } else {
        // 42 times y++
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
        y = y + 1;
        y = y + 1;
    }
    assert(y==42);
    return 0;
}