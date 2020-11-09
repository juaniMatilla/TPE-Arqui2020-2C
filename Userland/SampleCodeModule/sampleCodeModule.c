/* sampleCodeModule.c */
#include <shell.h>

char * v = (char*)0xB8000 + 79 * 2;

int main() {

	print("%d",StartShell(0));
	playchess();
	return 0;

}