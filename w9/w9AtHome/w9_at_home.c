// Workshop 9 - Files

#include <stdio.h>
#include <stdlib.h>
// Name: Youngmin Kim
// Student #: 109 161 158


struct Box{
	int id;			// the box ID
	double size[3];	// dimensions of the box (Length, Width, Height)
	double weight;	// weight of the box
};

void listBoxes(const char filename[])	// lists all boxes in the file
{
	struct Box temp;
	FILE *fp= NULL;

	fp = fopen(filename,"r");

	if (fp != NULL)
	{
		printf("ID Length Width Height Weight\n-----------------------------\n");
		while (fscanf(fp, "%d%lf%lf%lf%lf",&temp.id,&temp.size[0],&temp.size[1],&temp.size[2],&temp.weight) != EOF)
		{
			printf("%2d %6.2lf %5.2lf %6.2lf %6.2lf\n", temp.id, temp.size[0], temp.size[1], temp.size[2], temp.weight);
		}
		printf("\n");

		fclose(fp);
	}
	else // error
	{
		printf("ERR : Failed to open file.\n");
	}
}
void printBox(struct Box b);			// print one box- already implemented for you

// returns the record number of a box with specified ID, if found  
int searchBox(FILE *fp, int id2Find)
{
	struct Box temp;
	//FILE *tfp = fp; 

	if (fp != NULL)
	{
		rewind(fp);
		while (fscanf(fp, "%d%lf%lf%lf%lf", &temp.id, &temp.size[0], &temp.size[1], &temp.size[2], &temp.weight) != EOF)
		{
			if (temp.id == id2Find)
				return temp.id;
		}
		return -1;
	}
	else
	{
		return -1;
	}
}


void displayBox(const char filename[], int id2Find)		// display a box, given ID
{
	struct Box temp;
	FILE *fp = NULL;
	int index = 0;

	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		if (searchBox(fp, id2Find) == id2Find)
		{
			index++;
			rewind(fp);
			while (fscanf(fp, "%d%lf%lf%lf%lf", &temp.id, &temp.size[0], &temp.size[1], &temp.size[2], &temp.weight) != EOF)
			{
				if (temp.id == id2Find)
				{
					printf("Found box %d as record #%d\n", temp.id, index);
					printBox(temp);
					break;
				}
			}
		}
		else
		{
			printf("This box is not recorded.\n\n");
		}
		fclose(fp);
	}
	else
		printf("ERR : Failed to open file.\n");
}
int addBox(const char filename[], const struct Box * b2Add)// add a box to file
{
	FILE *fp = NULL;
	fp = fopen(filename, "a+");
	if (fp != NULL)
	{
		if (searchBox(fp, b2Add->id) != -1)
		{
			printf("A box with this ID is already recorded.\n");
			return 0;
		}
		else
		{
			fprintf(fp, "%d %.2lf %.2lf %.2lf %.2lf\n", b2Add->id, b2Add->size[0], b2Add->size[1], b2Add->size[2], b2Add->weight);
			fclose(fp);	
			return 1;
		}
	}
	else
	{
		printf("ERR : Failed to open file.\n");
	}
	return 0;
}

int numberBoxes(const char filename[])		// find the number of boxes in a file
{
	FILE *fp = NULL;
	struct Box temp;
	int counter = 0;
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fscanf(fp, "%d%lf%lf%lf%lf", &temp.id, &temp.size[0], &temp.size[1], &temp.size[2], &temp.weight) != EOF)
		{
			counter++;
		}
		fclose(fp);
	}
	else
	{
		printf("ERR : Failed to open file.\n");
	}

	return counter;

}
int getRandomInt(int lower, int higher)	// get a random number
{
	int r;
	r = rand() % higher+1;
	return r;
}
void displayBoxN(char filename[], int n)	// display a box given its record number
{
	FILE *fp = NULL;
	struct Box temp;
	int count = 1;
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fscanf(fp, "%d%lf%lf%lf%lf", &temp.id, &temp.size[0], &temp.size[1], &temp.size[2], &temp.weight) != EOF)
		{
			if (count == n)
			{
				printBox(temp);
			}
			count++;
		}
		fclose(fp);

	}
	else
		printf("ERR : Failed to open file.\n");

}

void printBox(struct Box b){
	printf("\nID:     %6d\n"
		"Length: %6.2lf\n"
		"Width:  %6.2lf\n"
		"Height: %6.2lf\n"
		"Weight: %6.2lf\n\n", b.id, b.size[0], b.size[1], b.size[2], b.weight);
}

int menu(void){
	int choice = -1;

	printf("1- List all boxes\n");
	printf("2- Find a box\n");
	printf("3- Add a box\n");
	printf("4- Randomly pick a lucky box!\n");
	printf("0- Exit program\n");

	printf("Select an option: ");
	do{
		scanf("%d", &choice);
		if (choice < 0 || choice > 4)
			printf("Please enter a number between 0 and 4: ");
	} while (choice < 0 || choice > 4);
	return choice;
}


int main(void){

	int choice; // , boxID, r;
	int temp;
	char filename[] = "storage.txt";
	struct Box b;
	FILE *fp;

	printf("Welcome to My Storage Room\n");
	printf("==========================\n");
	do {
		// get user's choice
		choice = menu();
		fp = fopen(filename,"r");
		if(fp != NULL)
		{	
			fclose(fp);
		}
		switch (choice){
		case 1:
			// IN_LAB: list items
			printf("List of boxes\n=============\n\n");
			listBoxes(filename);


			break;

		case 2:
			// IN_LAB: find a box given its ID
			// ask for ID
			printf("Enter box ID: ");
			scanf("%d",&choice);


			// call displayBox
			displayBox(filename,choice);


			break;

		case 3:
			// AT_HOME: add a box
			// get user input for box's ID, size and weight
			printf("Please enter the box's ID, length, width, height and weight: ");
			scanf("%d %lf %lf %lf %lf",&b.id, &b.size[0], &b.size[1], &b.size[2], &b.weight);

			// call addBox, print message to show number of boxes added
			temp = addBox(filename,&b);
			printf("%d box added to storage!\n\n", temp);


			break;

		case 4:
			// AT_HOME: randomly pick a lucky box
			//srand(time(NULL));


			// choose a random number between 1 and the number of boxes in storage
			//getRandomInt(1, numberBoxes(filename));

			// display the lucky box!
			printf("\nLucky box picked:\n");
			displayBoxN(filename,getRandomInt(1, numberBoxes(filename)));


			break;


		};

	} while (choice > 0);

	return 0;
}

/*
Welcome to My Storage Room
==========================
1- List all boxes
2- Find a box
3- Add a box
4- Randomly pick a lucky box!
0- Exit program
Select an option: 1
List of boxes
=============

ID Length Width Height Weight
-----------------------------
10  50.34 61.00  30.00  50.50
11  25.60 12.34   9.23  12.89
55  10.00 20.00  30.00  40.50
56  30.00 40.00  50.00  60.00
57   5.20  6.30   7.40   8.50

1- List all boxes
2- Find a box
3- Add a box
4- Randomly pick a lucky box!
0- Exit program
Select an option: 2
Enter box ID: 55
Found box 55 as record #3:

ID:         55
Length:  10.00
Width:   20.00
Height:  30.00
Weight:  40.50

1- List all boxes
2- Find a box
3- Add a box
4- Randomly pick a lucky box!
0- Exit program
Select an option: 2
Enter box ID: 15
This box is not recorded.

1- List all boxes
2- Find a box
3- Add a box
4- Randomly pick a lucky box!
0- Exit program
Select an option: 0
*/
