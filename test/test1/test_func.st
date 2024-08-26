


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
    c: INT := INT#-100;
END_VAR 
// x:=-aaa+b*c1;
// test_func := BOOL#1;
// test_func := BOOL#1;
// test_func := BOOL#1;
// IF x>1 THEN
//     IF x>1 THEN
//         x:=-aaa+b+c1;
//     END_IF;
// END_IF;

WHILE (c + 1) > 1 DO
     x:=-aaa+b+c1;
END_WHILE;


// b1:=b1+REAL#0.1;
END_FUNCTION



