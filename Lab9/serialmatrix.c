#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    int A[n][n];
    int B[n][n];
    int C[n][n];
    srand(time(0));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            A[i][j] = (rand() % 5) + 1;
            B[i][j] = (rand() % 5) + 1;
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            C[i][j] = 0;
            for(int k = 0; k < n; k++){
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%d ",C[i][j]);
        }
        printf("\n");
    }

    return 0;
}