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
/// <param name="c"> - символ на вывод</param>
/// <param name="mark"> - маркер (до него читается строка)</param>
/// <returns></returns>
bool outp(const char* text, const char* str, char c, char mark)
{
    std::ofstream file("C:\\Users\\Анечка\\Documents\\out1.txt", std::ios::app);

    if (!file.is_open()) {
        std::cout << "Ошибка открытия выходного файла";
        return false;
    }
    
    if (str != "") {
        file << text;
        for (int i = 0; i < N; i++) {
            if (str[i] != mark) {
                file << str[i];
            }
            else {
                file << std::endl;
                file.close();
                break;
            }
        }
        file << std::endl;
    }
    else{
        file << text << c << str << std::endl;
    }

    file.close();
    return true;
}


/// <summary>
/// Перемещает символы в строке до маркера
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <param name="mark"> - маркер </param>
void swap(strm& a, char mark){
    char temp = a.A[0];
    for (int i = 0; i < N; i++) {
        if (a.A[i+1] != mark) {
            a.A[i] = a.A[i + 1];
        }
        else {
            a.A[i] = temp;
        }
    }
}

/// <summary>
/// Ищет изначальную позицию маркера
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <returns></returns>

int poisk_pos(strm& a) {
    int o_pos = 0;

    while (a.A[o_pos] != a.mark)
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

//ПЕРЕДЕЛАТЬ!
void process(strm& a, int o_pos, int n_pos, char mark)
{
    int len = o_pos;
    while (o_pos != n_pos) {
        swap(a, len);
        o_pos--;
    }
    outp("Результат : ", a.A, ' ', mark);

}

/// <summary>
/// Функция ввода из файла
/// </summary>
/// <param name="a"> - структура {маркер ; строка с маркером} </param>
/// <returns></returns>

//ПЕРЕДЕЛАТЬ!
bool inp(strm& a) {
    int file_num = 1;
    std::ifstream file("C:\\Users\\Анечка\\Documents\\in1.txt", std::ios::in);

    char stop;
    char c;

    if (!file.is_open()) {
        std::cout << "Ошибка открытия входного файла";
        return false;
    }
    

    //читает построчно файл, считывает маркеты и ограничители, читает строки, если что-то не так, то выдает ошибки
    while (!(file.eof())) {
        char n = file_num + '0';
        outp("Cтрока №", "", n);


        file.get(a.mark);
        if (a.mark == '\n') {
            outp("Ошибка - пустая строка", "", ' ');
            file_num++;
            outp("----------------", "", ' ');
            continue;
        }

        file.get(stop);
        if (stop == '\n') {
            outp("Ошибка - нет ограничителя", "", ' ');
            file_num++;
            outp("----------------", "", ' ');
            continue;
        }

        unsigned i = 0;
        bool flag = false;

        while (file.get(c)) {
            if (c == stop || c == a.mark) break;
            if (c == '\n' || file.eof()) {
                file_num++;
                outp("Ошибка - в строке нет маркера и ограничителя", "", ' ');
                outp("----------------", "", ' ');
                flag = true;
                break;

            }

            a.A[i] = c;
            i++;
            if (i > N) {
                outp("Ошибка - в строке больше 100 символов", "", ' ');
                file_num++;
                outp("----------------", "", ' ');
                flag = true;
                break;
            }     
            
        }

        //Пропускает остаток строки и переходит на следующую строчку
        if (flag) { 
            while (file.get(c)) {
                if (c == '\n') break;
                if (file.eof()) return true;
            }
            continue;
        }

        if (i == 0) {
            outp("Ошибка - пустая строка", "", ' ');
            return 0;
        }
        if (i == N) {
            outp("В строке ровно 100 символов", "", ' ');
            a.A[i] = a.mark;
        }
        if(i < N){
            a.A[i] = a.mark;
            a.A[i + 1] = '\0';
        }

        outp("Маркер: ", "", a.mark);
        outp("Ограничитель: ", "", stop);
        outp("Строка: ", a.A, ' ');

        while (file.get(c) && !(file.eof())) {
            if (c == '\n') break;
            if (file.eof()) return true;
        }

        file_num++;


        int o_pos = poisk_pos(a);
        int n_pos = (poisk_pos(a)) / 2 + (poisk_pos(a)) % 2;
        process(a, o_pos, n_pos);

        outp("----------------", "", ' ');


    }
    file.close();
    return true;
}

int main() {
    clear_File();
    

    setlocale(LC_ALL, "ru");
    strm file;
    if (!(inp(file))) return 0;

    return 0;
}