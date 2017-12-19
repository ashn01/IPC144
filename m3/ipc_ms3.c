#include <stdio.h>

// define statements go here
#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0



/* ms1 prototypes*/
void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void pause(void);
void clrKyb(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);
/* ipc_ms2 prototype*/
int yes(void);  // ms2

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};


/* ms3 prototypes*/

double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);

/* Constant double TAX value */

const double TAX = 0.13l;

double totalAfterTax(struct Item item)
{
	return item.isTaxed ? item.price * item.quantity + item.price * item.quantity * TAX : item.price * item.quantity;
}

int isLowQty(struct Item item)
{
	return item.quantity < item.minQuantity ? 1 : 0;
}

struct Item itemEntry(int sku)
{
	struct Item i;
	char taxed;

	printf("        SKU: %d\n", sku);
	i.sku = sku;
	printf("       Name: ");
	scanf("%20[^\n]", i.name);
	clrKyb();
	printf("      Price: ");
	scanf("%lf", &i.price);
	printf("   Quantity: ");
	scanf("%d", &i.quantity);
	printf("Minimum Qty: ");
	scanf("%d", &i.minQuantity);
	clrKyb();
	printf("   Is Taxed: ");
	scanf("%c", &taxed);
	i.isTaxed = taxed == 'y' ? 1 : 0;
	clrKyb();

	return i;
}

void dspItem(struct Item item, int linear)
{
	if (linear)
	{
		printf("|%d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|", item.sku, item.name, item.price, item.isTaxed ? "Yes" : "No", item.quantity, item.minQuantity, item.isTaxed ? item.price * item.quantity + item.price * item.quantity * TAX : item.price * item.quantity);
		item.quantity < item.minQuantity ? printf("***\n") : printf("\n");
	}
	else
	{
		if (item.quantity < item.minQuantity && item.isTaxed)
		{
			printf("        SKU: %d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %.2f\n", item.price);
			printf("   Quantity: %d\n", item.quantity);
			printf("Minimum Qty: %d\n", item.minQuantity);
			printf("   Is Taxed: %s\n", item.isTaxed ? "Yes" : "No");
			printf("WARNING: Quantity low, please order ASAP!!!\n");
		}
		else
		{
			printf("        SKU: %d\n", item.sku);
			printf("       Name: %s\n", item.name);
			printf("      Price: %.2f\n", item.price);
			printf("   Quantity: %d\n", item.quantity);
			printf("Minimum Qty: %d\n", item.minQuantity);
			printf("   Is Taxed: %s\n", item.isTaxed ? "Yes" : "No");
		}
	}
}

void listItems(const struct Item item[], int NoOfItems)
{
	int i=0;
	double grandTotal=0l;

	prnTitle();
	for (i = 0; i < NoOfItems; i++)
	{
		printf("%-4d", i + 1);
		dspItem(item[i], 1);
		grandTotal += item[i].isTaxed ? item[i].price * item[i].quantity + item[i].price * item[i].quantity * TAX : item[i].price * item[i].quantity;
	}
	prnFooter(grandTotal);
}

int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index)
{
	int i;
	for (i = 0; i < NoOfRecs; i++)
	{
		if (item[i].sku == sku)
		{
			*index = i;
			return 1;
		}
	}
	return 0;
}

/*
int main() {
	struct Item I[21] = {
	   { 4.4,275,0,10,2,"Royal Gala Apples" },
	   { 5.99,386,0,20,4,"Honeydew Melon" },
	   { 3.99,240,0,30,5,"Blueberries" },
	   { 10.56,916,0,20,3,"Seedless Grapes" },
	   { 2.5,385,0,5,2,"Pomegranate" },
	   { 0.44,495,0,100,30,"Banana" },
	   { 0.5,316,0,123,10,"Kiwifruit" },
	   { 4.49,355,1,20,5,"Chicken Alfredo" },
	   { 5.49,846,1,3,5,"Veal Parmigiana" },
	   { 5.29,359,1,40,5,"Beffsteak Pie" },
	   { 4.79,127,1,30,3,"Curry Checken" },
	   { 16.99,238,1,10,2,"Tide Detergent" },
	   { 10.49,324,1,40,5,"Tide Liq. Pods" },
	   { 10.99,491,1,50,5,"Tide Powder Det." },
	   { 3.69,538,1,1,5,"Lays Chips S&V" },
	   { 3.29,649,1,15,5,"Joe Org Chips" },
	   { 1.79,731,1,100,10,"Allen's Apple Juice" },
	   { 6.69,984,1,30,3,"Coke 12 Pack" },
	   { 7.29,350,1,50,5,"Nestea 12 Pack" },
	   { 6.49,835,1,20,2,"7up 12 pack" }
	};
	double val;
	int ival;
	int searchIndex;
	val = totalAfterTax(I[0]);
	printf("totalAfterTax: yours=%lf, program's=44.000000\n", val);
	val = totalAfterTax(I[7]);
	printf("totalAfterTax: yours=%lf, program's=101.474000\n", val);
	ival = isLowQty(I[0]);
	printf("isLowQty: yours=%d, program's=0\n", ival);
	ival = isLowQty(I[14]);
	printf("isLowQty: yours=%d, program's=1\n", ival);
	pause();
	printf("itemEntry, enter the following values:\n");
	printf("        SKU: 999\n"
		"       Name: Red Apples\n"
		"      Price: 4.54\n"
		"   Quantity: 50\n"
		"Minimum Qty: 5\n"
		"   Is Taxed: n\n");
	printf("Enter the values:\n");
	I[20] = itemEntry(999);
	printf("dspItem, Linear:\nYours: ");
	dspItem(I[20], LINEAR);
	printf(" Prog: |999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|\n");
	printf("dspItem, Form:\nYours:\n");
	dspItem(I[20], FORM);
	printf("Programs: \n");
	printf("        SKU: 999\n"
		"       Name: Red Apples\n"
		"      Price: 4.54\n"
		"   Quantity: 50\n"
		"Minimum Qty: 5\n"
		"   Is Taxed: No\n");
	I[20].quantity = 2;
	I[20].isTaxed = 1;
	pause();
	printf("dspItem, Linear with low value and taxed:\nYours: ");
	dspItem(I[20], LINEAR);
	printf(" Prog: |999|Red Apples          |    4.54|  Yes|   2 |   5 |       10.26|***\n");
	printf("dspItem, Form with low value:\nYours:\n");
	dspItem(I[20], FORM);
	printf("Programs: \n");
	printf("        SKU: 999\n"
		"       Name: Red Apples\n"
		"      Price: 4.54\n"
		"   Quantity: 2\n"
		"Minimum Qty: 5\n"
		"   Is Taxed: Yes\n"
		"WARNING: Quantity low, please order ASAP!!!\n");
	pause();
	printf("Listing Items: \n");
	listItems(I, 21);
	pause();
	printf("Locate Item, successful search:\n");
	printf("program: Found the item 999 at index: 20\n");
	printf("  Yours: ");
	if (locateItem(I, 21, 999, &searchIndex)) {
		printf("Found the item 999 at index: %d\n", searchIndex);
	}
	else {
		printf("No item with the sku 999 is in the array!\n");
	}

	printf("Locae Item, unsuccessful search:\n");
	printf("Progam: No item with the sku 732 is in the array!\n");
	printf(" Yours: ");
	if (locateItem(I, 21, 732, &searchIndex)) {
		printf("Found the item at index: %d\n", searchIndex);
	}
	else {
		printf("No item with the sku 732 is in the array!\n");
	}
	return 0;
}
*/


/*   item entry output
		SKU: 999
	   Name: Red Apples
	  Price: 4.54
   Quantity: 50
Minimum Qty: 5
   Is Taxed: n

		SKU: 999
	   Name: Red Apples
	  Price: 4.54
   Quantity: 50
Minimum Qty: 5
   Is Taxed: No
WARNING: Quantity low, please order ASAP!!!


*/

/*  dspItems
|999|Red Apples          |    4.54|   No|  50 |   5 |      227.00|

		SKU: 999
	   Name: Red Apples
	  Price: 4.54
   Quantity: 50
Minimum qty: 5
   Is Taxed: No

*/


/*ms1 and 2 functions: */

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
