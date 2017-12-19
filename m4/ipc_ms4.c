#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#define MAX_ITEM_NO 21
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0

/***************************************************************
Tester Function prototypes and information, DO NOT MODIFY */

void searchTest();
void updateTest();
void addTest();
void addOrUpdateTest();
void adjustQtyTest();

struct Item {
   double price;
   int sku;
   int isTaxed;
   int quantity;
   int minQuantity;
   char name[21];
};

struct Item GI[21] = {
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
int GNoOfRecs = 20;

/**************************************************************/

/*************************************************************
Student Milestone 3 definitions and prototypes go here:
(Do not copy struct Item since it is already implimented above*/

const double TAX = 0.13l;

void welcome(void);
void prnTitle(void);
void prnFooter(double gTotal);
void pause(void);
void clrKyb(void);
int getInt(void);
double getDbl(void);
int getIntLimited(int lowerLimit, int upperLimit);
double getDblLimited(double lowerLimit, double upperLimit);

double totalAfterTax(struct Item item);
int isLowQty(struct Item item);
struct Item itemEntry(int sku);
void dspItem(struct Item item, int linear);
void listItems(const struct Item item[], int NoOfItems);
int locateItem(const struct Item item[], int NoOfRecs, int sku, int* index);




/*End of Student Milestone 3 definitions and prototypes
*************************************************************/

/*************************************************************
Milestone 4 defintions and prototypes:*/
// write the define statements here:




// function prototypes in order of implementation:
void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);


/*End of Milestone 4 defintions and prototypes:
***************************************************************/

/*************************************************************
Main tester */

/*int main() {
   //searchTest();
   //updateTest();
   //addTest();
   //addOrUpdateTest();
   adjustQtyTest();
   return 0;
}
*/
/*End of main tester
******************************************************************/


/***************************************************************
Milestone 4 functions to be implemented */
void search(const struct Item item[], int NoOfRecs)
{
	int sku, index;
	printf("Please enter the SKU: ");
	scanf("%d", &sku);
	if (sku >= SKU_MIN && sku <= SKU_MAX)
	{
		if (locateItem(item, NoOfRecs, sku, &index))
		{
			dspItem(item[index], FORM);
		}
		else
		{
			printf("Item not found!\n");
			clrKyb();
		}
	}
}

void updateItem(struct Item* itemptr)
{
	struct Item temp;
	char answer;
	printf("Enter new data:\n");
	temp = itemEntry(itemptr->sku);
	printf("Overwrite old data? (Y)es/(N)o: ");
	scanf("%c", &answer);
	if (answer == 'y')
	{
		*itemptr = temp;
		printf("--== Updated! ==--\n");
	}
	else
	{
		printf("--== Aborted! ==--\n");
	}
}

void addItem(struct Item item[], int *NoOfRecs, int sku) 
{
	struct Item temp;
	char answer;
	if (*NoOfRecs != MAX_ITEM_NO)
	{
		temp = itemEntry(sku);
		printf("Add Item? (Y)es/(N)o: ");
		scanf("%c", &answer);
		if (answer == 'y')
		{
			printf("--== Added! ==--\n");

			item[*NoOfRecs] = temp;
			*NoOfRecs+=1;
		}
		else
		{
			printf("--== Aborted! ==--\n");
		}
	}
	else
	{
		printf("Can not add new item; Storage Full!\n");
	}
}

void addOrUpdateItem(struct Item item[], int* NoOfRecs) 
{
	int sku,index;
	char answer;
	printf("Please enter the SKU: ");
	scanf("%d", &sku);
	if (sku >= SKU_MIN && sku <= SKU_MAX)
	{
		if (locateItem(item, *NoOfRecs, sku, &index))
		{
			dspItem(item[index], FORM);
			printf("Item already exists, Update? (Y)es/(N)o: ");
			scanf("%c", &answer);
			if (answer == 'y')
			{
				clrKyb();
				updateItem(&item[index]);
			}
			else
			{
				printf("--== Aborted! ==--\n");
			}
		}
		else
		{
			addItem(item,NoOfRecs,sku);
		}
	}
}

void adjustQty(struct Item item[], int NoOfRecs, int stock) 
{
	int sku,index,value;
	printf("Please enter the SKU: ");
	scanf("%d", &sku);
	if (locateItem(item, NoOfRecs, sku, &index))
	{
		dspItem(item[index],FORM);
		printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ",stock == STOCK ? "to stock" : "to checkout", stock == STOCK ? MAX_QTY - item[index].quantity : item[index].quantity );
		scanf("%d", &value);
		if (value > 0 && value <= (stock == STOCK ? MAX_QTY - item[index].quantity : item[index].quantity))
		{
			if (stock == STOCK)
			{
				item[index].quantity += value;
				printf("--== Stocked! ==--\n");
			}
			else
			{
				item[index].quantity -= value;
				printf("--== Checked out! ==--\n");
			}
			if (item[index].quantity <= item[index].minQuantity)
			{
				printf("Quantity is low, please reorder ASAP!!!\n");
			}
		}
		else if (value == 0)
		{
			printf("--== Aborted! ==--\n");
		}
	}
	else
	{
		printf("SKU not found in storage!\n");
	}

}
/*End of Milestone 4 functions
******************************************************************/

/*****************************************************************
Milestone 3 function implementations:
Please copy your milestone 3 functions here: */
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

//	clrKyb();
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
	clrKyb();
	if (linear)
	{
		printf("|%d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|", item.sku, item.name, item.price, item.isTaxed ? "Yes" : "No", item.quantity, item.minQuantity, item.isTaxed ? item.price * item.quantity + item.price * item.quantity * TAX : item.price * item.quantity);
		item.quantity < item.minQuantity ? printf("***\n") : printf("\n");
	}
	else
	{
		if (item.quantity <= item.minQuantity )
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
	int i = 0;
	double grandTotal = 0l;

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





/*End of Milestone 3 functions.
*******************************************************************/

/***************************************************************
Tester Functions DO NOT MODIFY */

void searchTest() {
   printf("================Search Test:\n");
   printf("Enter 731: \n");
   search(GI, GNoOfRecs);
   printf("Enter 222: \n");
   search(GI, GNoOfRecs);
}
void updateTest() {
   struct Item I = { 11.11,111,1,11,1,"Ones!" };
   printf("================Update Test:\n");
   printf("Enter the follwoing: \n");
   printf(
      "         SKU: 111\n"
      "        Name: Grape\n"
      "      Price : 22.22\n"
      "   Quantity : 22\n"
      "Minimum Qty : 2\n"
      "   Is Taxed : y\n"
      "Overwrite old data? (Y)es/(N)o: n\n");
   updateItem(&I);
   printf("Unchanged Item Data:\n");
   dspItem(I, FORM);
   printf("Enter the follwoing: \n");
   printf(
      "         SKU: 111\n"
      "        Name: Grape\n"
      "      Price : 22.22\n"
      "   Quantity : 22\n"
      "Minimum Qty : 2\n"
      "   Is Taxed : y\n"
      "Overwrite old data? (Y)es/(N)o: y\n");
   updateItem(&I);
   printf("Updated Item: \n");
   dspItem(I, FORM);
}
void addTest() {
   printf("================Add Test:\n");
   printf("Total items in Storage: %d, Max no: %d\n", GNoOfRecs, MAX_ITEM_NO);
   printf("Enter the follwoing: \n");
   printf(
      "         SKU: 222\n"
      "        Name: Grape\n"
      "      Price : 22.22\n"
      "   Quantity : 22\n"
      "Minimum Qty : 2\n"
      "   Is Taxed : y\n"
      "Add Item? (Y)es/(N)o: n\n");
   addItem(GI, &GNoOfRecs, 222); //n
   printf("Garbage here! Nothing is added, No of items in storage: %d\n", GNoOfRecs);
   dspItem(GI[GNoOfRecs], FORM);
   printf("Enter the follwoing: \n");
   printf(
      "         SKU: 222\n"
      "        Name: Grape\n"
      "      Price : 22.22\n"
      "   Quantity : 22\n"
      "Minimum Qty : 2\n"
      "   Is Taxed : y\n"
      "Add Item? (Y)es/(N)o: y\n");
   addItem(GI, &GNoOfRecs, 222); //y
   printf("New item is added, No of itemsinstorage: %d\n", GNoOfRecs);
   dspItem(GI[GNoOfRecs - 1], FORM);
   printf("Adding 333: \n");
   addItem(GI, &GNoOfRecs, 333);
}
void addOrUpdateTest() {
   GNoOfRecs = MAX_ITEM_NO;
   printf("================AddOrUpdate Test:\n");
   printf("Enter 731 and then \'n\':\n");
   addOrUpdateItem(GI, &GNoOfRecs); // n
   printf("Enter 731, \'y\' and then:\n"
      "       Name: Apple\n"
      "      Price: 1.80\n"
      "   Quantity: 101\n"
      "Minimum Qty: 11\n"
      "   Is Taxed: n\n"
      "Overwrite old data? (Y)es/(N)o: y\n");
   addOrUpdateItem(GI, &GNoOfRecs); // yes new data Yes
   printf("Updated Item: \n");
   dspItem(GI[16], FORM);
   printf("Enter 444: \n");
   addOrUpdateItem(GI, &GNoOfRecs); //n
}

void adjustQtyTest() {
   printf("================AdjustQty Test:\n");
   printf("Invalid SKU Test; Enter 444:\n");
   adjustQty(GI, GNoOfRecs, STOCK);
   printf("Aborting Entry test; Enter 731 and then 0:\n");
   adjustQty(GI, GNoOfRecs, CHECKOUT);
   printf("Checking out with low quantity warning; Enter 731 and then 90:\n");
   adjustQty(GI, GNoOfRecs, CHECKOUT);
   printf("Stocking; Enter 731 and then 50:\n");
   adjustQty(GI, GNoOfRecs, STOCK);
   dspItem(GI[16], FORM);
}

/* End test functions
*********************************************************************/
