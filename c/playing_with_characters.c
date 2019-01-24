#include<stdio.h>

int main()
{
    char ch, s[10], sen[100];
    scanf("%c", &ch);
    scanf("%s", s);
    scanf("\n");
    scanf("%[^\n]%*c", sen);

    printf("%c\n%s\n%s", ch, s, sen);
    return 0;
}
