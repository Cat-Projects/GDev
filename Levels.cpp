#include <iostream>
#include <ios>
#include <Windows.h>
#define N 256
enum {up, down, left, right, use};
struct player { int x, y; };

void View(int x, int y, char map_lev[N][N], char map_obj[N][N], HANDLE handle);
void Player_View(int &rows, int &cols, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N], HANDLE handle);
void Show_Level(int &rows, int &cols, char map_lev[N][N], char map_obj[N][N], HANDLE handle);
void TestWrite(int rows, int cols, char map_lev[N][N], char name[]);
void TestRead(int &rows, int &cols, char map_lev[N][N], char name[]);
void Check(int &y, int &x, char map_obj[N][N], int mov);
void color();

int main()
{
	player p{12,17};

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	system("chcp 1251");
	system("cls");

	int rows, cols;
	char map_lev[N][N];
	char map_obj[N][N];
	char map_fog[N][N];

	//color();
	//TestInp(rows, cols, map_lev);

	TestRead(rows, cols, map_lev, "Lev/Lev3.txt");
	TestRead(rows, cols, map_obj, "Lev/Lev3_obj.txt");
	TestRead(rows, cols, map_fog, "Lev/Lev3_fog.txt");
	Player_View(rows, cols, map_lev, map_obj, map_fog, handle);
	Show_Level(rows, cols, map_lev, map_obj, handle);
	//View(15, 15, map_lev, map_obj, handle);
	//TestWrite(rows, cols , map_lev,"TO2.txt");
	system("pause");
	return 0;
}
	//Функция записи общей геометрии карты *Для тестов
void TestWrite(int rows, int cols, char map_lev[N][N], char name[])
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
			fprintf(TestLev, "%c", map_lev[i][j]);
		fprintf(TestLev, "\n");
	}
	fclose(TestLev);
}

	//Функция загрузки карты *В разработке
void TestRead(int &rows, int &cols, char map_lev[N][N], char name[])
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
			fscanf_s(TestLev, "%c", &map_lev[i][j]);
	}
	fclose(TestLev);
}

	//Функция выведения палитры цветов *Для тестов
void color()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int k = 1; k < 255; k++)
	{
		SetConsoleTextAttribute(hConsole, k);
		printf("Цвет = %i", k);
		SetConsoleTextAttribute(hConsole, 15);
		printf("\n");
	}
}
	
	//Функция отображения карты *В разработке
void Player_View(int &rows, int &cols, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N], HANDLE handle)
{
	for (int i = 0; i <rows; i++)
	{
		for (int j = 0; j < cols; j++)
			switch (map_fog[i][j])
			{
			default:
				SetConsoleTextAttribute(handle, 15);
				printf(" ");
				break;
			case '\n':
				printf("\n");
				break;
			case '1':
				switch (map_obj[i][j]) 
				{
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
				case ' ':
					switch (map_lev[i][j]) 
					{
						case' ':
							SetConsoleTextAttribute(handle, 8);
							printf(".");
							break;
						case '¶':
							SetConsoleTextAttribute(handle, 2);
							printf("%c", map_lev[i][j]);
							break;
						case 'D':
							SetConsoleTextAttribute(handle, 15);
							printf("%c", map_lev[i][j]);
							break;
					}
					break;
					case 'W':
						switch(map_lev[i][j])
						{		
						case '^':
							SetConsoleTextAttribute(handle,7);
							printf("%c", map_lev[i][j]);
							break;
						case ' ':
							SetConsoleTextAttribute(handle, 15);
							printf("#");
							break;
						case '~':
							SetConsoleTextAttribute(handle, 159);
							printf("%c", map_lev[i][j]);
							break;
						default: 
							SetConsoleTextAttribute(handle, 15);
							printf("%c",map_lev[i][j]);
							break;	
				}
				break;
			}
			break;
		}
	}
	SetConsoleTextAttribute(handle, 15);
	printf("\n");
}
	
	//Функция отображения карты для дебага
void Show_Level(int &rows, int &cols, char map_lev[N][N], char map_obj[N][N], HANDLE handle)
{
		for (int i = 0; i <rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{//Вначале проверяем клетку массива объектов на наличие в ней объекта
			 //Если есть то выводим
				switch (map_obj[i][j])	
				{
				case '\n':
					printf("\n");
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
				case ' ':
					switch (map_lev[i][j])
					{//Если в массиве объектов пробел то 
					 //Выводим символ из массива геометрии уровня
					 //Через эти символы у игрока есть возможность передвигаться
					case' ':
						SetConsoleTextAttribute(handle, 8);
						printf(".");
						break;
					case '¶':
						SetConsoleTextAttribute(handle, 2);
						printf("%c", map_lev[i][j]);
						break;
					case 'D':
						SetConsoleTextAttribute(handle, 15);
						printf("%c", map_lev[i][j]);
						break;
					}
					break;
				case 'W':
					switch (map_lev[i][j])
					{
					//Если в массиве объектов 'W' то 
					//Выводим символ из массива геометрии уровня
					//Через эти символы у игрока нету возможности передвигаться
					case '^':
						SetConsoleTextAttribute(handle, 7);
						printf("%c", map_lev[i][j]);
						break;
					case '~':
						SetConsoleTextAttribute(handle, 159);
						printf("%c", map_lev[i][j]);
						break;
					case ' ':
						SetConsoleTextAttribute(handle, 15);
						printf("#");
						break;
					default:
						SetConsoleTextAttribute(handle, 15);
						printf("%c", map_lev[i][j]);
						break;
					}
					break;
				}
			}
	}
		SetConsoleTextAttribute(handle, 15);
		printf("\n");
}

void Check(int &y, int &x, char map_obj[N][N], int mov)
{
	switch (mov)
	{
		case up:
			if (map_obj[y + 1][x] == ' ')
				y++;	
			break;
			//To do: Изменить на switch и выкинуть use (т.к проще будет использовать объект при помощи перемещения)
		case down:
			if (map_obj[y - 1][x] == ' ')
				y--;
			break;
		case left:
			if (map_obj[y][x - 1] == ' ')
				x--;
			break;
		case right:
			if (map_obj[y][x + 1] == ' ')
				x++;
			break;
		case use:
			break;
	}
}
	// Функция случайного выбора шаблонов *Не реализована
int Randomize(int a, int b)
{
	return rand() % (b - a + 1) + a;
}

	//Функция отображения карты для игрока *V2
void View(int x, int y, char map_lev[N][N], char map_obj[N][N], HANDLE handle)
{
	for (int i = y-3 ; i <y+2 ; i++)
	{
		printf("\n");
		for (int j = x - 6; j < x+3 ; j++)
		{ 
			switch (map_obj[i][j])
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
				switch (map_lev[i][j])
				{
				case' ':
					SetConsoleTextAttribute(handle, 15);
					printf(".");
					break;
				case '¶':
					SetConsoleTextAttribute(handle, 2);
					printf("%c", map_lev[i][j]);
					break;
				case 'D':
					SetConsoleTextAttribute(handle, 15);
					printf("%c", map_lev[i][j]);
					break;
				}
				break;
			case 'W':
				switch (map_lev[i][j])
				{
				case '^':
					SetConsoleTextAttribute(handle, 8);
					printf("%c", map_lev[i][j]);
					break;
				case '~':
					SetConsoleTextAttribute(handle, 159);
					printf("%c", map_lev[i][j]);
					break;
				default:
					SetConsoleTextAttribute(handle, 8);
					printf("%c", map_lev[i][j]);
					break;
				}
				break;
			}
		}
	}
	SetConsoleTextAttribute(handle, 15);
	printf("\n");
}