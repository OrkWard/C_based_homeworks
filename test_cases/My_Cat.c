#include <stdio.h>
#include <unistd.h>

void copyfile(FILE *in, FILE *out) {
	int ch;

	while((ch = fgetc(in)) != EOF) {
		fputc(ch, out);
	}
}

int main(int argc, char **argv) {
	int i;
	FILE *fileptr;

	for (i = 1; i < argc; i++) {
		fileptr = fopen(argv[i], "r");

		if (fileptr != NULL) {
			copyfile(fileptr, stdout);
			fclose(fileptr);
		}
	}

	return 0;
}