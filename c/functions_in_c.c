#include <stdio.h>

int max_of_four(int a, int b, int c, int d);

int main()
{
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    
    int res = max_of_four(a, b, c, d);
    printf("%d", res);
    return 0;
}

int max_of_four(int a, int b, int c, int d)
{
    int res;

    res = a;
    res = b > res ? b : res;
    res = c > res ? c : res;
    res = d > res ? d : res;

    return res;
}
