#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*В файле записан текст стихотворения. Форматировать текст так,
чтобы каждый куплет из 4 строк следовал с одной и той же позиции,
начинался с прописной буквы и был сдвинут относительно предыдущего
куплета на 5 позиций вправо или влево поочередно. */

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

    puts("Hello world!");
    return EXIT_SUCCESS;
}
