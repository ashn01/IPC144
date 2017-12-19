/* marks.c */
/*
	Name : Youngmin Kim
	I  D : 109-161-158
*/
#include <stdio.h>

int main()
{
	int select,i,inputNum;
	float sum=0,average;
	printf("       ---=== IPC mark Analyser ===---\n");
	printf("Please enter the number of marks(between 3 and 40): ");
	scanf("%d", &select);
	
	while (1)
	{
		if (select < 3 || select > 40)
		{
			printf("Invalid number, enter a number between 3 and 40 inclusive: ");
			scanf("%d", &select);
		}
		else
			break;
	}

	for (i = 1; i <= select; i++)
	{
		printf("%d> ", i);
		scanf("%d", &inputNum);
		sum += inputNum;
	}
	average = (float)(sum / select);
	printf("The average of all marks in this group is %.1f.\nProgram Ended.\n", average);
	return 1;
}
