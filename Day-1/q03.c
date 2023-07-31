// Write a C program to extract each byte from a given number and store them in separate 
// character variables and print the content of those variables.

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    unsigned char *ch = (char *)&num;
    for (int i=0; i<sizeof(num); i++)
        printf("Byte %d: %d\n", i+1, *(ch+i));
return 0;
}

/* ALTERNATE SOLUTION
#include <stdio.h>
#include <stdlib.h>

int main(){
    int num;
    printf("Enter no.: ");
    scanf("%d", &num);

    int p = (num >> 24) & 0xff;
    int q = (num >> 16) & 0xff;
    int r = (num >> 8) & 0xff;
    int s = num & 0xff;
    
    printf("Byte 1: %d\nByte 2: %d\nByte 3: %d\nByte 4: %d", p,q,r,s);
}
*/