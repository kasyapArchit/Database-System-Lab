#include "stdio.h"

int main(int argc, char *argv[])
{
    FILE *fptr;
    fptr = fopen(argv[1], "r");
    if(fptr == NULL)
    {
        printf("Error!");
        return 0;
    }

    printf("The 20 numbers are\n");
    int n;
    for(int i=0; i<20; i++)
    {
        fscanf(fptr ,"%d\n", &n);

        printf("%d\n", n);
    }
    fclose(fptr);

    return 0;
}
