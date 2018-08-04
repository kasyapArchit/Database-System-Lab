#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct Student
{
    int roolNo;
    char name[30];
    int age;
};

int main(int argc, char *argv[])
{
    FILE *fptr;
    fptr = fopen(argv[1], "r");
    if(fptr == NULL)
    {
        printf("Error!");
        return 0;
    }

    printf("Students info are\n");
    struct Student st;
    st.roolNo = 1234;
    strcpy(st.name, "Hello");
    st.age = 25;
    for(int i=0; i<5; i++)
    {
        fscanf(fptr ,"%d, %[^,], %d\n", &st.roolNo, st.name, &st.age);
        printf("%d %s %d\n", st.roolNo, st.name, st.age);
    }
    fclose(fptr);

    return 0;
}
