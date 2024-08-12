


FUNCTION fahrenheit_to_celsius : REAL

VAR_INPUT
    f: REAL;
END_VAR

fahrenheit_to_celsius := (f - REAL#32.0) / REAL#1.8;

END_FUNCTION


PROGRAM main
    
    VAR
        v1: BOOL := TRUE;
        v2: REAL;
        v3: REAL;
        v4: INT;
    END_VAR

    v1 := v2 <> v3;

END_PROGRAM

