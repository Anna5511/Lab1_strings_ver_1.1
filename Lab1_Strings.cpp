#include <iostream>
#include <iomanip>
#include <fstream>

const unsigned N = 100;
struct strm { char mark; char A[N + 1]; };

void clear_File() {
    std::ofstream File("C:\\Users\\Анечка\\Documents\\out1.txt", std::ios::trunc);
    File.close();
}

void outp(const char* text, const char* str, char mark_symbol)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out1.txt", std::ios::app);
    if (str[0] != '\0') {
        file << text;
        for (int i = 0; i <= N; i++) {
            if (str[i] != mark_symbol) {
                file << str[i];
            }
            else {
                file << std::endl;
                break;
            }
        }
    }
    else {
        file << text << mark_symbol << std::endl;
    }
    file.close();
}
void outp_n(const char* text, int n) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out1.txt", std::ios::app);
    if (n != 0) file << "-------------------" << std::endl;
    file << text << n << std::endl;
    file.close();
}

void swap(strm& a, char mark) {
    char temp = a.A[0];
    for (int i = 0; i < N; i++) {
        if (a.A[i + 1] != mark) {
            a.A[i] = a.A[i + 1];
        }
        else {
            a.A[i] = temp;
            break;
        }
    }
}
int poisk_pos(strm& a) {
    int pos = 0;
    while (a.A[pos] != a.mark && pos != N) {
        pos++;
    }return pos;
}

void process(strm& a) {
    int pos = poisk_pos(a);
    int pos_count = pos / 2 + pos % 2;
    for (int i = 0; i < pos_count; i++) {
        swap(a, a.mark);
    }
    outp("Результат : ", a.A, a.mark);
}
void skipToNextLine(std::ifstream& file) {
    char c;
    while (file.get(c)) {
        if (c == '\n') break;
    }
}

bool readLine(std::ifstream& file, strm& a, int n) {
    char c = ' ';
    char stop;
    // Читаем маркер
    if (!file.get(a.mark)) {
        outp("Ошибка: Пустой входной файл", "", ' ');
        return false;
    }
    if (a.mark == '\n') {
        outp("Ошибка: Пустая строка (нет маркера)", "", ' ');
        return false;
    }

    // Читаем ограничитель
    file.get(stop);
    if (stop == '\n') {
        outp("Ошибка: Нет ограничителя", "", ' ');
        return false;
    }

    outp("Маркер : ", "", a.mark);
    outp("Ограничитель : ", "", stop);

    // Читаем строку до маркера или ограничителя
    unsigned i = 0;

    while (file.get(c) && c != '\n') {

        if (c == stop || c == a.mark) {

            skipToNextLine(file);

            // Добавляем маркер в конец
            a.A[i] = a.mark;
            return true;
        }
        a.A[i] = c;
        i++;
        if (i == N) {
            outp("В строке взяты первые 100 символов", "", ' ');
            skipToNextLine(file);
            break;
        }
    }
    if (i == 0) {
        outp("В строке нет символов", "", ' ');
        return false;

    }

    // Добавляем маркер в конец
    a.A[i] = a.mark;

    return true;
}

bool out_file_check() {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\out1.txt");
    if (!file.is_open()) {
        std::cout << "Ошибка открытия выходного файла";
        file.close();
        return true;
    }
    else {
        file.close();
        return false;
    }
}
bool in_file_check() {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in1.txt");
    if (!file.is_open()) {
        outp("Ошибка открытия входного файла", "", ' ');
        file.close();
        return true;
    }
    else {
        file.close();
        return false;
    }
}

int main()
{
    clear_File();
    setlocale(LC_ALL, "ru");
    if (in_file_check()) return 0;
    if (out_file_check()) return 0;


    std::ifstream file("C:\\Users\\Анечка\\Documents\\in1.txt");
    int lineNumber = 0;

    // Основной цикл обработки
    while (!file.eof()) {
        strm string;
        outp_n("Номер строки: ", lineNumber);

        if (readLine(file, string, lineNumber)) process(string);
        lineNumber++;

        for (int i = 0; i <= N; i++) {
            string.A[i] = string.mark;
        }
    }

    return 1;
}