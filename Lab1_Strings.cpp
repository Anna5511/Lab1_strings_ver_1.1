#include <iostream>
#include <fstream>

// Размер строки
const unsigned N = 100;
const char mark = '@';
const char stop = '!';

struct string
{
	char string[N + 1];
	unsigned markerIndex = NULL;
	bool flag_marker = false;
	unsigned size;

	void getLineFromFile(std::string filename)
	{
		size = get_line_from_file(filename);
	}

	// Вывод сообщения об ошибке и завершение программы
	void errorExit(std::string message)
	{
		std::cout << "Программа завершилась с ошибкой: ";
		std::cout << message << std::endl;
		exit(-1);	// Завершение программы с кодом "-1"
	}

	unsigned get_line_from_file(std::string filename)
	{
		std::ifstream file(filename);	// Создание потока чтения из файла
		if (!file.is_open())
			errorExit("Ошибка открытия файла \"" + filename + "\"");
		char ch;	// Переменная чтения из файла
		for (unsigned i = 0; i < N; i++)
		{
			file.get(ch);							// Посимвольное чтение
			if (ch == stop) return i;			// Если встретили символ конца строки, заканчиваем чтение
			if (ch == mark) { markerIndex = i; flag_marker++; }		// Если встретили маркер, запоминаем его индекс
			string[i] = ch;							// Записываем символ в char массив
			if (i == N-1)
			{
				std::cout << "Символ конца строки не найден! ";
				if (markerIndex)
					std::cout << "Кол-во символов с учётом маркера 100" << std::endl << std::endl;
				else
					std::cout << "Кол-во символов с учётом маркера 101" << std::endl << std::endl;
				file.get(ch);					// Посимвольное чтение
				if (ch == mark)				// Если маркер после окончания строки, записываем его в неё
				{
					string[i + 1] = mark;
					markerIndex = i + 1;		// Запись индекса маркера
					flag_marker++;
					return N + 1;						// Возвращаем кол-во эл-ов равное N + 1 (N символов + маркер)
				}
				return N;
			}
		}
	}

	void coutLine(bool no_marker = false)
	{
		for (unsigned i = 0; i < size; i++)
		{
			if (no_marker)
			{
				if (flag_marker)
					std::cout << string[i];
				else
				{
					if (i != markerIndex)
						std::cout << string[i];
				}
			}
			else {
				if (!flag_marker)
					std::cout << std::endl << "!!!NO mark!!!" << std::endl;
				std::cout << string[i];
			}
		}
	}


};

// Ставит маркер в случае его отсутствия
void setMarker(string str)
{
	str.string[str.size] = mark;
	str.size++;
}

// Смена подстрок местами (старый код)
void swapSubstring_Legacy(unsigned size, char* string, unsigned& markerIndex)
{
	if (size % 2 == 0)	// Если размер вместе с маркером чётен
	{
		// Меняем подстроки местами
		char substring[N / 2];
		for (unsigned i = 0; i < size / 2; i++)
		{
			substring[i] = string[i];
			string[i] = string[i + (size / 2)];
			string[i + (size / 2)] = substring[i];
		}

		// Вычисляем новый индекс маркера
		if (markerIndex < size / 2)
			markerIndex = markerIndex + (size / 2);
		else
			markerIndex = markerIndex - (size / 2);
	}
	else
	{
		// Меняем подстроки местами
		char substring[N / 2];
		for (unsigned i = 0; i < (size - 1) / 2; i++)
		{
			substring[i] = string[i];
		}
		for (unsigned i = 0; i < size; i++)
		{
			if (i < (size + 1) / 2)
				string[i] = string[i + ((size + 1) / 2) - 1];
			else
				string[i] = substring[i - ((size + 1) / 2)];
		}

		// Вычисляем новый индекс маркера
		if (markerIndex < (size - 1) / 2)
			markerIndex = markerIndex + (size - 1) / 2;
		else
			markerIndex = markerIndex - (size - 1) / 2;
	}
}

// Функция сдвига строки
void string_shift(string& str, unsigned count)
{
	for (unsigned i = 0; i < count; i++)
	{
		char buff = str.string[i];
		for (unsigned j = 0; j < str.size - 1; j++)
			str.string[i] = str.string[i + 1];
		str.string[str.size] = buff;
	}

	if (str.size % 2 == 0)
	{
		// Вычисляем новый индекс маркера
		if (str.markerIndex < str.size / 2)
			str.markerIndex = str.markerIndex + (str.size / 2);
		else
			str.markerIndex = str.markerIndex - (str.size / 2);
	}
	else
	{
		// Вычисляем новый индекс маркера
		if (str.markerIndex < (str.size - 1) / 2)
			str.markerIndex = str.markerIndex + (str.size - 1) / 2;
		else
			str.markerIndex = str.markerIndex - (str.size - 1) / 2;
	}
}

// Смена подстрок местами
void swapSubstring(string& str)
{
	string_shift(str, str.size / 2);
}

int main()
{
	setlocale(LC_ALL, "rus");

	//char stringL[N + 1];
	//unsigned markerIndex = NULL;
	//bool flag_marker = false;

	string str;

	std::string filename;
	std::cout << "Введите название файла с расширением: ";
	std::cin >> filename;
	str.getLineFromFile(filename);

	// Добавляем маркер, если его нет
	if (!str.flag_marker)
	{
		setMarker(str);
		str.markerIndex = str.size - 1;
		str.flag_marker++;
	}

	std::cout << "Строка с маркером: ";
	str.coutLine();					// Вывод строки с маркером
	std::cout << std::endl << std::endl;

	std::cout << "Строка без маркерa: ";
	str.coutLine(true);	// Вывод строки с маркером
	std::cout << std::endl << std::endl;

	// Меняем подстроки местами
	//swapSubstring(size, string, markerIndex);

	std::cout << "Изменённая строка с маркером: ";
	str.coutLine();		// Вывод строки с маркером
	std::cout << std::endl << std::endl << "Изменённая строка без маркера: ";
	str.coutLine(true);	// Вывод строки без маркера
	std::cout << std::endl << std::endl;

	return 0;
}