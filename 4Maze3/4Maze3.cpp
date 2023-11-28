#include "Mazex.h" 
#include <SFML/Audio.hpp>
using namespace std;
// прототипы функций:
void Systemname();
void Options();    // настройка размеров и расположения окна, установка заголовка, скрытие мигающего курсора
void MoveWindow();
void Menu(); // три пункта меню
void Letter(int x, int y, int forecolor, int backcolor, char symb); // рисование квадрата с буквой для заставки
void Text_effect(int x, int y, int forecolor, int backcolor, const char* symb, int len, int pause); // показ "ленты" текста
void Exit(); // быстрый выход из приложения
void The_end(); // концовка с пожеланием удачи
void Stand(int x, int y, int k, const char* str); // вспомогательная функция по установке курсора в нужную позцию + окрашивание
void Help(); // открытие файла справки
void Game(); // основной игровой процесс
// точка входа в приложение
int main()
{
	Options();
	Menu();
}
//конец программы
void Finish()
{
	system("cls");
	main();
	Sleep(INFINITE);
}
// функция вывода квадратика с буквой (стилизация под клавиатуру)
void Letter(int x, int y, short forecolor, int backcolor, char symb) 
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	int sizeX = 9; // размер квадрата по ширине
	int sizeY = 7; // по высоте
	// отрисовка квадрата двойным циклом
	for (int j = 0; j < sizeY; j++)
	{
		for (int i = 0; i < sizeX; i++)
		{
			COORD temp = { x + i, y + j }; // назначение координат
			SetConsoleCursorPosition(h, temp); // установка координат
			SetConsoleTextAttribute(h, backcolor * 16 + forecolor); // окрашивание
			cout << " "; // рисуем пробелы определённого цвета, из которых состоят квадраты
		}
	}
	// пишем букву в центре квадрата
	COORD temp = { x + sizeX / 2, y + sizeY / 2 };
	SetConsoleCursorPosition(h, temp);
	cout << symb;
}
//задаем размер окна
void Systemname()
{
	system("title Keyboard simulator");
	system("mode con cols=130 lines=50");
}

void Options()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	// размер окна - 130х50 символов
	CONSOLE_CURSOR_INFO ci; // скрытие курсора
	ci.bVisible = false; // курсор не видно
	ci.dwSize = 100; // на самом деле, не важно что сюда писать - подходит любое значение от 1 до 100 (рамер курсора в процентах относительно клетки)
	SetConsoleCursorInfo(h, &ci); // применить настройки
}
// двигаем окно: консольное окно ставится в точку 50 пикселей по иксу и 50 по игреку относительно рабочего стола
void MoveWindow()
{
	MoveWindow(GetConsoleWindow(), 50, 50, 2000, 2000, true); 
	// 2000х2000 - максимальные размеры окна, тру - перерисовка (обычно это имеет значение для приложений под виндовс)
}

// побуквенный показ переданного текста:
// x y - начальные координаты показа, фор и бэк калар - цвет текста и фона, текст - указатель на строку текста, лен - длина этого текста, пауз - время в мс перед показом следующей буквы текста
void Text_effect(int x, int y, int forecolor, int backcolor, const char* text, int len, int pause)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < len; i++)
	{
		COORD temp = { x + i, y }; // будем ставить курсор в определённые координаты
		SetConsoleCursorPosition(h, temp); // ставим
		SetConsoleTextAttribute(h, backcolor * 16 + forecolor); // применяем цвет
		cout << text[i]; // рисуем букву
		Sleep(pause); // ждём
	}
}
// делаем цвет текста чёрным - чтобы пользователь не увидел никаких надписей
void Exit()
{ 
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0);
	system("taskkill -im cmd.exe"); // закрываем все процессы по имени cmd - это все консольные окна
}

void The_end()
{
	Text_effect(5, 2, 12, 0, "Thank you for playing!", 30, 20); // красным цветом благодарим за игру
	Text_effect(5, 4, 7, 0, "Press Enter to exit", 24, 15); // белым цветом выводим просьбу нажать на энтер
	while (_getch() != 13); // до тех пор, пока пользователь не нажмёт на энтер - у него код 13
	Exit(); // выходим
}

void Stand(int x, int y, int k, const char* str)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c{ x, y };
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, k);
	cout << str << "\n";
}
//информаия
void Help()
{
	sf::SoundBuffer BlusterV6Buffer; BlusterV6Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\Mouse.wav");
	sf::Sound BlasterV6(BlusterV6Buffer);
	BlasterV6.setVolume(10);

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 10);
	system("type spravka.txt"); // стандартная команда виндовс по распечатке файла (файл лежит в папке с проектом!)

	while (true)
	{
		int n = _getch();
		if (n == 27 || n == 'n')
		{
			BlasterV6.play();
			Menu();
		}
	}
}
//вход в игру
void Game()
{ 	
	sf::SoundBuffer BlusterV1Buffer; BlusterV1Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\03-Rugged-Area.wav");
	sf::Sound BlasterV1(BlusterV1Buffer);
	BlasterV1.setVolume(10);
	BlasterV1.play();
	//1.Эта строка создает объект sf::SoundBuffer с именем BlusterV1Buffer. sf::SoundBuffer представляет буфер звуковых данных, который может быть использован для загрузки звукового файла.
	//2.BlusterV1Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\03-Rugged-Area.wav");: Загружает звуковой файл из указанного пути ("D:\C++\C++\4Maze3\GameEffects\03-Rugged-Area.wav") в буфер звуковых данных BlusterV1Buffer
	//3.sf::Sound BlasterV1(BlusterV1Buffer);: Создает объект sf::Sound с именем BlasterV1 и передает ему BlusterV1Buffer в качестве источника звука. sf::Sound представляет собой объект для воспроизведения звуков.
	//4.BlasterV1.setVolume(10);: Устанавливает уровень громкости для звукового объекта BlasterV1. Значение 10 указывает на громкость в диапазоне от 0 до 100.
	//5.BlasterV1.play();: Воспроизводит звук, используя звуковой объект BlasterV1
	sf::SoundBuffer BlusterV2Buffer; BlusterV2Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\money.wav");
	sf::Sound BlasterV2(BlusterV2Buffer);
	BlasterV2.setVolume(10);
	
	sf::SoundBuffer BlusterV3Buffer; BlusterV3Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\hill.wav");
	sf::Sound BlasterV3(BlusterV3Buffer);
	BlasterV3.setVolume(10);

	sf::SoundBuffer BlusterV4Buffer; BlusterV4Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\Game-Over.wav");
	sf::Sound BlasterV4(BlusterV4Buffer);
	BlasterV4.setVolume(10);

	sf::SoundBuffer BlusterV7Buffer; BlusterV7Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\GameOverDeath.wav");
	sf::Sound BlasterV7(BlusterV7Buffer);
	BlasterV7.setVolume(10);

	sf::SoundBuffer BlusterV9Buffer; BlusterV9Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\kick.wav");
	sf::Sound BlasterV9(BlusterV9Buffer);
	BlasterV9.setVolume(10);

	System("title Maze");
	Console();
	srand(time(0)); // запуск алгоритма генерации СЧ

	const int width = 60; // ширина лабиринта
	const int height = 20; // высота лабиринта

	int maze[height][width]; // заготовка для лабиринта в виде двумерного массива, заполненного нулями
	int two = 0;//создал переменную для посчета кол-ва монет 

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			maze[y][x] = rand() % 5; // 0 1 2 3
			// установка стен по бокам (делаем рамки)
			Walls(x, y, width, height, maze, WALL);
			// определение точки входа и выхода из лабиринта
			Mazeexit(x, y, width, height, maze, HALL);
			// если текущий элемент 2д-массива - это враг,
			// то ниже код, который уменьшает их количество
			// условно, произойдёт жеребьёвка (или же подбрасывание монетки)
			Reduction(x, y, maze, ENEMY, HALL, 10);
			Reduction(x, y, maze, 4, HALL, 20);

			if (maze[y][x] == 2)
			{
				two++;//считаем кол-во монет на карте
			}
			if (maze[y][x] == 0)//коридор
			{
				SetCursor(x, y, 0, " ");
			}
			else if (maze[y][x] == 1)//стена
			{
				SetCursor(x, y, 3, "");
				cout << (char)178;
			}
			else if (maze[y][x] == 2)//монетки
			{
				SetCursor(x, y, 14, ".");
			}
			else if (maze[y][x] == 3)//враг
			{
				SetCursor(x, y, 12, "");
				cout << (char)2;
			}
			else if (maze[y][x] == 4)//аптечка
			{
				SetCursor(x, y, 12, "");
				cout << (char)3;
			}
			else
			{
				cout << maze[y][x];
			}
		}
		cout << "\n";
	}
	// пример установки курсора в любые координаты консоли
	COORD position;
	position.X = 0;
	position.Y = 2;
	SetCursor(0, 2, 13, "");
	int coins = 0;
	int health = 100;
	int health2 = 100;
	int money = two;

	cout << (char)1;
	// начинаем интерактив (польщователь управляет смайликом с помощью клавиатуры)
	while (true)
	{
		if (_kbhit())//проверяет консоль на предмет недавнего нажатия клавиши
		{
			int code = _getch(); // get character - получение кода нажатой клавиши
			if (code == 224) // если была нажата какая-то стрелка
			{
				code = _getch();
			}
			// после того, как клавиша стрелки была нажата, программа уже знает, куда побежит смайлик
			// можно стереть смайлик в его текущей позиции
			SetCursor(position.X, position.Y, 0, " ");

			if (code == RIGHT and maze[position.Y][position.X + 1] != 1) // right
			{
				position.X++; // изменение позиции ГГ вправо на 1 по иксу
			}
			else if (code == LEFT and maze[position.Y][position.X - 1] != 1)
			{
				position.X--;// изменение позиции ГГ влево на 1 по иксу
			}
			else if (code == UP and maze[position.Y - 1][position.X] != 1)
			{
				position.Y--;// изменение позиции ГГ вверх на 1 по иксу
			}
			else if (code == DOWN and maze[position.Y + 1][position.X] != 1)
			{
				position.Y++;// изменение позиции ГГ вниз на 1 по иксу
			}

			SetCursor(position.X, position.Y, PURPUR, "");
			cout << (char)1;
			SetCursor(width+1,1,GREEN,"The number of coins in the gaim : ");
			cout << money;

			if (position.X == width - 1 and position.Y == height - 3)
			{
				BlasterV1.stop();
				BlasterV4.play();
				MessageBoxA(0, "You found your way out of the maze!!!!", "You win!!!", MB_OK);
				break;
			}
			if (maze[position.Y][position.X] == 2)
			{
				coins++;
				//CreateThread(0, 0, MusicThread, 0, 0, 0);
				BlasterV2.play();
				
				maze[position.Y][position.X] = 0;
				SetCursor(width + 1, 2, YELLOW, "Number of coins picked up: ");
				cout << coins;
			}
			if (coins == two)
			{
				BlasterV1.stop();
				BlasterV4.play();
				Message("You have collected all the coins!!! ", "You win!!!");
				break;
			}
			if (maze[position.Y][position.X] == 3)
			{
				BlasterV9.play();
				health -= 20;
				maze[position.Y][position.X] = 0;
				SetCursor(width + 1, 3, PURPUR, "Hit points: ");
				cout << health;
				cout << " ";
			}
			if (maze[position.Y][position.X] == 4 and health < 100)
			{
				BlasterV3.play();
				health += 20;
				maze[position.Y][position.X] = 0;
				SetCursor(width + 1, 3, PURPUR, "Hit points: ");
				cout << health;
				cout << " ";
			}
			if (health == 0)
			{
				BlasterV1.stop();
				BlasterV7.play();
				Message("You have run out of health!!!!", "You are dead!!!!");
				break;
			}
		}
		else 
		{
			Sleep(20);
			COORD enemy_positions[100]; 
			int enemy_count = 0; 

			for (int y = 0; y < height; y++) 
			{
				for (int x = 0; x < width; x++) 
				{
					
					if (maze[y][x] == MazeObject::ENEMY)
					{
						enemy_positions[enemy_count].X = x;
						enemy_positions[enemy_count].Y = y;
						enemy_count++;
					}
				}
			}
			//ПЕРЕДВИЖЕНИЕ ВРАГОВ
			for (int i = 0; i < enemy_count; i++)
			{
				int r = rand() % 100; 
				if (r == LEFT &&
					maze[enemy_positions[i].Y][enemy_positions[i].X - 1] != MazeObject::WALL &&
					maze[enemy_positions[i].Y][enemy_positions[i].X - 1] != MazeObject::BORDER &&
					maze[enemy_positions[i].Y][enemy_positions[i].X - 1] != MazeObject::ENEMY
					)
				{	
					COORD temp = enemy_positions[i];
					SetConsoleCursorPosition(h, temp);
					cout << " ";
					maze[enemy_positions[i].Y][enemy_positions[i].X] = MazeObject::HALL;

					
					temp.X = enemy_positions[i].X - 1;
					temp.Y = enemy_positions[i].Y;
					SetConsoleCursorPosition(h, temp);
					SetConsoleTextAttribute(h, Color::RED);
					cout << (char)2;
					maze[enemy_positions[i].Y][enemy_positions[i].X - 1] = MazeObject::ENEMY;
				}
				else if (r == RIGHT &&
					maze[enemy_positions[i].Y][enemy_positions[i].X + 1] != MazeObject::WALL &&
					maze[enemy_positions[i].Y][enemy_positions[i].X + 1] != MazeObject::BORDER &&
					maze[enemy_positions[i].Y][enemy_positions[i].X + 1] != MazeObject::ENEMY)
				{	
					COORD temp = enemy_positions[i];
					SetConsoleCursorPosition(h, temp);
					cout << " ";
					maze[enemy_positions[i].Y][enemy_positions[i].X] = MazeObject::HALL;
	
					temp.X = enemy_positions[i].X + 1;
					temp.Y = enemy_positions[i].Y;
					SetConsoleCursorPosition(h, temp);
					SetConsoleTextAttribute(h, Color::RED);
					cout << (char)2;
					maze[enemy_positions[i].Y][enemy_positions[i].X + 1] = MazeObject::ENEMY;
				}
				else if (r == UP &&
					maze[enemy_positions[i].Y - 1][enemy_positions[i].X] != MazeObject::WALL &&
					maze[enemy_positions[i].Y - 1][enemy_positions[i].X] != MazeObject::BORDER &&
					maze[enemy_positions[i].Y - 1][enemy_positions[i].X] != MazeObject::ENEMY)
				{	
					COORD temp = enemy_positions[i];
					SetConsoleCursorPosition(h, temp);
					cout << " ";
					maze[enemy_positions[i].Y][enemy_positions[i].X] = MazeObject::HALL;
					
					temp.X = enemy_positions[i].X;
					temp.Y = enemy_positions[i].Y - 1;
					SetConsoleCursorPosition(h, temp);
					SetConsoleTextAttribute(h, Color::RED);
					cout << (char)2;
					maze[enemy_positions[i].Y - 1][enemy_positions[i].X] = MazeObject::ENEMY;
				}
				else if (r == DOWN &&
					maze[enemy_positions[i].Y + 1][enemy_positions[i].X] != MazeObject::WALL &&
					maze[enemy_positions[i].Y + 1][enemy_positions[i].X] != MazeObject::BORDER &&
					maze[enemy_positions[i].Y + 1][enemy_positions[i].X] != MazeObject::ENEMY)
				{
					COORD temp = enemy_positions[i];
					SetConsoleCursorPosition(h, temp);
					cout << " ";
					maze[enemy_positions[i].Y][enemy_positions[i].X] = MazeObject::HALL;

					temp.X = enemy_positions[i].X;
					temp.Y = enemy_positions[i].Y + 1;
					SetConsoleCursorPosition(h, temp);
					SetConsoleTextAttribute(h, Color::RED);
					cout << (char)2;
					maze[enemy_positions[i].Y + 1][enemy_positions[i].X] = MazeObject::ENEMY;
				}
			}
		}
	}
	Finish();
}
void Menu()
{
	sf::SoundBuffer BlusterV5Buffer; BlusterV5Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\02-Metal-Area.wav");
	sf::Sound BlasterV5(BlusterV5Buffer);
	BlasterV5.setVolume(10);
	BlasterV5.play();

	sf::SoundBuffer BlusterV6Buffer; BlusterV6Buffer.loadFromFile("D:\\C++\\C++\\4Maze3\\GameEffects\\Mouse.wav");
	sf::Sound BlasterV6(BlusterV6Buffer);
	BlasterV6.setVolume(10);
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	system("title Maze");
	int start_y = 3;
	system("cls"); 
	Stand(5, start_y, 10, "Help");
	Stand(5, start_y + 2, 2, "Game");
	Stand(5, start_y + 4, 2, "Exit");

	int k;	
	int cur = 1;
	while (true)
	{
		k = _getch();
		if (k == 80)
		{
			BlasterV6.play();
			if (cur < 3)
			{
				cur++;
				if (cur == 2)
				{
					Stand(5, start_y, 2, "Help"); 
					Stand(5, start_y + 2, 10, "Game"); 
				}
				else if (cur == 3) {
					Stand(5, start_y + 2, 2, "Game");
					Stand(5, start_y + 4, 10, "Exit");
				}
			}
		}
		else if (k == 72) 
		{
			BlasterV6.play();
			if (cur > 1)
			{
				cur--;
				if (cur == 2)
				{
					Stand(5, start_y + 2, 10, "Game");
					Stand(5, start_y + 4, 2, "Exit");
				}
				else if (cur == 1)
				{
					Stand(5, start_y, 10, "Help");
					Stand(5, start_y + 2, 2, "Game");
				}
			}
		}
		else if (k == 13) 
		{
			BlasterV6.play();
			system("cls");
			SetConsoleTextAttribute(h, 12);
			if (cur == 1)
			{
				BlasterV5.stop();
				Help();
			}	
			else if (cur == 2)
			{
				BlasterV5.stop();
				Game();

			}
			else if (cur == 3)
				The_end();
		
			exit(0);
		}
	}
}
