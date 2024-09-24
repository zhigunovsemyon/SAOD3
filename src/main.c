#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*В файле записан текст стихотворения. Форматировать текст так,
чтобы каждый куплет из 4 строк следовал с одной и той же позиции,
начинался с прописной буквы и был сдвинут относительно предыдущего
куплета на 5 позиций вправо или влево поочередно. */

/*Дополнительное задание повышенной сложности.
• Обработку файла сделать на основе блочной парадигмы. При
этом программа должна работать при любом размере файла и
любом размере абзаца.
• Обязательно учесть в программе, что между словами могут
находиться несколько пробелов, в тексте могут встречаться
пустые абзацы (несколько подряд идущих переводов строк),
могут попадаться цифры и числа. В выходном файле лишние
пробелы и переводы строк должны отсутствовать.
• Программа должна быть регисторнезависимой, т.е. большая и
маленькая буква считаются одной и той же (если обратного не
предусмотрено индивидуальным заданием).
• Название входного и выходного файлов, а также все
необходимые переменные, должны запрашиваться у
пользователя.
• Необходимо уметь обосновать выбранные размеры переменных и
временных буферов. */

#define DEFAULT_COUPLET_SIZE 4
#define COUPLETSIZE_KEY "--coupletsize"

int GetCoupletSize (int const argc, char const *const *const args) {
	int coupletsize = DEFAULT_COUPLET_SIZE;
	if (argc == 2)
		return coupletsize;
	if (argc != 4)
		return -1;

	if (0 != strcmp(args[1], COUPLETSIZE_KEY))
		return -1;
	
	if (1 != sscanf(args[2], "%d", &coupletsize))
		return -1;

	if (coupletsize < 1)
		return -1;

	return coupletsize;
}

// Вывод справки об использовании
void usage(char const *const filename) {
    printf("%s ПУТЬ_К_ФАЙЛУ\n", filename);
}

// Функция, в которой будет исполняться алгоритм используя файл src
void FormatAndPrint(FILE *const src, size_t coupletsize) {
    bool Ident = false; // флаг необходимости сдвига строки
    size_t line = 1; // номер строки
    bool FirstChar = true; // Флаг того, первый ли символ в строке
    bool PrevSymbolWasSpace = false; // Флаг, был ли предыдущий символ пробелом
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
            if (line % coupletsize == 0)
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
            /*Если символ не был первым в строке, и является пробелом*/
            if (isspace(curChar)) {
                /*При этом предыдущий символ уже был пробелом,
                 * текущий символ пропускается*/
                if (PrevSymbolWasSpace == true) {
                    break;
                }
                // Если пробел первый в ряду, флаг поднимается, символ выводится
                PrevSymbolWasSpace = true;
            } else {
				//Если символ пробелом не является, флаг пробела сбрасывается
                PrevSymbolWasSpace = false;
            }
            putchar(curChar); // Вывод
            break; // Переход на следующий виток цикла
        }
    }
}

int main(int const argc, char const *const *const args) {
	int coupletsize = GetCoupletSize(argc, args);
    if (coupletsize < 1) {
        usage(args[0]);
        return EXIT_FAILURE;
    }

    // Открываемый файл с текстом
    FILE *src;
    // Открытие файла, вывод ошибки при неудаче
    if (NULL == (src = fopen(args[argc - 1], "rt"))) {
        perror(args[argc - 1]);
        return EXIT_FAILURE;
    }

    FormatAndPrint(src, (size_t)coupletsize);
    fclose(src); // Закрытие файла
    return EXIT_SUCCESS;
}
