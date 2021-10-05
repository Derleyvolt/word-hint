#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define min(a, b) (a > b ? b : a)

// remover
// substituir
// inserir
int dp[50][50];

int edit_distance(char *a, char *b, int len_a, int len_b, int idx_a, int idx_b) {
    if(idx_a >= len_a) {
        return len_b-idx_b;
    }

    if(idx_b >= len_b) {
        return len_a-idx_a;
    }
    
    if(dp[idx_a][idx_b] != -1) {
        return dp[idx_a][idx_b];
    }

    if(a[idx_a] == b[idx_b]) {
        return dp[idx_a][idx_b] = edit_distance(a, b, len_a, len_b, idx_a+1, idx_b+1);
    }

    // deletar
    int ax = edit_distance(a, b, len_a, len_b, idx_a+1, idx_b)   + 1;
    // substituir
    int bx = edit_distance(a, b, len_a, len_b, idx_a+1, idx_b+1) + 1;
    // inserir
    int cx = edit_distance(a, b, len_a, len_b, idx_a, idx_b+1)   + 1;

    return dp[idx_a][idx_b] = min(ax, min(bx, cx));
}