// piggybank program workshop 2 IPC144
// name: Youngmin Kim
// student number: 109-161-158
// Section: 
#include <stdio.h>

int main(void)
{
	int toonies=0, loonies=0, quarters=0, dimes=0, nickels=0, pennies=0;
	float total;
	int b50, b20, b10, b5;
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
	total = (toonies * 2) + loonies + (quarters * 0.25) + (dimes * 0.1) + (nickels * 0.05) + (pennies * 0.01);
	printf("You have $%.2f in your piggy bank!\n", total);
	b50 = total / 50;
	b20 = (total - b50 * 50) / 20;
	b10 = (total - b50 * 50 - b20 * 20) / 10;
	b5 = (total - b50 * 50 - b20 * 20 - b10 * 10) / 5;
	printf("$50 bill: %d\n",b50);
	printf("$20 bill: %d\n",b20);
	printf("$10 bill: %d\n",b10);
	printf("$5 bill: %d\n",b5);
	printf("Changes: $%.2f\n",total-b50*50-b20*20-b10*10-b5*5);
	return 1;
}
