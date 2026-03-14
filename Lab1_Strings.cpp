#include <iostream>
#include <iomanip>
#include <fstream>

const unsigned N = 100;
struct strm{ char mark; char A[N + 1]; };



bool inp(strm& a, char& stop) {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in.txt", std::ios::in);
    std::ofstream out("C:\\Users\\Анечка\\Documents\\out.txt", std::ios::out);

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
    if (!(file >> stop)) {
        out << "Нет ограничителя";
        return false;
    }

    unsigned i = 0;
    char c;

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
    a.A[i] = '\0';
    out.close();
    file.close();
    return true;
}




int main(){
	setlocale(LC_ALL, "RU");

    strm file;
    char stop;

    inp(file, stop);
    std::cout << std::endl << file.mark << std::endl << file.A;

	return 0;
}