// Write a C program to swap the content of 2 variables entered through the 
// command line using function and pointer.
#include <stdio.h>
#include <stdlib.h>
void swap(int *c, int *d){
    int temp = *c;
    *c = *d;
    *d = temp;
}
int main(int argc, char* argv[]){
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    printf("Entered values: a = %d, b = %d", a, b);
    swap(&a,&b);
    printf("\nSwapped values: a = %d, b = %d", a, b);
}
