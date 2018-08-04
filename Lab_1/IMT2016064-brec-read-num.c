#include "stdio.h"
#include "string.h"

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

    printf("Input 5 Student info\n");
    struct Student st;
    st.roolNo = 1234;
    strcpy(st.name, "Hello");
    st.age = 25;
    for(int i=0; i<5; i++)
    {
        fread(&st, sizeof(struct Student), 1, fptr);
        printf("%d %s %d\n", st.roolNo, st.name, st.age);
    }
    fclose(fptr);

    return 0;
}