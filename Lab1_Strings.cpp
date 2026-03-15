#include <iostream>
#include <iomanip>
#include <fstream>

const unsigned N = 100;
struct strm{ char mark; char A[N + 1]; };

/// <summary>
/// Функция вывода в файл out.txt
/// </summary>
/// <param name="text"> - сообщение</param>
/// <param name="str"> - строка на вывод</param>
/// <param name="c"> - символ на вывод</param>
void outp(const char* text, const char* str, char c)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out.txt", std::ios::app);
    file << text << " : " << c << str << std::endl;

    file.close();
}

/// <summary>
/// Функция ввода из файла
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <returns></returns>
bool inp(strm& a) {
    int file_num = 1;
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in.txt", std::ios::in);
    std::ofstream out("C:\\Users\\Анечка\\Documents\\out.txt", std::ios::out);

    char stop;
    char c;

    if (!file.is_open()) {
        std::cout << "Ошибка открытия входного файла";
        return false;
    }     
    if (!out.is_open()) {
        std::cout << "Ошибка открытия выходного файла";
        return false;
    }

    outp("Cтрока № :", "", file_num);


    if (!(file >> a.mark)) {
        std::cout << "Ошибка - пустой файл";
        outp("Ошибка - пустой файл", "", ' ');
        return false;
    }
    if (!(file >> stop)) {
        std::cout << "Ошибка - нет ограничителя";
        outp("Ошибка - нет ограничителя", "", ' ');
        return false;
    }

    unsigned i = 0;
    

    while (file.get(c)) {
        if (c == stop || c == '\n' || file.eof() || c == a.mark) break;
        a.A[i] = c;
        i++;
        if (i >= N) {
            outp("Ошибка - в файле больше 100 символов", "", ' ');
            std::cout << "Ошибка - в файле больше 100 символов";
            break;
        }
    }
        
    if (i == 0) {
        outp("Ошибка - пустая строка", "", ' ');
        std::cout << "Ошибка - пустая строка";
        return 0;
    }

    if (i == N) {
        outp("В файле ровно 100 символов", "", ' ');
        std::cout << "В файле ровно 100 символов";
    }

    a.A[i] = a.mark;
    a.A[i + 1] = '\0';
    
    outp("Маркер", "", a.mark );
    outp("Ограничитель", "", stop);
    outp("Строка", a.A, ' ');

    
    out.close();
    file.close();
    return true;
}

/// <summary>
/// Перемещает символы в строке
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <param name="len"> - изначальная позиция маркера </param>
void swap(strm& a, int len)
{
    char temp = a.A[0];
    for (int i = 0; i < len; i++) {
        a.A[i] = a.A[i+1];
    }
    a.A[len] = temp;
}

/// <summary>
/// Ищет изначальную позицию маркера
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <returns></returns>
int poisk_pos(strm& a) {
    int o_pos = 0;

    while (a.A[o_pos] != '\0')
    {
        if (a.A[o_pos] == a.mark) {
            return o_pos;
        }
        o_pos++;
    }
}

/// <summary>
/// Основная работа программы - перемещение символов в строке
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <param name="o_pos"> - old marker position (конец строки)</param>
/// <param name="n_pos"> - new marker position (середина строки)</param>
void process(strm& a, int o_pos, int n_pos)
{
    int len = o_pos;
    while (o_pos != n_pos) {
        swap(a, len);
        o_pos--;
    }

    outp("Результат", a.A, ' ');

}

int main(){
	setlocale(LC_ALL, "ru");
    strm file;

    if(!(inp(file))) return 0;

    int o_pos = poisk_pos(file);
    int n_pos = (poisk_pos(file))/2+(poisk_pos(file))%2;
    process(file, o_pos, n_pos);

	return 0;
}