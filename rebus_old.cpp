#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MAX 10
#define MAX_LENGTH 1000
typedef struct
{
	int v;
	char c;
} LetterAndValue;

enum
{
	LETTERS_TO_NUMBERS,
	NUMBERS_TO_LETTERS
};

char getLetter(char* str)
{
	char c; int i = 0;
	for (i = 0; i <= strlen(str); i++)
	{

		if (isalpha(str[i]) || str[i] == '\0')
		{
			c = str[i];
			break;
		}

	}
	return c;
}
int findNum(char* str, LetterAndValue* LetterAndValue_list)
{
	for (int j = 0; j <= MAX; j++)
	{
		if (LetterAndValue_list[j].c == str) return LetterAndValue_list[j].v;
	}
	return -1;
}
void StringReplacement(char* strLetters, char* strNumbers, LetterAndValue* LetterAndValue_list, int operation)
{
	switch (operation)
	{
		int num;
	case LETTERS_TO_NUMBERS:
	{
		char c[2] = { '\0' };
		for (int i = 0; strLetters[i] != '\0'; i++)
		{
			num = findNum(strLetters[i], LetterAndValue_list);
			if (num != -1)
			{
				_itoa(num, c, 10);
				strNumbers[i] = c[0];
			}

		}
		break;
	}
	case NUMBERS_TO_LETTERS:
	{
		char l[2] = { '\0' };
		num = findNum(strLetters, LetterAndValue_list);
		_itoa(num, l, 10);
		for (int i = 0; strNumbers[i] != '\0'; i++)
			if (strNumbers[i] == l[0]) strNumbers[i] = strLetters;
	}
	break;
	}
}
int ReadyString(char* str, bool* success, int* tries)
{
	int n = 0; int answer = 0; char digit[2]; int numbers[7] = { 0 }; int i = 0;
	for (i; str[i] != '='; i++)
	{
		if (isalpha(str[i])) return 0;
		if (str[i] == '+') n++;
		if (isdigit(str[i]))
		{
			digit[0] = str[i];
			numbers[n] = numbers[n] * 10 + atoi(digit);
		}
	}
	for (i; str[i] != '\0'; i++)
	{
		if (isalpha(str[i]))
			return 0;
		if (isdigit(str[i]))
		{
			digit[0] = str[i];
			answer = answer * 10 + atoi(digit);
		}
	}
	int sum = 0;
	for (int i = 0; i < n + 1; i++)
		sum += numbers[i];
	if (sum == answer)
		*success = 1;
	(*tries)++;
	return 1;
}
char* solve(char* str, LetterAndValue* LetterAndValue_list, int* tries)
{

	char strNumbers[MAX_LENGTH]; char* result = NULL;
	bool success = false;
	strncpy(strNumbers, str, strlen(str) + 1);
	if (ReadyString(strNumbers, &success, tries) == 1)//проверка на наличие букв и если букв в выражении не осталось на верность решения выражения
	{
		if (success) return strNumbers;
		else return 0;
	}
	char letter;
	letter = getLetter(strNumbers, &isbegining);//получаем первую букву, которая ещё не была поменяна на цифру

	for (; findNum(letter, LetterAndValue_list) != -1;)//ищем цифру соответствующую этой букву в LetterAndValue_list
	{
		letter = getLetter(strNumbers);
		if (letter == '\0') return 0;
	}

	int count = 0;
	if (isbegining)
		count = 1;
	printf("%d\n", isbegining);
	printf("%s\n", str);
	for (count; count <= 10; count++)
	{

		if (LetterAndValue_list[count].c == NULL)
		{
			LetterAndValue_list[count].c = letter;
			LetterAndValue_list[count].v = count;
		}
		else continue;

		StringReplacement(str, strNumbers, LetterAndValue_list, LETTERS_TO_NUMBERS);//меняем буквы на цифры
		
		result = (solve(strNumbers, LetterAndValue_list, tries));
		if (!result)
		{
			StringReplacement(letter, strNumbers, LetterAndValue_list, NUMBERS_TO_LETTERS);
			LetterAndValue_list[count].c = NULL;
			LetterAndValue_list[count].v = NULL;
		}
	}
	return result;
}

void list_init(LetterAndValue* LetterAndValue_list)
{
	for (size_t i = 0; i < MAX; i++)
	{
		LetterAndValue_list[i].c = NULL;
		LetterAndValue_list[i].v = NULL;
	}
}
int main()
{
	char string[MAX_LENGTH];
	int tries = 0;
	LetterAndValue LetterAndValue_list[MAX];//отвечает за соответствие букв и цифр
	list_init(&LetterAndValue_list);
	clock_t start, stop;
	printf("%s\n", "Enter expression:");
	gets(string);
	start = clock();
	printf("%s\n", solve(string, LetterAndValue_list, &tries));
	stop = clock();
	printf("Number of tries: %d\n", tries);
	printf("execution took %.3f seconds", ((float)(stop - start) / CLK_TCK));
}