
# Internal structure of pou

## global memory
c lang
```c
struct GTT
{
    uint8_t I[I_size];
    uint8_t Q[Q_size];
    uint8_t M[M_size];
};
```

## Function

### Funkcja napisana w ST
```st
FUNCTION test_func : BOOL

VAR_INPUT
    aaa: INT;
    b: INT;
    c1: INT;
END_VAR
VAR_OUTPUT
    x: INT  := 123;
END_VAR
VAR_IN_OUT
    b1: BOOL;
END_VAR
VAR
    c: INT := 1001;
END_VAR

test_func := 0.123;
x := - a + b + c;

END_FUNCTION
```

### Odpowiednik w C (wariant 1)
```c
struct test_func_io
{
    // VAR_INPUT
    INT aaa;
    INT b;
    INT c1;
    // VAR_OUTPUT
    INT x;
    // VAR_IN_OUT
    BOOL b1;
    // return value
    BOOL test_func := 0;
};

void test_func_fn(test_func_io* io)
{
    // VAR - inicjalizacja zmiennych tymczasowych
    INT c = 1001;
    // VAR_RETURN - wartosc zwracania (inicjalizacja wartością domyślną 0)
    BOOL test_func = 0;
    // inicjalizacja outputów wartością domyślną 
    io.x = 0;

    // cialo funkcji 
    test_func := 0.123;
    io.x := - io.a + io.b + io.c;
}
```

### Odpowiednik w C (wariant 2)
```c

void test_func_fn(
    // VAR_INPUT
    INT aaa,
    INT b,
    INT c1,
    // VAR_OUTPUT
    INT* x,
    // VAR_IN_OUT
    BOOL* b1,
    // return value
    BOOL* test_func)
{
    // VAR
    INT c    = 1001;
    // VAR_RETURN
    BOOL test_func = 0;

    // Body
    test_func := 0.123;
    io.x := - io.a + io.b + io.c;
}
```
