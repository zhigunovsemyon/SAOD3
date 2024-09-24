#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
/*В файле записан текст стихотворения. Форматировать текст так,
чтобы каждый куплет из 4 строк следовал с одной и той же позиции,
начинался с прописной буквы и был сдвинут относительно предыдущего
куплета на 5 позиций вправо или влево поочередно. */

#define COUPLET 4

// Вывод справки об использовании
void usage(char const *const filename) {
    printf("%s ПУТЬ_К_ФАЙЛУ\n", filename);
}

// Функция, в которой будет исполняться алгоритм используя файл src
void FormatAndPrint(FILE *const src) {
    bool Ident = false; // флаг необходимости сдвига строки
    size_t line = 1; // номер строки
    bool FirstChar = true; // Флаг того, первый ли символ в строке
    while (true) {
        // Прочитанный символ
        int const curChar = fgetc(src);
        // Возможные действия с прочитанным символом
        switch (curChar) {
        case '\r': // Служебный символ возврата каретки, пропуск
            break;
        case EOF: // Символ, сигнализирующий окончание файла, завершение работы
            putchar('\n');
            return;
        case '\n': // Символ переноса строки
            /* Если перенос был первым символом в строке, то вся строка
            пропускается и не учитывается счётчиком */
            if (FirstChar) {
                break;
            }
            /*Увеличение счётчика строк, вывод на экран.
             *Если флаг сдвига поднят, вставляется промежуток*/
            line++;
            printf("\n%s", (Ident) ? "    " : "");
            // Каждую COUPLET строку флаг сдвига переворачивается
            if (line % COUPLET == 0)
                Ident = !Ident;
            FirstChar = true; // Подъём флага первого символа для следующего
            break;
        default: // Любой иной символ
            // Если символ первый в строке
            if (FirstChar) {
                /* И этот символ является пробелом, табуляцией,
                 * он пропускается */
                if (isspace(curChar))
                    break;
            }
            FirstChar = false; // Сброс флага первенства в строке
            putchar(curChar); // Вывод
            break; // Переход на следующий виток цикла
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
