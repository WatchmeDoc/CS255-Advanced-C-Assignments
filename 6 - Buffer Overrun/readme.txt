This assignment also runs on a 32-bit Unix environment, using C-99 GCC. This assignment basically
asked us to "hack" into hello executable using buffer overrun and alter the program's 
behavior. It's a simple program that asks for your name and if your name is Angelos Bilas
it assigns you with a grade of 6, otherwise 3. traces.txt is a helpful file which shows how the program's 
memory works.
 
We had 3 different goals and a bonus one as described below:

1. (createdata3.c) Make the program crash (Segmentation Fault)
2. (createdata6.c) Make the program print your name and a grade of 6
3. (createdata9.c) Make the program print your name and a grade of 9
4. (createdata10.c) Make the program print your name and a grade of 10 (Bonus) 

Note that buffer overrun violates articles no. 4 and 5, but also 2, 3, 7 and 8 of European Council's Convention on Cybercrime.
This assignment was done purely for educational purposes.

Now, to achieve those goals, one had to create a specific input and insert machine code into the program's memory,
for some of the parts. 

createdata3.c input injects my name and then alters the return
address of the readString function into any value, thus making the program crash.

createdata6.c input injects my name and then alters the return
address of the readString function into the address of "grade = '6'" command, thus
changing my grade into '6'.

createdata9.c input injects my name and then alters the return
address of the readString function into the address of the name buffer,
where machine language commands will be stored and executed, changing my grade into '9'
and then straight back into main function.

createdata10.c input injects my name and then alters the return
address of the readString function into the address of the name buffer,
where machine language commands will be stored and executed, basically
pushing an also injected string into stack before jumping to printf function call
in main, thus printing a similar con string with my name and a grade of '10', matching
the input. Note that the string contains tab characters to try and fit the newlines/con
the user while trying to look like a normal program execution. The pseudo-string was stored
in frame activation stack right after the function's arguments (check traces.txt file). Note
that this could have been done in a few other ways as well, either using execv function and
executing another executable, perhaps doing even more damage to the user (e.g. open a terminal)
which is illegal to do, or call putc instead of jumping onto the instruction which calls printf.