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

    int num;
    printf("The 20 numbers are:\n");
    for(int i=0; i<20; i++)
    {
        fread(&num, sizeof(int), 1, fptr);
        printf("%d\n", num);
    }
    fclose(fptr);

    return 0;
}
