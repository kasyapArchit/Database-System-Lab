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

    int num[21]={0};
    printf("The 20 numbers are:\n");
    fread(num, sizeof(int), 20, fptr);
    for(int i=0; i<20; i++)
    {
        printf("%d\n", num[i]);
    }
    fclose(fptr);

    return 0;
}
