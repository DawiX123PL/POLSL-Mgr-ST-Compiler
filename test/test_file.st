//  FILE GENERATED WITH CHAT.GPT



(* 
  Multiline comment
  This program demonstrates various features of ST
*)

PROGRAM MainProgram
VAR
    (* Variable declaration *)
    iCounter : INT := 0; (* Single-line comment *)
    bFlag : BOOL := FALSE;
    fTemperature : REAL := 0.0;
    sMessage : STRING[50] := 'Hello, World!';
    arrNumbers : ARRAY [1..10] OF INT := [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
END_VAR

VAR CONSTANT
    pi : REAL := 3.14159; (* Constant declaration *)
END_VAR

VAR RETAIN
    retainedValue : INT := 0; (* Retained variable *)
END_VAR

VAR PERSISTENT
    persistentValue : INT := 100; (* Persistent variable *)
END_VAR

// Function block definition
FUNCTION_BLOCK FB_Counter
VAR_INPUT
    bEnable : BOOL;
    iIncrement : INT;
END_VAR
VAR_OUTPUT
    iCount : INT := 0;
END_VAR
VAR
    temp : INT;
END_VAR
    // Function block body
    IF bEnable THEN
        iCount := iCount + iIncrement;
    END_IF;
END_FUNCTION_BLOCK

// Function definition
FUNCTION Add
VAR_INPUT
    a : INT;
    b : INT;
END_VAR
VAR_OUTPUT
    result : INT;
END_VAR
    result := a + b;
END_FUNCTION

// Structured text program body
BEGIN
    // Conditional statement
    IF iCounter < 10 THEN
        iCounter := iCounter + 1;
    ELSE
        iCounter := 0;
    END_IF;

    // CASE statement
    CASE iCounter OF
        1: sMessage := 'Counter is 1';
        2: sMessage := 'Counter is 2';
        3: sMessage := 'Counter is 3';
        4..10: sMessage := 'Counter is between 4 and 10';
        ELSE sMessage := 'Counter is out of range';
    END_CASE;

    // FOR loop
    FOR i : INT := 1 TO 10 DO
        arrNumbers[i] := i * 2;
    END_FOR;

    // WHILE loop
    WHILE bFlag DO
        fTemperature := fTemperature + 1.0;
        IF fTemperature > 100.0 THEN
            bFlag := FALSE;
        END_IF;
    END_WHILE;

    // REPEAT loop
    REPEAT
        retainedValue := retainedValue + 1;
    UNTIL retainedValue > 10
    END_REPEAT;

    // Calling a function block
    fbCounter : FB_Counter;
    fbCounter(bEnable := TRUE, iIncrement := 1);
    persistentValue := fbCounter.iCount;

    // Calling a function
    persistentValue := Add(a := 5, b := 10);
END_PROGRAM

// Task configuration pragma
{attribute 'qualified_only'}
TASK MainTask(INTERVAL := T#20ms, PRIORITY := 1);
PROGRAM MainProgram;
END_TASK

// Nested comments example
(* Outer comment
    (* Nested comment *)
End of outer comment *)