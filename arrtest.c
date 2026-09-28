#include <stdio.h>
int main(void)
{
    int arr[] = {1, 2, 3};
    printf("%d", arr[2]);
    printf("%d", *(arr + 2));
    printf("%d", 2 [arr]);
    printf("%d", *(2 + arr));
}