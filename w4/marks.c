/* marks.c */
/*
Name : Youngmin Kim
I  D : 109-161-158
*/
#include <stdio.h>

int main()
{
	int select, i;
	float sum = 0, average;
	int students[40];
	int marks[40];
	printf("       ---=== IPC mark Analyser V2.0 ===---\n");
	printf("Please enter the number of students(between 3 and 40): ");
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

	printf("Row   Std No  Mrk\n--- --------- ---\n");

	for (i = 0; i < select; i++)
	{
		printf("    _________ ___\r  %d ", i+1);
		scanf("%d", &students[i]);
		scanf("%d", &marks[i]);
		sum += marks[i];
	}
	printf("=================\n");
	printf("Marks Entered, printing results:\n");
	printf("Row   Std No  Mrk\n--- --------- ---\n");
	for (i = 0; i < select; i++)
	{
		printf("%03d %09d  %d\n",i+1, students[i], marks[i]);
	}
	printf("=================\n");
	average = (float)(sum / select);
	printf("The average of all marks in this group is %.1f.\nProgram Ended.\n", average);
	return 1;
}


/* the output
       ---=== IPC mark Analyser V2.0 ===---
Please enter the number of students(between 3 and 40): 2
Invalid number, enter a number between 3 and 40 inclusive: 41
Invalid number, enter a number between 3 and 40 inclusive: 5
Row   Std No  Mrk
--- --------- ---
  1 123456789 45_
  2 456789123 90_
  3 789123456 57_
  4 147258369 89_
  5 014725836 32_
=================
Marks Entered, printing results:
Row   Std No  Mrk
--- --------- ---
001 123456789  45
002 456789123  90
003 789123456  57
004 147258369  89
005 014725836  32
=================
The average of all marks in this group is 62.6.
Program Ended.
*/
