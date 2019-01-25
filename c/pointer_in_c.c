#include <stdio.h>
#include <stdlib.h>

void update(int *a, int *b);

int main()
{
    int a, b;
    
    scanf("%d %d",&a, &b);
    update(&a, &b);
    printf("%d\n%d", a, b);
    return 0;
}

void update(int *a, int *b)
{
    int localA, localB;
    localA = *a + *b;
    localB = *a - *b;
    *a = localA;
    *b = abs(localB);
}
