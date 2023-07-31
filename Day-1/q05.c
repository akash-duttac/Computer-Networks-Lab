// Write a C program to check whether the Host machine is in Little Endian or Big
// Endian. Enter a number, print the content of each byte location and Convert the
// Endianness of the same i.e. Little to Big Endian and vice-versa.
#include <stdio.h>
#include <stdlib.h>
int endian_check(int num){
    unsigned char *ch = (char *)&num;
    return (int)*ch;
}
unsigned int convertLittleToBig(unsigned int num){
    return ((num >> 24) & 0xff)
            | ((num >> 8) & 0xff00)
            | ((num << 8) & 0xff0000)
            | ((num << 24) & 0xff000000);
}
void print_byte(unsigned int num){
    char *ch = (char *)&num;
    for (int i=0; i<sizeof(num); i++)
        printf("Byte %d: %d\n", i+1, *(ch+i));
}
int main()
{
    unsigned int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (endian_check(num)){
        printf("\nHost machine is Little Endian\n");
    } else {
        printf("\nHost machine is Big Endian\n");
    }
    print_byte(num);
    //since host machine is little endian
    unsigned int bigEnd = convertLittleToBig(num);
    printf("\nBig endian form: %d\n", bigEnd);
    print_byte(bigEnd);
return 0;
}