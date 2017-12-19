// piggybank program workshop 2 IPC144
// name: Youngmin Kim
// student number: 109-161-158
// Section: 
#include <stdio.h>

int main(void)
{
	int toonies=0, loonies=0, quarters=0, dimes=0, nickels=0, pennies=0;
	printf("Please enter the number of coins in your piggy bank:\n");
	printf("Toonies: ");
	scanf("%d", &toonies);
	printf("Loonies: ");
	scanf("%d", &loonies);
	printf("Quarters: ");
	scanf("%d", &quarters);
	printf("Dimes: ");
	scanf("%d", &dimes);
	printf("Nickels: ");
	scanf("%d", &nickels);
	printf("Pennies: ");
	scanf("%d", &pennies);
	printf("You have $%.2f in your piggy bank!\n",(toonies * 2) + loonies + (quarters * 0.25) + (dimes * 0.1) + (nickels * 0.05) + (pennies * 0.01));
	return 1;
}
