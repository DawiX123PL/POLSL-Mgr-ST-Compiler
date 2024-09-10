

// find minimum of function
// y = x1 ^2 - 6 *x1 ^2.*x2 - 20 *x1 + 3 *x2 ^2 + 3 *x1 ^4 + 109

FUNCTION OptimizedFunction: LREAL
    VAR_INPUT
        x1: LREAL;
        x2: LREAL;
    END_VAR

    OptimizedFunction := x1 ** LREAL#2.0 - LREAL#6.0 * x1 ** LREAL#2.0 * x2 - LREAL#20.0 * x1 + LREAL#3.0 * x2 ** LREAL#2.0 + LREAL#3.0 * x1 ** LREAL#4.0 + LREAL#109.0;

END_FUNCTION


FUNCTION GradientSearchMin: LREAL
    VAR_INPUT
        x01: LREAL;
        x02: LREAL;
        iter: INT;
    END_VAR

    VAR
        x1: LREAL;
        x2: LREAL;
        delta: LREAL := LREAL#0.001;
        alpha: LREAL := LREAL#1.0;
        y: LREAL;
        y1: LREAL;
        y2: LREAL;
        dy_dx1: LREAL;
        dy_dx2: LREAL;
    END_VAR

    x1 := x01;
    x2 := x02;

    WHILE iter >= 0 DO
        iter := iter - 1;

        // calculate gradient
        y := OptimizedFunction(x1, x2);
        y1 := OptimizedFunction(x1 + delta, x2);
        y2 := OptimizedFunction(x1, x2 + delta);

        dy_dx1 := (y1 - y) / delta;
        dy_dx2 := (y2 - y) / delta;

        x1 := x1 - alpha * dy_dx1;
        x2 := x2 - alpha * dy_dx2;

    END_WHILE;

    GradientSearchMin := OptimizedFunction(x1, x2);

END_FUNCTION

PROGRAM main
    VAR
        minimum: LREAL; (* Comment *)
    END_VAR

    minimum := GradientSearchMin(100, 100, 0.1);

END_PROGRAM
