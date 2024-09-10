
PROGRAM main
    VAR
        counter: LINT;
    END_VAR

    counter := LINT#10_000;

    WHILE counter >= LINT#0 DO
        counter := counter - LINT#1;
    END_WHILE;
END_PROGRAM
