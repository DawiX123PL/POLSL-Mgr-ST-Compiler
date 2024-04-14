





int func1(int a, int b, int *c, int* d) {
    int c1 = *c;
    int d1 = *d;
    
    *c = a + b;
    return a;
}

