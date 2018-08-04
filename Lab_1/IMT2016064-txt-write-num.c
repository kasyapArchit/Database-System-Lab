// Write 20 numbers to a txt file
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
    int n;
    for(int i=0; i<20; i++)
    {
        scanf("%d", &n);
        fprintf(fptr ,"%d\n", n);
    }
    fclose(fptr);

    return 0;
}
