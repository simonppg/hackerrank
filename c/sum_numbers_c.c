#include <stdio.h>

int main()
{
    int aInt, bInt;
    float aFloat, bFloat;

    scanf("%d%d", &aInt, &bInt);
    scanf("%f%f", &aFloat, &bFloat);

    printf("%d %d\n", aInt + bInt, aInt - bInt);
    printf("%.1f %.1f", aFloat + bFloat, aFloat - bFloat);
    return 0;
}
