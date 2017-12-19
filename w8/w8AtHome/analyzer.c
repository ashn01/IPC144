
#include <stdio.h>
#define MAX 100

struct studentMarks {
   int   id;
   float marks;
};

void welcome(void);
int get_data( struct studentMarks * ptr );
void show( struct studentMarks list[], int num );
float analyze(struct studentMarks list[], int num, float* ptr_highest, float* ptr_lowest);
void print_summary(float avg, float high, float low);

int main(void){

    // declarations of a constant, an array and variables
	struct studentMarks list[MAX];
	int breakLoop = 0;
	int i = 0;
	float highest=0, lowest=100, ave;

	for (i = 0; i < MAX; i++)
	{
		list[i].id = 0;
		list[i].marks = 0;
	}

    // call a function to display a welcome message
	welcome();

   // 1. use a do-while loop to get student ids and student marks
	do
	{
		breakLoop = get_data(list);
	} while (!breakLoop);

   // 2. print out all the student marks

	show(list, breakLoop);

	// 3. data analysis
	ave = analyze(list, breakLoop, &highest, &lowest);

	// 4. print the result of data analysis
	print_summary(ave,highest,lowest);

    return 0;
}

void welcome(void)
{
	printf("####### Marks Analyzer V3.0 #######\n");
}

int get_data(struct studentMarks * ptr)
{
	struct studentMarks temp;
	int getIndex = 0;
	while (1)
	{
		if (ptr[getIndex].id == 0 && ptr[getIndex].marks == 0)
			break;
		getIndex++;
	}
	if (getIndex < 100)
	{
		printf("Enter student id and marks (e.g. 12345 89.5): ");
		scanf("%d %f", &temp.id, &temp.marks);
		if (temp.id == -1 || temp.marks == -1)
		{
			return getIndex;
		}
		else
		{
			ptr[getIndex].id = temp.id;
			ptr[getIndex].marks = temp.marks;
			return 0;
		}

	}
	else
		return getIndex;
	
}

void show(struct studentMarks list[], int num)
{
	int i;
	for (i = 0; i < num; i++)
		printf("%d. %d, %.2f\n", i + 1, list[i].id, list[i].marks);
}

float analyze(struct studentMarks list[], int num, float* ptr_highest, float* ptr_lowest)
{
	int i = 0;
	float total=0;
	for (i = 0; i < num; i++)
	{
		if (list[i].marks > *ptr_highest)
			*ptr_highest = list[i].marks;
		if (list[i].marks < *ptr_lowest)
			*ptr_lowest = list[i].marks;
		total += list[i].marks;
	}

	return total / i;
}

void print_summary(float avg, float high, float low)
{
	printf("### result of marks analysis ###\n");
	printf("average: %.2f, highest marks: %.2f, lowest marks: %.2f\n", avg, high, low);
}