#include <stdio.h>
#include <string.h>

void generatePassword(char pass[], char name[])
{
	int i = 0;
	for (i = 0; i < strlen(name); i++)
	{
		pass[i] = name[i] - 1;
	}
	pass[strlen(name)] = '\0';
}

int main(void)
{
	char name[9];
	char pass[9];
	char guess[9];
	char backup[9];

	printf("Password Game\n");
	printf("=============\n");
	printf("Enter your name (up to 8 characters): ");
	scanf("%s", name);

	strcpy(backup, name);
	generatePassword(pass, name);


	printf("WELCOME %s\n", name);

	do {
		if (strlen(name) != strlen(backup))
			printf("FALSE: ");
		printf("Guess the password (up to 8 characters) %s: ", name);
		scanf("%s", guess);
		if (!strcmp(pass, guess))
		{
			printf("You got it, %s!!!\n", backup);
			break;
		}
		name[strlen(name) - 1] = '\0';

	} while (strlen(name) != 0);

	printf("Game Over!\n");
	return 0;
}
