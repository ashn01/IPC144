#include <stdio.h>

#define MAX_ITEMS 10

struct Item {
	int sku_;
	float price_;
	int quantity_;
};

int main(){

	struct Item item[MAX_ITEMS];
	struct Item temporary;
	int size = 0;
	int selection;
	int checkEx=-1;
	int i;
	int loop = 0;
	printf("Welcome to the Shop\n===================\n");

	while (loop == 0) {
		checkEx = -1;
		printf("Please select from the following options:\n");
		printf("1) Display the inventory.\n");
		printf("2) Add to shop.\n");
		printf("0) Exit.\n");
		printf("Select:");
		scanf("%d", &selection);
		switch (selection)
		{
		case 1:
			printf("\n\n");
			printf("Inventory\n");
			printf("=========================================\n");
			printf("Sku         Price       Quanity\n");
			for (i = 0; i < size; i++)
			{
				printf("%d        %.2f       %d         \n",item[i].sku_,item[i].price_,item[i].quantity_);
			}
			printf("=========================================\n");
			break;
		case 2:
			printf("Please input a SKU number:");
			scanf("%d",&temporary.sku_);
			printf("Quantity:");
			scanf("%d", &temporary.quantity_);

			for (i = 0; i < size; i++)
			{
				if (item[i].sku_ == temporary.sku_)
				{
					checkEx = i;
				}
			}

			if (checkEx == -1)
			{
				printf("Price:");
				scanf("%f", &temporary.price_);

				item[size].sku_ = temporary.sku_;
				item[size].price_ = temporary.price_;
				item[size].quantity_ = temporary.quantity_;

				printf("The item is successfully added to the inventory.\n");
				size++;
			}
			else
			{
				item[checkEx].quantity_ += temporary.quantity_;
				printf("The item exists in the repository, quanity is updated.\n");
			}
			break;
		case 0:
			printf("Good bye!\n");
			loop++;
			break;
		default:
			printf("Invalid input, try again: ");
		}
	}


	return 0;
}

/*
Welcome to the Shop
===================
Please select from the following options:
1) Display the inventory.
2) Add to shop.
0) Exit.
Select:8
Invalid input, try again: Please select from the following options:
1) Display the inventory.
2) Add to shop.
0) Exit.
Select:2
Please input a SKU number:2341
Quantity:3
Price:12.78
The item is successfully added to the inventory.
Please select from the following options:
1) Display the inventory.
2) Add to shop.
0) Exit.
Select:2
Please input a SKU number:4567
Quantity:9
Price:98.2
The item is successfully added to the inventory.
Please select from the following options:
1) Display the inventory.
2) Add to shop.
0) Exit.
Select:1


Inventory
=========================================
Sku         Price       Quanity
2341        12.78       3
4567        98.20       9
=========================================
Please select from the following options:
1) Display the inventory.
2) Add to shop.
0) Exit.
Select:2
Please input a SKU number:2341
Quantity:5
The item exists in the repository, quanity is updated.
Please select from the following options:
1) Display the inventory.
2) Add to shop.
0) Exit.
Select:1


Inventory
=========================================
Sku         Price       Quanity
2341        12.78       8
4567        98.20       9
=========================================
Please select from the following options:
1) Display the inventory.
2) Add to shop.
0) Exit.
Select:0
Good bye!
*/
