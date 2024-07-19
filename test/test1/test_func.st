


FUNCTION test_func:BOOL
VAR_INPUT
    aaa: INT;
    b: INT;
    c1: INT := INT#1001;
END_VAR
VAR_IN_OUT
    b1: REAL;
END_VAR
VAR_OUTPUT
    x: INT;
END_VAR
VAR
    c: INT := INT#16#100;
END_VAR 
x:=-aaa+b*c1;
test_func := BOOL#1;
test_func := BOOL#1;
test_func := BOOL#1;
test_func := BOOL#1;
test_func := BOOL#1;
test_func := BOOL#1;
IF Condition THEN
    IF Condition THEN
        x:=-a1+b+c1;
    END_IF;
    x:=-a3+b+c1;
END_IF;

b1:=b1+REAL#0.1;
END_FUNCTION



