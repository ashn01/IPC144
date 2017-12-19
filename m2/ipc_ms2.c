#include <stdio.h>
void clrKyb(void);
void pause(void);
int getInt(void);
int yes(void);  // ms2
int getIntLimited(int lowerLimit, int upperLimit);
void welcome(void);
void GrocInvSys(void);  // ms2
int menu(void);  // ms2

/*
int main(void) {
   GrocInvSys();
   return 0;
}*/

// implmement MS2 fucntions here
int yes(void)
{
	char answer;
	printf("(Y)es/(N)o : ");
	scanf("%c", &answer);
	clrKyb();
	while (answer != 'Y' && answer != 'y' && answer != 'N' && answer != 'n')
	{
		printf("Only (Y)es or (N)o are acceptable: ");
		scanf("%c", &answer);
	}

	switch (answer)
	{
	case 'Y':
	case 'y': return 1;
	case 'N':
	case 'n': return 0;
	}
	return 1;
}

int menu(void)
{
	int answer;
	puts("1- List all items");
	puts("2- Search by SKU");
	puts("3- Checkout an item");
	puts("4- Stock an item");
	puts("5- Add new item or update item");
	puts("6- delete item");
	puts("7- Search by name");
	puts("0- Exit program");
	printf("> ");
	scanf("%d", &answer);
	while (answer < 0 || answer > 7)
	{
		printf("Invalid value, 0 < value < 7: ");
		clrKyb();
		scanf("%d", &answer);
	}

	return answer;
}

void GrocInvSys(void)
{
	int selection;
	welcome();
	do
	{
		selection = menu();
		switch (selection)
		{
		case 1: 
			puts("List Items!");
			puts("Press <ENTER> to continue...");
			break;
		case 2:
			puts("Search Items!");
			puts("Press <ENTER> to continue...");
			break;
		case 3:
			puts("Checkout Item!");
			puts("Press <ENTER> to continue...");
			break;
		case 4:
			puts("Stock Item!");
			puts("Press <ENTER> to continue...");
			break;
		case 5:
			puts("Add/Update Item!");
			puts("Press <ENTER> to continue...");
			break;
		case 6:
			puts("Delete Item!");
			puts("Press <ENTER> to continue...");
			break;
		case 7:
			puts("Search by name!");
			puts("Press <ENTER> to continue...");
			break;
		case 0:
			printf("Exit the program? ");
			clrKyb();
			if (yes())
			{
				selection = -1;
			}

			break;
		}
	} while (selection != -1);

}

// copy MS1 functions here

void welcome(void)
{
	printf("---=== Grocery Inventory System ===---\n\n");
}

void prnTitle(void)
{
	printf("Row |SKU| Name               | Price  |Taxed| Qty | Min |   Total    |Atn\n----+---+--------------------+--------+-----+-----+-----+------------|---\n");

}

void prnFooter(double gTotal)
{
	printf("--------------------------------------------------------+----------------\n");
	if (gTotal > 0)
		printf("                                           Grand Total: |%12.2lf\n", gTotal);
}

void clrKyb(void)
{
	char entered = '0';
	while (entered != '\n')
	{
		scanf("%c", &entered);
	}
}

void pause(void)
{
	printf("Press <ENTER> to continue...");
	clrKyb();
}

int getInt(void)
{
	int entered;
	char isNewline;

	do
	{
		scanf("%d%c", &entered, &isNewline);
		if (isNewline != '\n')
		{
			printf("Invalid integer, please try again: ");
			clrKyb();
		}
	} while (isNewline != '\n');

	return entered;
}

double getDbl(void)
{
	double entered;
	char isNewline;
	do
	{
		scanf("%lf%c", &entered, &isNewline);
		if (isNewline != '\n')
		{
			printf("Invalid number, please try again: ");
			clrKyb();
		}
	} while (isNewline != '\n');

	return entered;
}

int getIntLimited(int lowerLimit, int upperLimit)
{
	int entered;
	do
	{
		scanf("%d", &entered);
		if (entered < lowerLimit || entered > upperLimit)
			printf("Invalid value, %d < value < %d: ", lowerLimit, upperLimit);
	} while (entered < lowerLimit || entered > upperLimit);

	return entered;
}

double getDblLimited(double lowerLimit, double upperLimit)
{
	double entered;
	do
	{
		scanf("%lf", &entered);
		if (entered < lowerLimit || entered > upperLimit)
			printf("Invalid value, %lf< value < %lf: ", lowerLimit, upperLimit);
	} while (entered < lowerLimit || entered > upperLimit);

	return entered;
}


/*
---=== Grocery Inventory System ===---

1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 8
Invalid value, 0 < value < 7: 1
List Items!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 2
Search Items!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 3
Checkout Item!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 4
Stock Item!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 5
Add/Update Item!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 6
Delete Item!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 7
Search by name!
Press <ENTER> to continue...
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 0
Exit the program? (Y)es/(N)o : x
Only (Y)es or (N)o are acceptable: n
1- List all items
2- Search by SKU
3- Checkout an item
4- Stock an item
5- Add new item or update item
6- delete item
7- Search by name
0- Exit program
> 0
Exit the program? (Y)es/(N)o : y
*/
