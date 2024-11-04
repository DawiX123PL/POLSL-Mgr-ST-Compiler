


PROGRAM main

    // wlaczenie wyjsc cyfrowych przy stanie wysokim na wejsciu
    %Q1.1.0 := %I0.0.1;
    %Q1.1.1 := %I0.0.1;
    %Q1.1.2 := %I0.0.1;
    %Q1.1.3 := %I0.0.1;
    %Q1.1.4 := %I0.0.1;
    %Q1.1.5 := %I0.0.1;
    %Q1.1.6 := %I0.0.1;
    %Q1.1.7 := %I0.0.1;

    // zmiana stanu wyjsc w zaleznosci od napiecia na wejsciu
    %Q1.0.0 := WORD_TO_REAL(%IW0.2) > 100.0;
    %Q1.0.1 := WORD_TO_REAL(%IW0.2) > 200.0;
    %Q1.0.2 := WORD_TO_REAL(%IW0.2) > 300.0;
    %Q1.0.3 := WORD_TO_REAL(%IW0.2) > 400.0;
    %Q1.0.4 := WORD_TO_REAL(%IW0.2) > 500.0;
    %Q1.0.5 := WORD_TO_REAL(%IW0.2) > 600.0;
    %Q1.0.6 := WORD_TO_REAL(%IW0.2) > 700.0;
    %Q1.0.7 := WORD_TO_REAL(%IW0.2) > 800.0;


END_PROGRAM


