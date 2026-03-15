#include <iostream>
#include <iomanip>
#include <fstream>

const unsigned N = 100;
struct strm{ char mark; char A[N + 1]; };

/// <summary>
/// Функция ввода из файла
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <param name="stop"> - маркер </param>
/// <returns></returns>
bool inp(strm& a, char& stop) {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in.txt", std::ios::in);
    std::ofstream out("C:\\Users\\Анечка\\Documents\\out.txt", std::ios::out);

    char c;

    if (!file.is_open()) {
        std::cout << "Ошибка открытия входного файла";
        return false;
    }     
    if (!out.is_open()) {
        std::cout << "Ошибка открытия выходного файла";
        return false;
    }

    if (!(file >> a.mark)) {
        out << "Пустой файл";
        return false;
    }
    file >> c;
    if (c != '\n') file.seekg(-1, std::ios::cur);

    if (!(file >> stop)) {
        out << "Нет ограничителя";
        return false;
    }

    file >> c;
    if (c != '\n') file.seekg(-1, std::ios::cur);

    unsigned i = 0;
    

    while (file.get(c)) {
        if (c == stop || c == '\n' || file.eof() || c == a.mark) break;
        a.A[i] = c;
        i++;
        if (i >= N) {
            std::cout << "В файле больше 100 символов";
            break;
        }
    }

    a.A[i] = a.mark;
    a.A[i+1] = '\0';
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

}

int main(){
	setlocale(LC_ALL, "ru");

    strm file;
    char stop;

    inp(file, stop);
    std::cout << file.mark << std::endl << file.A;
    int o_pos = poisk_pos(file);
    int n_pos = (poisk_pos(file))/2+(poisk_pos(file))%2;
    process(file, o_pos, n_pos);

    std::cout << std::endl;
    std::cout << file.A;
	return 0;
}