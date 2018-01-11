#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char * array;
int size;

int readInput(char ** text, int * length, int enterEnds, int * eof) {
    int occupied = 0;

    *length = 20;
    *eof=0;

    if ((*text = (char *)malloc(*length * sizeof(int))) == NULL)
        return 0;

    int c, last = '.';
    int lastEnter = 0;

    while(1) {
        c = fgetc(stdin);
        if(c == EOF) {
            *eof=1;
            break;
        }

        if (enterEnds && c == '\n')
            break;

        if (c == '\n' && lastEnter)
            break;

        if (c == '\n')
            lastEnter=1;
        else
            lastEnter=0;

        if ((c == ' ' && last == ' ') || (c== ' ' && last == '\n'))
            continue;

        if (!isalpha(c) && c != ' ' && c != '\n') {
            if (last != ' ' && last != '\n') {
                (*text)[occupied++] = ' ';
                last = ' ';
            }
            continue;
        }

        if (c == '\n' && last != ' ' && last != '\n')
        {
            (*text)[occupied++] = ' ';

            if (occupied >= *length)
            {
                if ((*text = (char *)realloc(*text,((*length)*=2) * sizeof(int))) == NULL)
                    return 0;
            }
            (*text)[occupied++] = '\n';
            last=' ';
            continue;
        }else
            last = c;

        if (occupied == 0 && (c == '\n' || c == ' '))
            continue;

        if (occupied >= *length)
        {
            if ((*text = (char *)realloc(*text,((*length)*=2) * sizeof(int))) == NULL)
                return 0;
        }

        (*text)[occupied++]= (char)tolower((char)c);

        if (occupied >= *length)
        {
            if ((*text = (char *)realloc(*text,((*length)*=2) * sizeof(int))) == NULL)
                return 0;
        }

    }

    (*text)[occupied] = '\0';

    return 1;
}

void printResult(int * lines, int count)
{
    if (count == 0)
    {
        printf("Nenalezeno\n");
        return;
    }

    printf("Nalezeno:");

    for (int i = 0; i < count-1; ++i) {
        printf(" %d,", lines[i]);
    }
    printf(" %d\n",lines[count-1]);
}

int handleQueries()
{
    printf("Hledani:\n");

    int querySize;
    char * searchString;
    int foundLineSize,occupiedFoundLines;
    int *foundLines;
    int eof = 0;
    int actualFindLine;

    int line;
    char *arrayIterator, *searchIterator;

    char lastChar;

    while(1) {
        if (!readInput(&searchString, &querySize, 1, &eof))
            return 0;

        if (!*searchString && eof)
            break;

        if (!*searchString)
        {
            free(searchString);
            printf("Neplatny dotaz\n");
            continue;
        }

        foundLineSize = 20;
        occupiedFoundLines = 0;
        if ((foundLines = (int *) malloc(foundLineSize * sizeof(int))) == NULL)
            return 0;

        line = 1;
        arrayIterator = array;
        searchIterator = searchString;

        lastChar = ' ';
        actualFindLine = -1;

        for (; *arrayIterator; arrayIterator++) {
            if (*arrayIterator == '\n') {
                lastChar = ' ';
                line++;
                continue;
            }

            //printf("array:%c, search:%c\n", *arrayIterator, *searchIterator);

            if (*arrayIterator == *searchIterator && (lastChar == ' ' || searchIterator != searchString)) {
                searchIterator++;

                if (actualFindLine == -1)
                    actualFindLine = line;

                while (*searchIterator == '\n') {
                    searchIterator++;
                }

                if (*searchIterator == '\0') {
                    if (*(arrayIterator+1) != ' ' && *(arrayIterator+1) != '\0')
                    {
                        actualFindLine = -1;

                        searchIterator = searchString;

                        continue;
                    }
                    if (occupiedFoundLines >= foundLineSize)
                        if ((foundLines = (int *) realloc(foundLines, (foundLineSize *= 2) * sizeof(int))) == NULL)
                            return 0;

                    foundLines[occupiedFoundLines++] = actualFindLine;

                    actualFindLine = -1;

                    searchIterator = searchString;
                }
            } else {
                searchIterator = searchString;
                actualFindLine = -1;
            }

            lastChar = *arrayIterator;
        }

        printResult(foundLines, occupiedFoundLines);

        free(foundLines);
        free(searchString);
    }
    free(searchString);

    return 1;

}

int main() {
    printf("Text:\n");
    int eof = 0;
    if (!readInput(&array, &size,0, &eof)) {
        free(array);
        return 1;
    }

    if (eof)
    {
        printf("Nespravny vstup.\n");
        free(array);
        return 1;
    }

    //printf("%s",array);

    if (!handleQueries()) {
        free(array);
        return 1;
    }

    free(array);

    return 0;
}