#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, q;
    void *a;
    int size = 0;

    scanf("%d %d", &n, &q);

    a = malloc(sizeof(int *) * n);

    for(int i = 0; i < n; i++) {
        int *k;
        scanf("%d", &size);
        k = (int *) malloc(sizeof(int) * (size + 1));
        k[0] = size;
        for(int j = 1; j <= size; j++) {
            scanf("%d", &k[j]);
        }
        ((int **)a)[i] = k;
    }

    for(int i = 0; i < n; i++) {
        int x,y;
        scanf("%d %d", &x, &y);
        printf("%d\n", ((int **)a)[x][y+1]);
    }

    for(int i = 0; i < n; i++) {
        free(((int **)a)[i]);
    }
    
    free(a);

    return 0;
}
