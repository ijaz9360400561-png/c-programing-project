#include<stdio.h>
int main()
{
int choice;
float a=0,b=0;
do
{
printf("\n======CALCULATER MENU=======\n");
printf("1.addition\n");
printf("2.subraction\n");
printf("3.multiplication\n");
printf("4.division\n");
printf("5.exit");
printf("Enter your choice:");
scanf("%d",&choice);
if(choice>=1 && choice<=4)
{
printf("enter two numbers:");
scanf("%f %f", &a, &b);
}
switch(choice)
{
case 1:
printf("result=%.2f\n",a+b);
break;
case 2:
printf("result=%.2f\n",a-b);
break;
case 3:
printf("result=%.2f\n",a*b);
break;
case 4:
if(b!=0)
printf("result=%.2f\n",a/b);
else
printf("error:division by zero!\n");
break;
case 5:
printf("exiting the program...\n");
}
} while(choice!=5);
return 0;
}