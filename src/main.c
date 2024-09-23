#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*В файле записан текст стихотворения. Форматировать текст так,
чтобы каждый куплет из 4 строк следовал с одной и той же позиции,
начинался с прописной буквы и был сдвинут относительно предыдущего
куплета на 5 позиций вправо или влево поочередно. */

inline void PutIdent(void) {
    printf("     ");
}

// Вычисление длинны файла fptr
long FileLen(FILE *const fptr) {
    fseek(fptr, SEEK_SET, SEEK_END);
    long const len = ftell(fptr);
    rewind(fptr);
    return len;
}

// Вывод справки об использовании
void usage(char const *const filename) {
    printf("%s ПУТЬ_К_ФАЙЛУ\n", filename);
}

//Функция, в которой будет исполняться алгоритм используя файл src
void FormatAndPrint(FILE *const src) {
    // bool Ident = true;
    [[maybe_unused]] size_t line = 0;
    // bool FirstChar = true;
    while (true) {
        //Прочитанный символ
        int const curChar = fgetc(src);
        //Возможные действия с прочитанным символом
        switch (curChar) {
        case '\r'://Служебный символ возврата каретки, пропуск
            break;
        case EOF://Символ, сигнализирующий окончание файла, завершение работы
            return;
        case '\n'://Символ переноса строки
            line++;//Увеличение счётчика строк, вывод на экран (далее)
        default://Любой иной символ
            putchar(curChar);//Вывод
            break;//Переход на следующий виток цикла
        }
    }
}

int main(int const argc, char const *const *const args) {
    // Вывод справки об использовании при неправильном вводе
    if (argc != 2) {
        usage(args[0]);
        return EXIT_SUCCESS;
    }

    // Открываемый файл с текстом
    FILE *src;
    // Открытие файла, вывод ошибки при неудаче
    if (NULL == (src = fopen(args[1], "rt"))) {
        perror(args[1]);
        return EXIT_FAILURE;
    }

    FormatAndPrint(src);
    fclose(src); // Закрытие файла
    return EXIT_SUCCESS;
}
