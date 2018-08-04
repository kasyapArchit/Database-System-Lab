#include "stdio.h"

int main(int argc, char *argv[])
{
    FILE *fptr;
    fptr = fopen(argv[1], "w");
    if(fptr == NULL)
    {
        printf("Error!");
        return 0;
    }

    printf("Input 20 numbers\n");
    int num[21];
    for(int i=0; i<20; i++)
    {
        scanf("%d", &num[i]);
    }
    fwrite(num, sizeof(int), 20, fptr);
    fclose(fptr);

    return 0;
}
