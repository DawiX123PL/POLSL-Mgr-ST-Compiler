

// find minimum of function
// y = x1 ^2 - 6 *x1 ^2.*x2 - 20 *x1 + 3 *x2 ^2 + 3 *x1 ^4 + 109

FUNCTION OptimizedFunction: REAL
    VAR_INPUT
        x1: REAL;
        x2: REAL;
    END_VAR

    OptimizedFunction := x1 ** REAL#2.0 - REAL#6.0 * x1 ** REAL#2.0 * x2 - REAL#20.0 * x1 + REAL#3.0 * x2 ** REAL#2.0 + REAL#3.0 * x1 ** REAL#4.0 + REAL#109.0;

END_FUNCTION


FUNCTION GradientSearchMin: REAL
    VAR_INPUT
        x01: REAL;
        x02: REAL;
        iter: INT;
    END_VAR

    VAR
        x1: REAL;
        x2: REAL;
        delta: REAL := REAL#0.001;
        alpha: REAL := REAL#1.0;
        y: REAL;
        y1: REAL;
        y2: REAL;
        dy_dx1: REAL;
        dy_dx2: REAL;
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
        minimum: REAL; (* Comment *)
    END_VAR

    minimum := GradientSearchMin(REAL#100.0, REAL#100.0, 1000);

END_PROGRAM
