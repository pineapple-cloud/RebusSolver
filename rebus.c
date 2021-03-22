#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#define MAX 10
#define MAX_LENGTH 100
#define MAX_WORDS 7
#define ZERO 48
#define NINE 57
#define A 65
#define Z 90
#define a 97
#define z 122
#define NOT_FOUND -1

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

char getLetter(char* str, char words[][MAX_LENGTH], char* answer)
{
	char letter = 0;
	char c = 0;
	int found = 0;
	int strlenWords[MAX_WORDS];
	for (int i = 0; i < MAX_WORDS && words[i][0]; i++)
		strlenWords[i] = strlen(words[i]);
	int strlenAnswer = strlen(answer);

	for (int i = 1; !found; i++)
	{
		for (int j = 0; words[j][0] && !found; j++)
		{

			c = words[j][strlenWords[j] - i];
			if ((A <= c && c <= Z) || (a <= c && c <= z))
			{
				letter = c;
				found = 1;
			}
		}
		c = answer[strlenAnswer - i];
		if ((A <= c && c <= Z) || (a <= c && c <= z))
		{
			letter = c;
			found = 1;
		}
	}
	return letter;
}
int checkWordBeginning(char c, char* str)
{
	if (str[0] == c)
		return 1;
	int i = 1;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] == ' ')
			return 1;
		i++;
	}
	return 0;
}
int findNum(char* str, LetterAndValue* LetterAndValue_list)
{
	for (int j = 0; j <= MAX; j++)
	{
		if (LetterAndValue_list[j].c == str) return LetterAndValue_list[j].v;
	}
	return NOT_FOUND;
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
			if (num != NOT_FOUND)
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
void tokeniseString(char* str, char words[][MAX_LENGTH], char* answer)
{
	int i = 0;
	int j = 0;
	int wordsCount = 0;
	for (i; str[i] != '='; i++)
	{
		if ((ZERO <= str[i] && str[i] <= NINE) || (A <= str[i] && str[i] <= Z) || (a <= str[i] && str[i] <= z))
		{
			words[wordsCount][j] = str[i];//массив из слагаемых
			j++;
		}
		if (str[i] == '+')
		{
			wordsCount++;//колличество слагаемых
			j = 0;
		}
	}
	j = 0;
	for (i; str[i] != '\0'; i++)//сохраняем "число" после = в answer
	{
		if ((ZERO <= str[i] && str[i] <= NINE) || (A <= str[i] && str[i] <= Z) || (a <= str[i] && str[i] <= z))
		{
			answer[j] = str[i];
			j++;
		}
	}

}
void checkReady(char* str, char words[][MAX_LENGTH], char* answer, bool* still_Letters, bool* success, int* tries, int* wordsLen, int answerLen)
{

	int sumNum[MAX_WORDS] = { 0 }; int sumAnswer = 0;
	char c; char digit[2] = { '\0' };
	int minDigits = 0;
	for (int i = 1; *still_Letters==0 && i <= answerLen; i++)
	{
		for (int j = 0; *still_Letters==0 && words[j][0]; j++)
		{
			c = words[j][wordsLen[j] - i];
			if (ZERO <= c && c <= NINE)//если число
			{
				digit[0] = c;
				sumNum[j] += atoi(digit) * (int)pow(10, minDigits);

			}
			if ((A <= c && c <= Z) || (a <= c && c <= z))//если буква
			{
				*still_Letters = 1;
			}
		}
		c = answer[answerLen - i];
		if (ZERO <= c && c <= NINE)
		{
			digit[0] = c;
			sumAnswer += atoi(digit) * (int)pow(10, minDigits);
		}
		if ((A <= c && c <= Z) || (a <= c && c <= z))
		{
			*still_Letters = 1;
		}
		if (*still_Letters == 0)//если не было ни одной буквы в проверяемом разряде слов и ответа
		{
			minDigits++;
		}
	}
	int sumAll = 0;
	for (int i = 0; i < MAX_WORDS; i++)
	{
		sumAll += sumNum[i];
	}
	if (!minDigits)
		*success = true;
	if (*still_Letters==0)
	{
		if (sumAll == sumAnswer)
			*success = true;
	}
	else
	{ 
		int numDivider = (int)pow(10, minDigits);
		if (sumAll % numDivider == sumAnswer % numDivider)
			*success = true;
	}
	(*tries)++;
}
char* solveExpression(char* str, LetterAndValue* LetterAndValue_list, int* tries, int* wordsLen, int answerLen)
{
	static char strNumbers[MAX_LENGTH];
	char* result = NULL;
	bool success = false;
	bool still_Letters = 0;
	static char words[MAX_WORDS][MAX_LENGTH] = { 0 };
	static char answer[MAX_LENGTH] = { 0 };

	strncpy(strNumbers, str, strlen(str) + 1);
	tokeniseString(strNumbers, words, answer);
	checkReady(strNumbers, words, answer, &still_Letters, &success, tries, wordsLen, answerLen);
	if (success)
	{

		if (still_Letters==0) 
		{
			return strNumbers;
		}
	}
	else return 0;

	char letter;
	letter = getLetter(strNumbers, words, answer);
	if (letter == '\0') return 0;
	int count = 0;
	for (count; count <= 10; count++)
	{
		if (LetterAndValue_list[count].c == NULL)
		{
			LetterAndValue_list[count].c = letter;
			LetterAndValue_list[count].v = count;
		}
		else continue;

		StringReplacement(str, strNumbers, LetterAndValue_list, LETTERS_TO_NUMBERS);
		result = (solveExpression(strNumbers, LetterAndValue_list, tries, wordsLen, answerLen));
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
	char string[MAX_LENGTH]; int wordsLen[MAX_WORDS]; static char words[MAX_WORDS][MAX_LENGTH] = { 0 };
	static char answer[MAX_LENGTH] = { 0 };
	int answerLen;
	int tries = 0;
	LetterAndValue LetterAndValue_list[MAX];
	list_init(&LetterAndValue_list);
	clock_t start, stop;
	printf("%s\n", "Enter expression:");
	gets(string);
	//strcpy(string,"BIG + CAT = LION");
	tokeniseString(string, words, answer);//рабиваем строку на массив слагаемых и answer
	for (int i = 0; i < MAX_WORDS && words[i][0]; i++)
	{
		wordsLen[i] = strlen(words[i]);//массив длин каждого слова
	}
	answerLen = strlen(answer);
	start = clock();
	char str[1024];
	printf("%s\n", solveExpression(string, LetterAndValue_list, &tries, wordsLen, answerLen));
	stop = clock();
	printf("Number of tries: %d\n", tries);
	printf("execution took %.3f seconds", ((float)(stop - start) / CLK_TCK));
}