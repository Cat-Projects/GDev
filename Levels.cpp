#include <iostream>
#include <conio.h>
#include <Windows.h>
#define N 256
enum {up = 72, down = 80, left = 75, right = 77, use};
struct player { int x, y, health, key; };

void Player_View(int &rows, int &cols, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N], HANDLE handle);
void Show_Level(int &rows, int &cols, char map_lev[N][N], char map_obj[N][N], HANDLE handle);
void TestWrite(int rows, int cols, char map_lev[N][N], char name[]);
void TestRead(int &rows, int &cols, char map_lev[N][N], char name[]);
void CheckP(player &p, char map_obj[N][N], int mov);
void PlayerTurn(player &p, char map_obj[N][N]);
void color();
void setcur(int x, int y);
void Read_Lev(int &rows, int &cols, char map_lev[N][N], char name[]);
void Read_Obj(int rows, int cols, player &p, char map_obj[N][N], char name[]);
void Read_Fog(int rows, int cols, char map_fog[N][N], char name[]);
void Fog_Change(int rows, int cols, player p, char map_fog[N][N]);
void Main_Menu(int &rows, int &cols, player &p, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N]);
void Level_Load(int &rows, int &cols, player &p, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N]);
void Refresh(int &rows, int &cols, player p, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N], HANDLE handle);
void Game_Process(int &rows, int &cols, player p, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N], HANDLE handle);

int main()
{
	player p;
	p.x = 16; p.y = 25; p.key = 0;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	system("chcp 1251");
	system("cls");

	int rows, cols;
	char map_lev[N][N];
	char map_obj[N][N];
	char map_fog[N][N];

	Main_Menu(rows, cols, p, map_lev, map_obj, map_fog);
	Refresh(rows, cols, p, map_lev, map_obj, map_fog, handle);
	Game_Process(rows, cols, p, map_lev, map_obj, map_fog, handle);
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
	setcur(0, 0);
	for (int i = 0; i <rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{//Вначале проверяем клетку массива объектов на наличие в ней объекта
		 //Если есть то выводим
			switch(map_fog[i][j])
			{
			default :
				SetConsoleTextAttribute(handle, 15);
				printf("\n");
				break;
			case '0':
				SetConsoleTextAttribute(handle, 15);
				printf(" ");
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
			break;
			}
		}
	}
	SetConsoleTextAttribute(handle, 15);
	printf("\n");
}
	
	//Функция отображения карты для дебага
void Show_Level(int &rows, int &cols, char map_lev[N][N], char map_obj[N][N], HANDLE handle)
{
	setcur(0, 0);
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
					printf(" ");
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

	//Костыль для избавления от "мигания" консоли при очистке
void setcur(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

	//Передвежение игрока и взаимодействие с предметами
void CheckP(player &p, char map_obj[N][N], int mov)
{
	switch (mov)
	{
		case up:
			switch(map_obj[p.y - 1][p.x])
			{
			case ' ':
				map_obj[p.y - 1][p.x] = 'P';
				map_obj[p.y][p.x] = ' ';
				p.y--;
				break;
			case 'C':
				if (p.key)
				{
					map_obj[p.y - 1][p.x] = ' ';
					p.key--;
				}
				break;
			case 'K':
				p.key++;
				map_obj[p.y - 1][p.x] = ' ';
				break;
			}
			break;
		case down:
			switch (map_obj[p.y + 1][p.x])
			{
			case ' ':
				map_obj[p.y + 1][p.x] = 'P';
				map_obj[p.y][p.x] = ' ';
				p.y++;
				break;
			case 'C':
				if (p.key)
				{
					map_obj[p.y + 1][p.x] = ' ';
					p.key--;
				}
				break;
			case 'K':
				p.key++;
				map_obj[p.y + 1][p.x] = ' ';
				break;
			}
			break;
		case left:
			switch (map_obj[p.y][p.x - 1])
			{
			case ' ':
				map_obj[p.y][p.x - 1] = 'P';
				map_obj[p.y][p.x] = ' ';
				p.x--;
				break;
			case 'C':
				if (p.key)
				{
					map_obj[p.y][p.x - 1] = ' ';
					p.key--;
				}
				break;
			case 'K':
				p.key++;
				map_obj[p.y][p.x - 1] = ' ';
				break;
			}
			break;
		case right:
			switch (map_obj[p.y][p.x + 1])
			{
			case ' ':
				map_obj[p.y][p.x + 1] = 'P';
				map_obj[p.y][p.x] = ' ';
				p.x++;
				break;
			case 'C':
				if (p.key)
				{
					map_obj[p.y][p.x + 1] = ' ';
					p.key--;
				}
				break;
			case 'K':
				p.key++;
				map_obj[p.y][p.x + 1] = ' ';
				break;
			}
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

	//Функция ввода клавиши во время хода игрока
void PlayerTurn(player &p, char map_obj[N][N])
{
	do
	{
		int n = _getch();
		int act = _getch();
		if (act == 72 || act == 80 || act == 75 || act == 77)
		{
			CheckP(p, map_obj, act);
			return;
		}
		else if (act == 141 || act == 145 || act == 115 || act == 116)
		{
			//	Attack(player, map, act);
			return;
		}
	} while (true);
}

	//Функция загрузки геометрии карты
void Read_Lev(int &rows, int &cols, char map_lev[N][N], char name[])
{
	FILE* ReadLev;
	if (fopen_s(&ReadLev, name, "r+") != 0)
	{
		printf("ERROR");
		system("pause");
		exit(1);
	}
	fscanf_s(ReadLev, "%i", &rows);
	fscanf_s(ReadLev, "%i\r", &cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fscanf_s(ReadLev, "%c", &map_lev[i][j]);
	}
	fclose(ReadLev);
}

	//Функция загрузки объектов карты
void Read_Obj(int rows, int cols, player &p, char map_obj[N][N], char name[])
{
	FILE* ReadObj;
	if (fopen_s(&ReadObj, name, "r+") != 0)
	{
		printf("ERROR");
		system("pause");
		exit(1);
	}
	fscanf_s(ReadObj, "%i", &p.x);
	fscanf_s(ReadObj, "%i\r", &p.y);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fscanf_s(ReadObj, "%c", &map_obj[i][j]);
	}
	fclose(ReadObj);
}

	//Функция загрузки тумана войны
void Read_Fog(int rows, int cols, char map_fog[N][N], char name[])
{
	FILE* ReadFog;
	if (fopen_s(&ReadFog, name, "r+") != 0)
	{
		printf("ERROR");
		system("pause");
		exit(1);
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fscanf_s(ReadFog, "%c", &map_fog[i][j]);
	}
	fclose(ReadFog);
}

	//Обновление тумана войны
void Fog_Change(int rows, int cols, player p, char map_fog[N][N])
{
	int a, b;
	if (p.y - 3 < 0)
	{
		a = 0;
		b = p.y + 3;
	}
	else if (p.y + 3 >= rows)
	{
		a = p.y - 3;
		b = rows;
	}
	else
	{
		a = p.y - 3;
		b = p.y + 3;
	}

	int c, d;
	if (p.x - 3 <0)
	{
		c = 0;
		d = p.x + 4;
	}
	else if (p.x + 4 >= cols)
	{
		c = p.x - 3;
		d = cols-1;
	}
	else
	{
		c = p.x - 3;
		d = p.x + 4;
	}
	for (int i = a; i < b; i++)
	{
		for (int j = c; j < d; j++)
		{
			map_fog[i][j] = '1';
		}
	}
}

	//Загрузка уровня
void Level_Load(int &rows, int &cols, player &p, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N])
{
	Read_Lev(rows, cols, map_lev, "Lev/Lev2_v2.txt");
	Read_Obj(rows, cols, p, map_obj, "Lev/Lev2_obj.txt");
	Read_Fog(rows, cols, map_fog, "Lev/Lev2_fog.txt");
}

	//Главное меню игры
void Main_Menu(int &rows, int &cols, player &p, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N])
{
	Level_Load(rows, cols, p, map_lev, map_obj, map_fog);
}
	
	//Обновление экрана игрока
void Refresh(int &rows, int&cols, player p, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N], HANDLE handle)
{
	Fog_Change(rows, cols, p, map_fog);
	Player_View(rows, cols, map_lev, map_obj, map_fog, handle);
}

	//Основной процесс игры
void Game_Process(int &rows, int &cols, player p, char map_lev[N][N], char map_obj[N][N], char map_fog[N][N], HANDLE handle)
{
	do
	{
		PlayerTurn(p, map_obj);
		Fog_Change(rows, cols, p, map_fog);
		Player_View(rows, cols, map_lev, map_obj, map_fog, handle);
		//Show_Level(rows, cols, map_lev, map_obj, handle);
	} while (true);
}