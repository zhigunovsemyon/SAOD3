#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/*В файле записан текст стихотворения. Форматировать текст так,
чтобы каждый куплет из 4 строк следовал с одной и той же позиции,
начинался с прописной буквы и был сдвинут относительно предыдущего
куплета на 5 позиций вправо или влево поочередно. */

//Функция, добавляющая вставку сдвига перед текстом
inline char const * Identation (bool const Ident){
	return (Ident) ? "     " : "";
}

//Вычисление длинны файла fptr
long FileLen(FILE *const fptr) {
    fseek(fptr, SEEK_SET, SEEK_END);
    long const len = ftell(fptr);
    rewind(fptr);
    return len;
}

//Вывод справки об использовании
void usage(char const * const filename) {
	printf("%s ПУТЬ_К_ФАЙЛУ\n", filename);
}

int main (int const argc, char const * const * const args) {
	//Вывод справки об использовании при неправильном вводе
	if (argc != 2) {
		usage(args[0]);
		return EXIT_SUCCESS;
	}

	//Открываемый файл с текстом
	FILE *src;
	//Открытие файла, вывод ошибки при неудаче
	if (NULL == (src = fopen(args[1], "rt"))){
		perror(args[1]);
		return EXIT_FAILURE;
	}

	fclose(src); //Закрытие файла
    puts("Hello world!");
    return EXIT_SUCCESS;
}
