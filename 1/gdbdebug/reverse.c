#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reverse.h"

int reverse(char* str)
{
    int i;
    int len;
    char c;
    len = strlen(str);
    for (i = 0; i < len/2; ++i)
    {
        c = *(str +i );//c = str[i]
        *(str + i ) = *(str + len - i - 1); //str[i] = str[len-i-1];
        *(str + len - i - 1) = c; //str[len-i-1] = c;
    }
    return 1;
}

int main(void)
{
    char str[1024];
    printf("Give me a word to reverse:\n");
    scanf("%s", str);
    reverse(str);
    printf("REVERSE:   %s\n",str);
    return 0;
}