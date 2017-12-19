/* marks.c */
/*
	Name : Youngmin Kim
	I  D : 109-161-158
*/
#include <stdio.h>

int main()
{
	int select,count=1,inputNum,lowestScore=49,highestScore=50,highStudent=0,lowStudent=0;
	float passScore = 0, failScore = 0, passAve,failAve, allAve;

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

	do
	{
		printf("%d> ", count);
		scanf("%d", &inputNum);
		if (inputNum > 100 || inputNum < 0)
			printf("Error: Enter values between 0 and 100 inclusive.\n");
		else
		{
			if (inputNum >= 50)
			{
				passScore += inputNum;
				highStudent++;
				if (inputNum > highestScore)
					highestScore = inputNum;
			}
			else
			{
				failScore += inputNum;
				lowStudent++;
				if (lowestScore > inputNum)
					lowestScore = inputNum;
			}
			count++;
		}
	} while (count <= select);

	passAve = passScore / highStudent;
	failAve = failScore / lowStudent;
	allAve = (passScore + failScore) / select;
	printf("Total of %d students passed with an average of %.1f.\n", highStudent, passAve);
	printf("Total of %d students failed with an average of %.1f.\n", lowStudent, failAve);
	printf("Highest mark in group: %d\n", highestScore);
	printf("Lowest mark in group: %d\n", lowestScore);
	printf("The average of all marks in this group is %.1f.\n",allAve);
	printf("Program Ended.\n");

	return 1;
}
