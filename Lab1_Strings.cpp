#include <iostream>
#include <iomanip>
#include <fstream>

const unsigned N = 100;
struct strm { char mark; char A[N + 1]; };

void clear_File(){
    std::ofstream File("C:\\Users\\Анечка\\Documents\\out1.txt", std::ios::trunc);
    File.close();
}

/// <summary>
/// Функция вывода в файл out.txt
/// </summary>
/// <param name="text"> - сообщение</param>
/// <param name="str"> - строка на вывод</param>
/// <param name="mark_symbol"> - маркер (до него читается строка) или символ на выход</param>
/// <returns></returns>
void outp(const char* text, const char* str, char mark_symbol)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out1.txt", std::ios::app);
        
    if (str && str[0]) {
        file << text;
        for (int i = 0; i < N; i++) {
            if (str[i] != mark_symbol) {
                file << str[i];
            }
            else {
                file << std::endl;
                break;
            }
        }
        file << std::endl;
    }
    else{
        file << text << mark_symbol << str << std::endl;
    }

    file.close();
}

void outp_n(const char* text, int n) {
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out1.txt", std::ios::app);
    if (n!= 1) file << "-------------------" << std::endl;
    file << text << n << std::endl;
    file.close();
}

/// <summary>
/// Перемещает символы в строке до маркера
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <param name="mark"> - маркер </param>
void swap(strm& a, char mark){
    char temp = a.A[0];
    for (int i = 0; i < N-1; i++) {
        if (a.A[i+1] != mark) {
            a.A[i] = a.A[i + 1];
        }
        else {
            a.A[i] = temp;
            break;
        }
    }
}

/// <summary>
/// Ищет изначальную позицию маркера
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <returns></returns>

int poisk_pos(strm& a) {
    int pos = 0;

    while (a.A[pos] != a.mark && pos != N)
    {
        if (a.A[pos] == a.mark) {
            return pos;
        }
        pos++;
    }
    return pos;
}

/// <summary>
/// Основная работа программы - перемещение символов в строке
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <param name="o_pos"> - old marker position (конец строки)</param>
/// <param name="n_pos"> - new marker position (середина строки)</param>

void process(strm& a)
{
    int pos = poisk_pos(a);
    int pos_count = pos / 2 + pos % 2;
    for (int i = 0; i < pos_count; i++) {
        swap(a, a.mark);
    }

    outp("Результат : ", a.A, a.mark);

}

/// <summary>
/// Функция ввода из файла
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <returns></returns>

//ПЕРЕДЕЛАТЬ!

//bool inp(strm& a) {
//    int file_num = 1;
//    std::ifstream file("C:\\Users\\Анечка\\Documents\\in1.txt", std::ios::in);
//
//    char stop;
//    char c;
//
//    if (!file.is_open()) {
//        std::cout << "Ошибка открытия входного файла";
//        return false;
//    }
//    
//
//    //читает построчно файл, считывает маркеты и ограничители, читает строки, если что-то не так, то выдает ошибки
//    while (!(file.eof())) {
//        char n = file_num + '0';
//        outp("Cтрока №", "", n);
//
//
//        file.get(a.mark);
//        if (a.mark == '\n') {
//            outp("Ошибка - пустая строка", "", ' ');
//            file_num++;
//            outp("----------------", "", ' ');
//            continue;
//        }
//
//        file.get(stop);
//        if (stop == '\n') {
//            outp("Ошибка - нет ограничителя", "", ' ');
//            file_num++;
//            outp("----------------", "", ' ');
//            continue;
//        }
//
//        unsigned i = 0;
//        bool flag = false;
//
//        while (file.get(c)) {
//            if (c == stop || c == a.mark) break;
//            if (c == '\n' || file.eof()) {
//                file_num++;
//                outp("Ошибка - в строке нет маркера и ограничителя", "", ' ');
//                outp("----------------", "", ' ');
//                flag = true;
//                break;
//
//            }
//
//            a.A[i] = c;
//            i++;
//            if (i > N) {
//                outp("Ошибка - в строке больше 100 символов", "", ' ');
//                file_num++;
//                outp("----------------", "", ' ');
//                flag = true;
//                break;
//            }     
//            
//        }
//
//        //Пропускает остаток строки и переходит на следующую строчку
//        if (flag) { 
//            while (file.get(c)) {
//                if (c == '\n') break;
//                if (file.eof()) return true;
//            }
//            continue;
//        }
//
//        if (i == 0) {
//            outp("Ошибка - пустая строка", "", ' ');
//            return 0;
//        }
//        if (i == N) {
//            outp("В строке ровно 100 символов", "", ' ');
//            a.A[i] = a.mark;
//        }
//        if(i < N){
//            a.A[i] = a.mark;
//            a.A[i + 1] = '\0';
//        }
//
//        outp("Маркер: ", "", a.mark);
//        outp("Ограничитель: ", "", stop);
//        outp("Строка: ", a.A, ' ');
//
//        while (file.get(c) && !(file.eof())) {
//            if (c == '\n') break;
//            if (file.eof()) return true;
//        }
//
//        file_num++;
//
//
//        int o_pos = poisk_pos(a);
//        int n_pos = (poisk_pos(a)) / 2 + (poisk_pos(a)) % 2;
//        process(a, o_pos, n_pos);
//
//        outp("----------------", "", ' ');
//
//
//    }
//    file.close();
//    return true;
//}

void skipToNextLine(std::ifstream& file) {
    char c;
    while (file.get(c)) {
        if (c == '\n') break;
    }
}

/// <summary>
/// Чтение одной строки из файла
/// </summary>
/// <param name="file"> - входной файл для чтения</param>
/// <param name="a"> - структура на вход</param>
/// <returns></returns>
bool readLine(std::ifstream& file, strm& a) {
    char c;
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

    // Читаем строку до маркера или ограничителя
    unsigned i = 0;
    file.get(c);
    while (c != '\n' && !(file.eof())) {
        file.get(c);
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
            break;
        }
    }

    // Добавляем маркер в конец
    a.A[i] = a.mark;

    return true;
}

//проверяем сразу, все ли хорошо с входным файлом
bool file_check() {
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in1.txt");
    if (!file.is_open()) {
        outp("Ошибка открытия входного файла", "", ' ');
        return true;
    }
    else {
        return false;
    }
}



int main() {
    clear_File();
    setlocale(LC_ALL, "ru");

    
    if (file_check()) return 0;
    //открываем входной файл (ОБРАБОТКА В ДРУГОЙ ФУНКЦИИ, ТУТ МЫ ТОЛЬКО УПРАВЛЯЕМ ЭТИМ ЧТЕНИЕМ!)
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in1.txt");

    int lineNumber = 1;

    // Основной цикл обработки
    while (!file.eof()) {
        strm string;
        char stop;

        outp_n("Номер строки: ", lineNumber);
        lineNumber++;

        if(!(readLine(file, string))) continue;
        process(string);
        
        

        // Проверка на конец файла (чтобы не обрабатывать последнюю пустую строку)
        if (file.peek() == EOF) break;
    }


    //if (!(inp(file))) return 0;

    file.close();
    return 0;
}