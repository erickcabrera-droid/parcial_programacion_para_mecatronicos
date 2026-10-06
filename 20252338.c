#include <stdio.h>

int main(void)
{
    int N, M, L, U;
    int mat[30][30];
    long sumaCol[30];
    int cantCol[30];
    int eventos[30];
    long impacto[30];
    int racha[30];
    int inicio[30];
    int i, j;

    if (scanf("%d %d %d %d", &N, &M, &L, &U) != 4) {
        printf("ERROR\n");
        return 0;
    }
    if (N < 1 || N > 30 || M < 1 || M > 30 ||
        L < 0 || U > 1000 || L > U) {
        printf("ERROR\n");
        return 0;
    }

    for (j = 0; j < M; j++) {
        sumaCol[j] = 0;
        cantCol[j] = 0;
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            if (scanf("%d", &mat[i][j]) != 1 ||
                mat[i][j] < 0 || mat[i][j] > 1000) {
                printf("ERROR\n");
                return 0;
            }
            sumaCol[j] += mat[i][j];
        }
    }

    for (i = 0; i < N; i++) {
        int rachaActual = 0, inicioActual = 0;
        eventos[i] = 0;
        impacto[i] = 0;
        racha[i] = 0;
        inicio[i] = 0;
        for (j = 0; j < M; j++) {
            long x = mat[i][j];
            if ((long)N * x - sumaCol[j] >= (long)N * L && x >= U) {
                eventos[i]++;
                impacto[i] += (long)N * x - sumaCol[j] + 1;
                cantCol[j]++;
                if (rachaActual == 0)
                    inicioActual = j + 1;
                rachaActual++;
                if (rachaActual > racha[i]) {
                    racha[i] = rachaActual;
                    inicio[i] = inicioActual;
                }
            } else {
                rachaActual = 0;
            }
        }
    }

    int filaP = 0;
    int hayEventos = 0;
    for (i = 0; i < N; i++) {
        if (eventos[i] > 0)
            hayEventos = 1;
    }
    if (hayEventos) {
        filaP = 1;
        for (i = 1; i < N; i++) {
            int mejor = filaP - 1;
            if (racha[i] > racha[mejor] ||
                (racha[i] == racha[mejor] && impacto[i] > impacto[mejor]) ||
                (racha[i] == racha[mejor] && impacto[i] == impacto[mejor] &&
                 eventos[i] > eventos[mejor]))
                filaP = i + 1;
        }
    }

    int colD = 0;
    if (hayEventos) {
        colD = 1;
        for (j = 1; j < M; j++) {
            if (cantCol[j] > cantCol[colD - 1])
                colD = j + 1;
        }
    }

    for (i = 0; i < N; i++) {
        printf("FILA %d EVENTOS %d IMPACTO %ld RACHA %d INICIO %d\n",
               i + 1, eventos[i], impacto[i], racha[i], inicio[i]);
    }
    printf("COLUMNAS");
    for (j = 0; j < M; j++)
        printf(" %d", cantCol[j]);
    printf("\n");
    printf("PRIORIDAD %d\n", filaP);
    printf("COLUMNA %d\n", colD);
    return 0;
}