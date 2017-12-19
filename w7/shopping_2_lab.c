
#include <stdio.h>

#define MAX_ITEMS 10
struct Item {
       int _sku;
       float _price;
       int _quantity;
};


void displayInventory(const struct Item items[],const int size);
void clear()
{
	int i = 0;
	for (i = 0; i < 20; i++)
		printf("\n");
}
int validate(const int low, const int high)
{
	int answer;
	printf("Select: ");
	scanf("%d", &answer);
	while (!(low<=answer && answer <= high))
	{
		printf("Invalid input, try again: ");
		scanf("%d", &answer);
	}

	return answer;
}
void displayInventory(const struct Item items[],const int size)
{
	int i;
	printf("\n\nInventory\n");
	printf("=========================================\n");
	printf("Sku         Price       Quantity\n");
	for (i = 0; i < size; i++)
	{
		printf("%d        %.2f       %d\n", items[i]._sku, items[i]._price, items[i]._quantity);
	}
	printf("=========================================\n");
}
int searchInventory(const struct Item items[], const int sku_item, const int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (items[i]._sku == sku_item)
			return i;
	}
	return -1;
}
void addItem(struct Item items[], int *size)
{
	int skuNum,quant,searching;
	float price;
	printf("Please input a SKU number: ");
	scanf("%d", &skuNum);
	printf("Quantity: ");
	scanf("%d", &quant);
	searching = searchInventory(items, skuNum, *size);
	if (searching == -1)
	{// not found
		if (!(*size == MAX_ITEMS))
		{ // not full so add
			printf("Price: ");
			scanf("%f", &price);
			items[*size]._sku = skuNum;
			items[*size]._quantity = quant;
			items[*size]._price = price;
			*size+=1;
			printf("The item is successfully added to the inventory.\n");
		}
		else
		{ // full
			printf("Inventory is full\n");
		}
	}
	else // found so update
	{
		puts("The item exists in the repository, quantity is updated.");
		items[searching]._quantity += quant;
	}
}
void menu()
{
	printf("Please select from the following options:\n");
	puts("1) Display the inventory.");
	puts("2) Add to the inventory.");
	puts("3) Check price.");
	puts("4) Clear Screen.");
	puts("0) Exit.");
}
void checkPrice()
{

}



int main(){
	struct Item item[MAX_ITEMS];
	int size = 0;
	clear();
	printf("Welcome to the Shop\n");
	puts("===================");
	while (1) {
		menu();
		switch (validate(0, 3))
		{
		case 0: puts("Goodbye!");
			return 0;
		case 1:
			displayInventory(item, size);
			break;
		case 2:
			addItem(item, &size);
			break;
		case 3:
			checkPrice();
			break;
		case 4:
			clear();
			break;
		}
	}
	return 0;
}


/* output:




















Welcome to the Shop
===================
Please select from the following options:
1) Display the inventory.
2) Add to the inventory.
3) Check price.
4) Clear Screen.
0) Exit.
Select: 5
Invalid input, try again: 2
Please input a SKU number: 1234
Quantity: 2
Price: 45.63
The item is successfully added to the inventory.
Please select from the following options:
1) Display the inventory.
2) Add to the inventory.
3) Check price.
4) Clear Screen.
0) Exit.
Select: 2
Please input a SKU number: 9010
Quantity: 5
Price: 23.50
The item is successfully added to the inventory.
Please select from the following options:
1) Display the inventory.
2) Add to the inventory.
3) Check price.
4) Clear Screen.
0) Exit.
Select: 2
Please input a SKU number: 1234
Quantity: 5
The item exists in the repository, quantity is updated.
Please select from the following options:
1) Display the inventory.
2) Add to the inventory.
3) Check price.
4) Clear Screen.
0) Exit.
Select: 1


Inventory
=========================================
Sku         Price       Quantity
1234        45.63       7
9010        23.50       5
=========================================
Please select from the following options:
1) Display the inventory.
2) Add to the inventory.
3) Check price.
4) Clear Screen.
0) Exit.
Select: 0
Goodbye!
*/


