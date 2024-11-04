

FUNCTION AddNumbers : INT
    VAR_INPUT
        a : INT;
        b : INT;
    END_VAR
    AddNumbers := a + b;
END_FUNCTION

FUNCTION AddAndModify : INT
VAR_INPUT
    a : INT;
    b : INT;
END_VAR
VAR_OUTPUT
    sum : INT;
END_VAR
VAR_IN_OUT
    modifier : INT;
END_VAR

sum := a + b;
modifier := modifier + 1;  // Modyfikacja zmiennej IN_OUT
AddAndModify := sum + modifier;
END_FUNCTION

FUNCTION ModifyAndOutput : INT
VAR_OUTPUT
    result : INT;
END_VAR
VAR_IN_OUT
    value : INT;
END_VAR

value := 10;
result := 10;
ModifyAndOutput := 10;
END_FUNCTION

PROGRAM main
    VAR
        Variable: BOOL; (* Comment *)
    END_VAR
    // Variable := NOT Variable;
    // Variable := %M0.0;

    %MX0.0 := %QX0.0.0;
END_PROGRAM
