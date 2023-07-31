/*Write a C program to assign values to each member of the following structure. 
Pass the populated structure to a function Using call-by-value and another function 
using call-by-address and print the value of each member of the structure.
struct student_info{
int roll_no;
char name[50];
float CGPA;
struct dob age;
};
*/
#include <stdio.h>
#include <stdlib.h>
struct dob{
    int d,m,y;
};
struct student_info{
    int roll_no;
    char name[50];
    float CGPA;
    struct dob age;
};
void print_by_value(struct student_info s){
    printf("\nSTUDENT DETAILS (CALL BY VALUE)");
    printf("\nName: %s\nRoll: %d\nCGPA: %.2f\nDOB: %d-%d-%d\nAge: %d",
            s.name, s.roll_no, s.CGPA, s.age.d, s.age.m, s.age.y, 2023-s.age.y);
}
void print_by_address(struct student_info *s){
    printf("\nSTUDENT DETAILS (CALL BY ADDRESS)");
    printf("\nName: %s\nRoll: %d\nCGPA: %.2f\nDOB: %d-%d-%d\nAge: %d",
        s->name, s->roll_no, s->CGPA, s->age.d, s->age.m, s->age.y, 2023-s->age.y);
}
int main()
{
    struct student_info s;
    printf("Enter name: ");
    gets(s.name);
    printf("Enter roll no.: ");
    scanf("%d", &s.roll_no);
    printf("Enter CGPA: ");
    scanf("%f", &s.CGPA);
    printf("Enter DOB (in dd-mm-yyyy): ");
    scanf("%d %d %d", &s.age.d, &s.age.m, &s.age.y);
    print_by_value(s);
    print_by_address(&s);
return 0;
}