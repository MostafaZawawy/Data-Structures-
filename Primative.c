#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void print_binary_char(char a)
{
    int y,x;
    for(x=7; x>=0; x--)
    {
        y=1<<x;
        if(y&a)
            printf("1");
        else
            printf("0");
    }
}
union FloatToHex
{
    float f;
    int i;
} X;
void question1() {
	printf("printing from -16 to 15 in binary\n");
	char c;
	for(c=-16; c<16; c++) {
		printf("%d\t", c);
		print_binary_char(c);
		printf("\n");
}}
/* My machine uses Two's complement*/
void print_binary_float(float a)
{
    int z,y;
    X.f=a;
    printf("%x",X.i);/*the our system uses a little endian storage but as we are using x.i which is integer so the bits will be read from the memory as big endian*/

}
void question2()
{

    float numbers[] = {0.0f, 1.0f, 2.0f, 0.1f};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    int i;

    for(i=0; i<count; i++)
    {
        printf("%.2f is represented as: ", numbers[i]);
        print_binary_float(numbers[i]);
        printf("\n");
    }

}/* floating points are stored according to IEE's double precision floating point as i am using a 64 bit system and my machine uses a little endian*/

float get_smallest_positive_float()
{
    X.i=1;
    X.i=X.i<<23;
    X.i=X.i&(1<<23);
    /*shifting the right most bit which is 1 in the integer to the correct position(which is the right most bit of the exponent)*/
    return X.f;
}
union IntLong
{
long double l;
int i[3];
} z;
union epsilon
{
double d;
int i;
} e;
double get_double_epsilon()
{
    e.d=1;
    e.i=e.i|1;
    /* double x=1;
     while((1+0.5*x)>1)
         x=x/2;
     x=x*2;
     return x;*/

    return e.d-1;
}
int get_longdouble_exponent_bias()
{
    z.l=1;
    int y,x;
    int c=0;
    int count=0;
    for(x=95; x>=0; x--)
    {
        if(x==63||x==31)
            c++;
        y=1<<x;
        if(y&((int)z.i[c]))
        {
            printf("1"); //for me to see the representation of 1 as a longDouble in memory
            if(x<60)
            //to ignore any thing in the mantisa as we want to know the bias of the exponent
            count++;
        }
        else
            printf("0");

    }
    /*the number of ones in the exponent is 14 so the the range is 2^15=32768, two special numbers(infinity and NaN are stored in 32767,32766) so we have 32766/2=16383 which is 2^14-1 as LongDouble exponent*/
    return (int)pow(2,count)-1;

}
int get_command() {
	int choice;
	printf("\n\n");
	printf("*********************************************\n");
	printf("* Enter 1 for Signed Integer Representation *\n");
	printf("* Enter 2 for Floating-Point Endianness     *\n");
	printf("* Enter 3 for Floating-Point Representation *\n");
	printf("* Enter anything else to exit               *\n");
	printf("*********************************************\n");
	printf("Your choice: ");
	scanf("%d", &choice);
	fseek(stdin, 0, SEEK_END);
	printf("\n");
	return choice;
}
void question3()
{
    printf("The smallest positive 'float' is: %e\n", get_smallest_positive_float());
    printf("Epsilon for 'double' is:%le\n", get_double_epsilon());
    printf("'long double' has a bias of %d for its exponent\n", get_longdouble_exponent_bias());
}

int main()
{
    int choice;
	while(1) {
		switch(get_command()) {
			case 1:
				question1();
				break;
			case 2:
				question2();
				break;
			case 3:
				question3();
				break;
			default:
				printf("Invalid Choice. Exiting...\n");
				exit(1);
		}
	}
    return 0;
}
