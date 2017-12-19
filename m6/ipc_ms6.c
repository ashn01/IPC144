#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <stdio.h>
#define MAX_QTY 999
#define SKU_MAX 999
#define SKU_MIN 100

#define LINEAR 1
#define FORM 0
#define STOCK 1
#define CHECKOUT 0

#define MAX_ITEM_NO 500
#define DATAFILE "ipc_ms5_long.txt"

struct Item {
	double price;
	int sku;
	int isTaxed;
	int quantity;
	int minQuantity;
	char name[21];
};




/********************************************************************
Milestones 1 to 4  prototypes, definitions and etc...*/
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
void GrocInvSys(void);

void search(const struct Item item[], int NoOfRecs);
void updateItem(struct Item* itemptr);
void addItem(struct Item item[], int *NoOfRecs, int sku);
void addOrUpdateItem(struct Item item[], int* NoOfRecs);
void adjustQty(struct Item item[], int NoOfRecs, int stock);






/*End of milestone 1 to 4 stuff
*********************************************************************/



/********************************************************************
Milestone 5 prototypes*/

void saveItem(struct Item item, FILE* dataFile);
int loadItem(struct Item* item, FILE* dataFile);
int saveItems(struct Item* item, char fileName[], int NoOfRecs);
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr);

/*End of milestone 5 prototypes
*********************************************************************/


/********************************************************************
Milestone 6 prototypes*/

void deleteItem(struct Item* item, int* NoOfRecs);
void searchByName(struct Item* item, int NoOfItems);
void sort(struct Item* item, int NoOfItems);


/*End of milestone 6 prototypes
*********************************************************************/


/********************************************************************
Milestone 6 functions*/


void deleteItem(struct Item* item, int* NoOfRecs)
{
	int sku,index;
	char answer;
	struct Item temp = {0};
	printf("Please enter the SKU: ");
	scanf("%d", &sku);
	clrKyb();
	if (locateItem(item, *NoOfRecs, sku, &index))
	{
		dspItem(item[index], FORM);
		printf("This item will be deleted, are you sure? (Y)es/(No): ");
		scanf("%c", &answer);
		clrKyb();
		if (answer == 'y')
		{
			if (index < *NoOfRecs) // move forward
			{
				// if an item is deleted that is not located in the end of array, 
				// move forward behind item to the location where the item is located.
				// 
				int i;
				for (i = index; i < *NoOfRecs; i++)
				{
					item[i] = item[i+1];
				}
			}
			item[*NoOfRecs] = temp; // remove item or remove duplicated item
			// if the item is located in the end of array which doesn't get in the if statement above,
			// just replace the item with a temporal Item
			*NoOfRecs -= 1; // reduce records.
			printf("Item deleted!\n");
			
		}
		else
		{
			printf("Delete aborted!\n");
		}
	}
	else
	{
		printf("Item not found!\n");
	}
}

void searchByName(struct Item* item, int NoOfItems)
{
	char pName[21];
	int i = 0, j, chPtr = 0;
	int charLen = 0;
	int output = 0;
	struct Item temp;

	printf("Please enter partial name: ");
	scanf("%21[^\n]s", pName);
	clrKyb();

	while (pName[charLen] != '\0') // calcualte length entered
		charLen++;


	for (; i < NoOfItems; i++)
	{
		chPtr = 0;
		temp = item[i]; // to prevent to change original data(Upper -> Lower case)
		for (j = 0; temp.name[j] != '\0'; j++)
		{
			if (pName[chPtr] >= 65 && pName[chPtr] <= 90) // make string lowercase
			{
				pName[chPtr] += 32;
			}

			if (temp.name[j] >= 65 && temp.name[j] <= 90) // make string lowercase
			{
				temp.name[j] += 32;
			}

			if (chPtr >= 1 && pName[chPtr] != temp.name[j]) // if not continued, restart
			{
				chPtr = 0;
			}

			if (pName[chPtr] == temp.name[j]) // check if same
			{
				chPtr++;
			}

			if (chPtr == charLen)
			{
				if (output == 0) // only first time.. print title
				{
					prnTitle();
				}
				printf("%-3d ",i+1); // numbering
				dspItem(item[i], LINEAR); // output form
				output = 1;
				break;
			}
		}
	}
	if (output == 0) // if no  output
	{
		printf("No matches found!\n");
	}
	else
	{
		printf("--------------------------------------------------------+----------------\n");
	}
}
void sort(struct Item* item, int NoOfItems)
{
	int answer;
	char cAns;
	struct Item temp = {0}; // init
	int i, j;

	printf("1- Sort by Sku\n");
	printf("2- Sort by Name\n");
	printf("0- Exit\n");
	printf("> ");
	scanf("%d", &answer);
	clrKyb();
	switch (answer)
	{
	case 1:
		printf("List sorted by %s.\n","Sku");
		// sort
		for (i = 0; i < NoOfItems-1; i++)
		{
			for (j = i+1; j < NoOfItems; j++)
			{
				if (item[i].sku > item[j].sku)
				{
					temp = item[i];
					item[i] = item[j];
					item[j] = temp;
				}
			}
		}
		// /sort
		printf("Would you like to save the sorted list in file? (Y)es/(N)o: ");
		scanf("%c", &cAns);
		clrKyb();
		// save 
		if (cAns == 'y')
		{
			if (saveItems(item, DATAFILE, NoOfItems))
			{
				printf("Sorted list saved!\n");
			}
			else
			{
				printf("Could not update data file %s\n",DATAFILE);
			}
		}
		else
		{
			printf("Sorted list NOT saved!\n");
		}
		// /save
		break;
	case 2:printf("List sorted by %s.\n", "Name");
		// sort
		int index=0;
		for (i = 0; i < NoOfItems - 1; i++)
		{
			for (j = i + 1; j < NoOfItems; j++)
			{
				if (item[i].name[index] > item[j].name[index]) // if first letter is different
				{
					temp = item[i];
					item[i] = item[j];
					item[j] = temp;
				}
				else if (item[i].name[index] == item[j].name[index]) // if they are same
				{
					int k=1;
					do
					{
						if (item[i].name[k] > item[j].name[k]) // if letter is different,
						{ // exchange
							temp = item[i];
							item[i] = item[j];
							item[j] = temp;
							break;
						}
						k++;
					} while (item[i].name[k] != '\0' && item[j].name[k] != '\0' && item[i].name[k] == item[j].name[k]);
					// until either of them get \0 and if letters are same
				}
			}
		}
		// /sort
		printf("Would you like to save the sorted list in file? (Y)es/(N)o: ");
		scanf("%c", &cAns);
		clrKyb();
		// save 
		if (cAns == 'y')
		{
			if (saveItems(item, DATAFILE, NoOfItems))
			{
				printf("Sorted list saved!\n");
			}
			else
			{
				printf("Could not update data file %s\n", DATAFILE);
			}
		}
		else
		{
			printf("Sorted list NOT saved!\n");
		}
		// /save
		break;
	case 0:
		break;
	}
}



/*End of milestone 6 functions
*********************************************************************/


/**************************************************************************
TTTTTTTTT   EEEEEEEE   SSSSSSSS   TTTTTTTTTT   EEEEEEEEE   RRRRRRRR
TT       EE         SS             TT       EE          RR     RR
TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RRRRRRRR
TT       EE               SS       TT       EE          RR  RR
TT       EEEEEEEE   SSSSSSSS       TT       EEEEEEEEE   RR    RR
***************************************************************************
Tester for saveItem, loadItem, saveItems and loadItems:
uncomment this to test your functions prior to putting all the code together by adding a * and / here:



void prnFile() {
FILE* tp = fopen("test.txt", "r");
char ch;
if (tp) {
for (; fscanf(tp, "%c", &ch) == 1; putch(ch));
fclose(tp);
}
else {
printf("text.txt not found\n");
}
}


int main(void) {
int i, n;
struct Item GI[3] = {
{ 4.4,275,0,10,2,"Royal Gala Apples" },
{ 5.99,386,0,20,4,"Honeydew Melon" },
{ 3.99,240,0,30,5,"Blueberries" },
};
struct Item I;
struct Item IN[3];
printf("***********Testing saveItem:\n");
printf("Your saveItem saved the following in test.txt: \n");
FILE* tp = fopen("test.txt", "w");
if (tp) {
for (i = 0; i < 3; i++) saveItem(GI[i], tp);
fclose(tp);
prnFile();
}
printf("*******************************\nThey have to match the following:\n");
printf("275,10,2,4.40,0,Royal Gala Apples\n");
printf("386,20,4,5.99,0,Honeydew Melon\n");
printf("240,30,5,3.99,0,Blueberries\n");
printf("***********END Testing saveItem!\n\n\n");
pause();
printf("***********Testing loadItem:\n");
printf("Your loadItem loaded the following from test.txt: \n");
tp = fopen("test.txt", "r");
if (tp) {
for (i = 0; i < 3; i++) {
loadItem(&I, tp);
dspItem(I, LINEAR);
}
fclose(tp);
tp = fopen("test.txt", "w");
fclose(tp);
}
printf("*******************************\nThey have to match the following:\n");
printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
printf("***********END Testing loadItem!\n\n\n");
pause();
printf("***********Testing saveItems:\n");
printf("Your saveItems saved the following in test.txt: \n");
saveItems(GI, "test.txt", 3);
prnFile();
printf("*******************************\nThey have to match the following:\n");
printf("275,10,2,4.40,0,Royal Gala Apples\n");
printf("386,20,4,5.99,0,Honeydew Melon\n");
printf("240,30,5,3.99,0,Blueberries\n");
printf("***********END Testing saveItems!\n\n\n");
pause();
printf("***********Testing loadItems:\n");
printf("Your loadItems loaded the following from test.txt: \n");
loadItems(IN, "test.txt", &n);
for (i = 0; i < n; i++) {
dspItem(IN[i], LINEAR);
}
printf("*******************************\nThey have to match the following:\n");
printf("|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|\n");
printf("|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|\n");
printf("|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|\n");
printf("***********END Testing loadItems!\n\n\n");
pause();
printf("Done!\n");
return 0;
}*/

/* End MS5 functions' tester
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************
***************************************************************************/


/********************************************************************
Main function to run the application
uncomment this to test your functions after putting all the code together by adding a * and / here:
*/
int main(void) {
	GrocInvSys();
	return 0;
}

/* End Main function
********************************************************************/





/********************************************************************
Milestone 5 functions*/

void saveItem(struct Item item, FILE* dataFile)
{
	fprintf(dataFile, "%d,%d,%d,%.2lf,%d,%s\n", item.sku, item.quantity, item.minQuantity, item.price, item.isTaxed, item.name);
}
int loadItem(struct Item* item, FILE* dataFile)
{
	return fscanf(dataFile, "%d, %d, %d, %lf, %d, %[^\n]s", &item->sku, &item->quantity, &item->minQuantity, &item->price, &item->isTaxed, item->name) != EOF ? 1 : 0;
}
int saveItems(struct Item* item, char fileName[], int NoOfRecs)
{
	FILE *fp = NULL;
	int i;
	fp = fopen(fileName, "w");
	if (fp != NULL)
	{
		for (i = 0; i < NoOfRecs; i++)
		{
			saveItem(item[i], fp);
		}
		fclose(fp);
		return 1;
	}
	else
	{
		return 0;
	}
}
int loadItems(struct Item* item, char fileName[], int* NoOfRecsPtr)
{
	FILE *fp = NULL;
	*NoOfRecsPtr = 0; // 0
	fp = fopen(fileName, "r");
	if (fp != NULL)
	{
		while (loadItem(&item[*NoOfRecsPtr], fp))
		{
			//loadItem(&item[*NoOfRecsPtr], fp);
			*NoOfRecsPtr += 1;
		}
		fclose(fp);
		return 1;
	}
	else
	{
		return 0;
	}
}



/*End of milestone 5 functions
*********************************************************************/


/********************************************************************
Milestones 1  to 4 functions*/
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
	clrKyb();
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
		clrKyb();
		if (answer == 'y')
		{
			printf("--== Added! ==--\n");

			item[*NoOfRecs] = temp;
			*NoOfRecs += 1;
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
	int sku, index;
	char answer;
	printf("Please enter the SKU: ");
	scanf("%d", &sku);
	clrKyb();
	if (sku >= SKU_MIN && sku <= SKU_MAX)
	{
		if (locateItem(item, *NoOfRecs, sku, &index))
		{
			dspItem(item[index], FORM);
			printf("Item already exists, Update? (Y)es/(N)o: ");
			scanf("%c", &answer);
			clrKyb();
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
			addItem(item, NoOfRecs, sku);
		}
	}
}

void adjustQty(struct Item item[], int NoOfRecs, int stock)
{
	int sku, index, value;
	printf("Please enter the SKU: ");
	scanf("%d", &sku);
	clrKyb();
	if (locateItem(item, NoOfRecs, sku, &index))
	{
		dspItem(item[index], FORM);
		printf("Please enter the quantity %s; Maximum of %d or 0 to abort: ", stock == STOCK ? "to stock" : "to checkout", stock == STOCK ? MAX_QTY - item[index].quantity : item[index].quantity);
		scanf("%d", &value);
		clrKyb();
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
	//scanf("%lf", &i.price);
	i.price = getDblLimited(0.01, 1000);
	printf("   Quantity: ");
	//scanf("%d", &i.quantity);
	i.quantity = getIntLimited(1, MAX_QTY);
	printf("Minimum Qty: ");
	//scanf("%d", &i.minQuantity);
	i.minQuantity = getIntLimited(0, 100);
	clrKyb();
	printf("   Is Taxed: ");
	scanf("%c", &taxed);
	i.isTaxed = taxed == 'y' ? 1 : 0;
	clrKyb();

	return i;
}

int menu(void)
{
	int answer;
	puts("1- List all items");
	puts("2- Search by SKU");
	puts("3- Checkout an item");
	puts("4- Stock an item");
	puts("5- Add new item or update item");
	puts("6- Delete item");
	puts("7- Search by name");
	puts("8- Sort Items");
	puts("0- Exit program");
	printf("> ");
	scanf("%d", &answer);
	while (answer < 0 || answer > 8)
	{
		printf("Invalid value, 0 < value < 8: ");
		clrKyb();
		scanf("%d", &answer);
	}
	clrKyb();

	return answer;
}

int yes(void)
{
	char answer;
	printf("(Y)es/(N)o): ");
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

void dspItem(struct Item item, int linear)
{
	//clrKyb();
	if (linear)
	{
		printf("|%d|%-20s|%8.2lf|  %3s| %3d | %3d |%12.2lf|", item.sku, item.name, item.price, item.isTaxed ? "Yes" : "No", item.quantity, item.minQuantity, item.isTaxed ? item.price * item.quantity + item.price * item.quantity * TAX : item.price * item.quantity);
		item.quantity <= item.minQuantity ? printf("***\n") : printf("\n");
	}
	else
	{
		if (item.quantity <= item.minQuantity)
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

void GrocInvSys(void)
{
	int selection;
	struct Item item[MAX_ITEM_NO];
	int index = 0;

	welcome();
	if (!loadItems(item, DATAFILE, &index)) // read failed
	{
		printf("Could not read from %s.\n", DATAFILE);
	}
	do
	{
		selection = menu();
		switch (selection)
		{
		case 1:
			//puts("List Items!");
			listItems(item, index);
			pause();
			break;
		case 2:
			//puts("Search Items!");
			search(item, index);
			pause();
			break;
		case 3:
			//puts("Checkout Item!");
			adjustQty(item, index, CHECKOUT);
			if (saveItems(item, DATAFILE, index))
			{
				//printf("could not update data file %s\n", DATAFILE);
			}
			pause();
			break;
		case 4:
			//puts("Stock Item!");
			adjustQty(item, index, STOCK);
			if (saveItems(item, DATAFILE, index))
			{
				//printf("could not update data file %s\n", DATAFILE);
			}
			pause();
			break;
		case 5:
			//puts("Add/Update Item!");
			addOrUpdateItem(item, &index);
			if (saveItems(item, DATAFILE, index))
			{
				//printf("could not update data file %s\n", DATAFILE);
			}
			pause();
			break;
		case 6:
			//puts("Delete Item!");
			deleteItem(item, &index);
			pause();
			break;
		case 7:
			//puts("Search by name!");
			searchByName(item, index);
			pause();
			break;
		case 8:

			sort(item, index);
			pause();
			break;
		case 0:
			printf("Exit the program? ");
			if (yes())
			{
				selection = -1;
			}

			break;
		}
	} while (selection != -1);

}


/*End of milestone 1 to 4 functions
*********************************************************************/








/* ms5 Tester output

***********Testing saveItem:
Your saveItem saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItem!


Press <ENTER> to continue...
***********Testing loadItem:
Your loadItem loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItem!


Press <ENTER> to continue...
***********Testing saveItems:
Your saveItems saved the following in test.txt:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
*******************************
They have to match the following:
275,10,2,4.40,0,Royal Gala Apples
386,20,4,5.99,0,Honeydew Melon
240,30,5,3.99,0,Blueberries
***********END Testing saveItems!


Press <ENTER> to continue...
***********Testing loadItems:
Your loadItems loaded the following from test.txt:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
*******************************
They have to match the following:
|275|Royal Gala Apples   |    4.40|   No|  10 |   2 |       44.00|
|386|Honeydew Melon      |    5.99|   No|  20 |   4 |      119.80|
|240|Blueberries         |    3.99|   No|  30 |   5 |      119.70|
***********END Testing loadItems!


Press <ENTER> to continue...
Done!


*/
