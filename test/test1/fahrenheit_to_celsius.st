


FUNCTION fahrenheit_to_celsius : LREAL

VAR_INPUT
    f: LREAL;
END_VAR

fahrenheit_to_celsius := (f - LREAL#32.0) / LREAL#1.8;

END_FUNCTION


PROGRAM main
    
    VAR
        v1: BOOL := TRUE;
        v2: LREAL;
        v3: LREAL;
        v4: INT;
    END_VAR

    v1 := v2 <> v3;

END_PROGRAM

