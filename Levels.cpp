#include <iostream>
#include <ios>
#include <Windows.h>
#define N 200

void TestInp(int rows, int cols, char lev[N][N]);
void Show_Level(int &rows, int &cols, char lev[N][N], char data[N][N], HANDLE handle);
void TestWrite(int rows, int cols, char lev[N][N], char name[]);
void TestRead(int &rows, int &cols, char lev[N][N], char name[]);
void color();

int main()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("chcp 1251");
	system("cls");
	int rows = 30, cols = 30;
	char lev[N][N];
	char data[N][N];
	//color();
	//TestInp(rows, cols, lev);
	TestRead(rows, cols, lev, "2.txt");
	TestRead(rows, cols, data, "2.2.txt");
	Show_Level(rows, cols, lev, data, handle);
	//TestWrite(rows, cols , lev,"TO2.txt");

	system("pause");
	return 0;
}

void TestInp(int rows, int cols, char lev[N][N])
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			lev[i][j] = '#';
	}
}

void TestWrite(int rows, int cols, char lev[N][N], char name[])
{
	FILE* TestLev;
	if (fopen_s(&TestLev, name, "w+") != 0)
	{
		printf("ERROR");
		system("pause");
		exit(1);
	}
	fprintf(TestLev, "%i\n", rows+1);
	fprintf(TestLev, "%i\n", cols);
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
			fprintf(TestLev, "%c", lev[i][j]);
		fprintf(TestLev, "\n");
	}
	fclose(TestLev);
}

void TestRead(int &rows, int &cols, char lev[N][N], char name[])
{
	FILE* TestLev;
	if (fopen_s(&TestLev, name, "r+") != 0)
	{
		printf("ERROR");
		system("pause");
		exit(1);
	}
	fscanf_s(TestLev, "%i", &rows);
	fscanf_s(TestLev, "%i\r", &cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fscanf_s(TestLev, "%c", &lev[i][j]);
	}
	fclose(TestLev);
}

void color()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int k = 1; k < 255; k++)
	{
		SetConsoleTextAttribute(hConsole, k);
		printf("Öâåò = %i", k);
		SetConsoleTextAttribute(hConsole, 15);
		printf("\n");
	}
}

void Show_Level(int &rows, int &cols, char lev[N][N], char data[N][N], HANDLE handle)
{
	for (int i = 0; i <rows; i++)
	{
		for (int j = 0; j < cols; j++)
			switch (data[i][j]) 
			{
			case '\n':
				SetConsoleTextAttribute(handle, 15);
				printf("\n");
				break;
			case ' ':
				SetConsoleTextAttribute(handle, 15);
				printf(" ");
				break;
			case 'K':
				SetConsoleTextAttribute(handle, 14);
				printf("K");
				break;
			case 'P':
				SetConsoleTextAttribute(handle, 15);
				printf("@");
				break;
			case 'C':
				SetConsoleTextAttribute(handle, 14);
				printf("D");
				break;
			case '1':
				SetConsoleTextAttribute(handle, 12);
				printf("§");
				break;
			case '2':
				SetConsoleTextAttribute(handle, 13);
				printf("¤");
				break;
			case '0':
				switch (lev[i][j]) 
				{
					case' ':
						SetConsoleTextAttribute(handle, 15);
						printf(".");
						break;
					case '¶':
						SetConsoleTextAttribute(handle, 2);
						printf("%c", lev[i][j]);
						break;
					case 'D':
						SetConsoleTextAttribute(handle, 15);
						printf("%c", lev[i][j]);
						break;
				}
				break;
			case 'W':
				switch(lev[i][j])
				{		
					case '^':
						SetConsoleTextAttribute(handle,8);
						printf("%c", lev[i][j]);
					break;
					case '~':
						SetConsoleTextAttribute(handle, 159);
						printf("%c", lev[i][j]);
						break;
					default: 
						SetConsoleTextAttribute(handle, 8);
						printf("%c",lev[i][j]);
						break;	
				}
				break;
			}
		}
	SetConsoleTextAttribute(handle, 15);
	printf("\n");
}

int Randomize(int a, int b)
{
	return rand() % (b - a + 1) + a;
}