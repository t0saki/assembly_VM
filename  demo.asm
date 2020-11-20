INT N
IN N
INT FL
LD FL 2
INT I
INT J
INT RNGI
INT RNGJ
MOV RNGI N
INT TMP
LD TMP 0
ADD RNGI TMP
LD TMP 1
DIV RNGI TMP
INT TMP1
INT TMP2

MV I RNGI
istart:
    LD J 1
    jstart:
        MOV TMP I
        MUL TMP J
        MOV TMP2 N
        SUB TMP2 TMP
        SUB TMP N
        AND TMP TMP2
        NOT TMP TMP
        JC TMP ifend
            LD FL 0
            JMP endf
        ifend:
    forjend:
    LD TMP 0
    ADD J TMP
    MOV TMP I
    SUB TMP J
    JC TMP jstart
LD TMP 0
SUB I TMP
MOV TMP1 I
SUB TMP1 TMP
JC TMP1 istart
endf:
OUT I


/**INT A
IN A
INT B
IN B
ADD A,B
OUT A
MUL A,B
OUT A


INT A
INT B
INT C
IN C
IN B
IN A
MUX B,C
OUT C

INT A
IN A
INT B
IN B
test:ADD A,B
OUT A
JC B test

ram:
0 1
1 2
2 0

