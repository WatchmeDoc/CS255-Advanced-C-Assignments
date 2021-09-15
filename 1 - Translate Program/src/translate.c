#include <stdio.h>
#include <stdlib.h>

char **initialize_map(char *[3]);

void map_character(int, char *[], int);
void map_double_character(int, char *[], int);
void map_previous_character(int, char *[], int);

enum
{
    SINGLE_LETTER = 0,
    DUAL_LETTER = 1,
    PREVIOUS_LETTER = 2
} state;

int main()
{
    int c, prev_char = '\0';
    char *map[3];
    void (*character_insertion[])(int, char *[], int) = {map_character, map_double_character, map_previous_character};
    initialize_map(map);
    /* Array of Functions for the bonus part of the assignment :) */
    state = SINGLE_LETTER;
    while (1)
    {
        c = getchar();
        if (c == EOF)
        { /* If we got an EOF, we must check if we have a letter waiting to be printed, otherwise we just break */
            if (state == DUAL_LETTER)
            {
                state = PREVIOUS_LETTER;
            }
            else
            {
                break;
            }
        }
        if (c == 236 || c == 237 || c == 204 || c == 205)
        { /* POTENTIAL DOUBLE LETTER - MAPS EITHER TO M OR N  */
            if (state == DUAL_LETTER)
            { /* If we got a second DUAL_LETTER, we must print the previous one before moving to the next one. */
                state = PREVIOUS_LETTER;
            }
            else
            { /* if its the first potential dual letter, we just change the state of this "FSM" and read the next character. */
                state = DUAL_LETTER;
                prev_char = c;
                continue;
            }
        }

        (*character_insertion[state])(c, map, prev_char);
        prev_char = c;
        if (prev_char == EOF)
        { /* Case where the last letter was a potential dual letter, so we just printed it and break after EOF. */
            break;
        }
        if (state == PREVIOUS_LETTER)
        { /* If the state was in Previous Letter it means that we read a 2nd potential Dual Letter, 
            thus we need to change the state back into Dual Letter */
            state = DUAL_LETTER;
        }
        else
        { /* Otherwise we just go back into single letter. */
            state = SINGLE_LETTER;
        }
    }

    return 0;
}

char **initialize_map(char *map[3])
{
    /* 
    Note how 210 number has no match in ISO 8859-7
    */
    map[0] = "'\0'''\0'\0''iAVGDEZH8IKLMNKOPR\0STYFXPW\"\"aehiyavgdezh8iklmnkoprsstyfxpwiyoyw";
    map[1] = "A\0EHI\0O\0YW'\0\0\0\0\0\0\0\0\0\0\0\0\0S\0\0\0\0\0\0\0\0\0S\0IY'''''\0\0\0\0\0\0\0\0\0\0\0\0\0s\0\0\0\0\0\0\0\0\0s\0\"\"'''";
    map[2] = "\0\0\0\0\0\0\0\0\0\0\"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\"\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";
    return map;
}

void map_character(int c, char *map[], int prev_char)
{ /* PRINT THE PROPER GREEK LETTER */
    int i, index = c % 182;
    if (c < 182 || c > 254)
    { /* IF IT IS NOT A GREEK LETTER JUST PRINT AND WE ARE OUT */
        putchar(c);
        return;
    }
    for (i = 0; i < 3; i++)
    { /* ELSE WE PRINT ALL 3 CHARACTERS */
        char tmp = map[i][index];
        if (tmp == '\0')
        { /*IF IT IS THE EMPTY CHARACTER, JUST BREAK BECAUSE WE PRINTED ALL NECESSARY CHARACTERS*/
            break;
        }
        putchar(tmp);
    }
}

void map_double_character(int c, char *map[], int prev_char)
{
    if (c == 208 || c == 240)
    { /* Case its a MP or mP or Mp or mp */
        putchar(prev_char == 204 ? 'B' : 'b');
    }
    else if (c == 212 || c == 244)
    { /* Case its a NT or nT or Nt or nt */
        putchar(prev_char == 205 ? 'D' : 'd');
    }
    else
    {
        map_character(prev_char, map, c);
        map_character(c, map, prev_char);
    }
}

void map_previous_character(int c, char *map[], int prev_char)
{
    map_character(prev_char, map, c);
}
