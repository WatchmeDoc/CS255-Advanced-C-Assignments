## Assignment 5: C and Assembly Code Tutorial: Computing Sums


*  **Task 1:**

a. 
The program prints: 
`The sum from 0 to 1000 is 500500`

d. 
Main function has **19 instructions** (including L1 and L2 blocks, counting up until
ret instruction, excluding the further 2 instructions **"xchg"** - **including** them 
adds **up to 21 instructions** in total). Those instructions take space up to **59 bytes** 
(**64**, **including** the further **2 "xchg" instructions** after "ret").

To add a breakpoint at line 32 - right after L1 block, use `b *main + 28`
(thus **offset = 28**).

e.


| Variable Name | Value | Address | 
| ------ | ------ | ------ |
| S | 500500 | 0x4202528 |
| Msg | "The sum from 0 to %d is %d\n" | 0x402024 |

After changing the contents of S to 99, the program prints: `The sum from 0 to 1000 is 99` 


*  **Task 2:**

a. 
The program prints: `The sum from 0 to 1000 is 500500`

d. 
Main function has **34 instructions**, taking space up to **110 bytes**.

To add a breakpoint at line 14 - right after while loop ends, use
`b 14` (thus **offset = 14**).


e.

| Variable Name | Value | Address |
| ------ | ------ | ------ |
| Sum | 500500 | 0x402024 |
| n | -1 | 0x40201c |

After changing the contents of both Sum and on its address location, the message
printed by the program is still the same:
`The sum from 0 to 1000 is 500500`

f. 
The program now prints:
`The sum from 0 to 1000 is 495450`


* **Task 3:**

a.   
The program prints:
`The sum from 0 to 1000 is 500500`

b. 
Main has **25 instructions**.

c. 
After changing the variable names, the program prints:
`The sum from 0 to 1000 is 500500`


