#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

// test_strtok.c
int main(void)
{
    char *str = "hello world this is C";

    char *token = strtok(str, " ");

    while (token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }
}
