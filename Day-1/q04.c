// Write a C Program to enter a number and store the number across the following
// structure and print the content of each member of the structure. Then aggregate each
// member of the structure to form the original number and print the same.
// struct pkt{
// char ch1;
// char ch2[2];
// char ch3;
// };

#include <stdio.h>
#include <stdlib.h>
struct pkt{
    char ch1;
    char ch2[2];
    char ch3;    
};

int main()
{
    int num;
    struct pkt packet;
    printf("Enter a number: ");
    scanf("%d", &num);

    unsigned char *ch = (char *)&num;
    packet.ch1 = *ch; *ch++;
    packet.ch2[0] = *ch; *ch++;
    packet.ch2[1] = *ch; *ch++;
    packet.ch3 = *ch;

    printf("The contents of the structure are: \n");
    printf("ch1 = %d\n", packet.ch1);
    printf("ch2[0] = %d\n", packet.ch2[0]);
    printf("ch2[1] = %d\n", packet.ch2[1]);
    printf("ch3 = %d\n", packet.ch3);

    int regenerated_num = 0;
    regenerated_num |= packet.ch1;
    regenerated_num |= (packet.ch2[0] << 8);
    regenerated_num |= (packet.ch2[1] << 16);
    regenerated_num |= (packet.ch3 << 24);
    
    printf("Regenerated number: %d", regenerated_num);

    
return 0;
}