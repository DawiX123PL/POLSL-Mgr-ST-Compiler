
# Internal structure of pou

## global memory
c lang
```c
struct GTT
{
    uint8_t I[size];
    uint8_t Q[size];
    uint8_t M[size];
};
```

## Function

ST language 
```st
FUNCTION test_func : BOOL

VAR_INPUT
    aaa: INT;
    b: INT;
    c1: INT := 1001;
END_VAR
VAR_OUTPUT
    x: INT;
END_VAR
VAR_IN_OUT
    b1: BOOL;
END_VAR
VAR
    c: INT := 1001;
END_VAR
test_func := 0.123;
x := - a + b + c;

RETURN ;

END_FUNCTION
```
C equivalent
```c
struct test_func_io
{
    INT aaa;
    INT b;
    INT c1;
    INT x;
    BOOL b1;
    INT c;
}

void test_func_fn(GTT gtt, test_func_io* io)
{
    // VAR_INPUT, VAR_OUTPUT, VAR_IN_OUT
    INT aaa  = *io.a;
    INT b    = *io.b;
    INT c1   = *io.1;
    INT x    = *io.x;
    BOOL b1  = *io.1;
    INT c    = *io.c;

    // VAR
    INT c    = 1001;

    // Body

}
```

