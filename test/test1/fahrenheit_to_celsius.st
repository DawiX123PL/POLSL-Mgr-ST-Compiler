


FUNCTION fahrenheit_to_celsius : LREAL

VAR_INPUT
    f: LREAL;
END_VAR

fahrenheit_to_celsius := (f - LREAL#32.0) / LREAL#1.8;

END_FUNCTION


PROGRAM main
    
    VAR
        v1: BOOL := TRUE;
        v2: LREAL := LREAL#1.1;
        v3: REAL := LREAL#2137.0;
        v4: INT;
        v5: BOOL;
    END_VAR


    // v1 := v2 <> v3;
    // v5 := %MX2.4;

    // %MX0.2 := LREAL_TO_REAL(v2) > v3;

    %Q1.1.0 := TRUE;
    %Q1.1.1 := TRUE;
    %Q1.1.2 := TRUE;
    %Q1.1.3 := TRUE;
    %Q1.1.4 := TRUE;
    %Q1.1.5 := TRUE;
    %Q1.1.6 := TRUE;
    %Q1.1.7 := TRUE;

    %Q1.0.0 := WORD_TO_REAL(%IW0.2) > 0.0;
    %Q1.0.1 := WORD_TO_REAL(%IW0.2) > 100.0;
    %Q1.0.2 := WORD_TO_REAL(%IW0.2) > 200.0;
    %Q1.0.3 := WORD_TO_REAL(%IW0.2) > 300.0;
    %Q1.0.4 := WORD_TO_REAL(%IW0.2) > 400.0;
    %Q1.0.5 := WORD_TO_REAL(%IW0.2) > 500.0;
    %Q1.0.6 := WORD_TO_REAL(%IW0.2) > 600.0;
    %Q1.0.7 := WORD_TO_REAL(%IW0.2) > 700.0;

    // %I1.0.1;

END_PROGRAM


