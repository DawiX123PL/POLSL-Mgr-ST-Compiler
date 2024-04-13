
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

RETURN ;

END_FUNCTION
```

```c
struct test_func_io
{
    // VAR_INPUT, (caller: write only; callee: read only) 
    INT aaa;
    INT b;
    INT c1;
    // VAR_OUTPUT (caller: read only; callee: read-write)
    INT x;
    // VAR_IN_OUT (caller: read-write; callee: read-write)
    BOOL b1;
    // return value (caller: read only; callee: read-write)
    BOOL test_func := 0;
};

void test_func_fn(GTT gtt, test_func_io* io)
{
    // VAR_INPUT, 

    // VAR_OUTPUT
    INT x    = 123;
    // VAR_IN_OUT
    BOOL b1  = *io.b1;
    // VAR
    INT c    = 1001;
    // VAR_RETURN
    BOOL test_func = 0;
    // Body
    test_func := 0.123;
    io.x := - io.a + io.b + io.c;
}
```

