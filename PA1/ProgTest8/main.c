#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TEmployee
{
    struct TEmployee         * m_Next;
    struct TEmployee         * m_Bak;
    char                     * m_Name;
} TEMPLOYEE;

#endif /* __PROGTEST__ */

TEMPLOYEE        * newEmployee  ( const char      * name,
                                  TEMPLOYEE       * next )
{
    TEMPLOYEE * temployee = (TEMPLOYEE *)malloc(sizeof(TEMPLOYEE));
    temployee->m_Bak = NULL;
    temployee->m_Name = strdup(name);
    temployee->m_Next = next;
    return temployee;
}

TEMPLOYEE        * cloneList    ( TEMPLOYEE       * src )
{
    if (src == NULL)
        return NULL;

    TEMPLOYEE * iterator = src;
    TEMPLOYEE * newList;
    TEMPLOYEE * newIterator;

    while(iterator != NULL)
    {
        TEMPLOYEE * newEmployee = (TEMPLOYEE *) malloc(sizeof(TEMPLOYEE));
        memcpy(newEmployee,iterator, sizeof(TEMPLOYEE));
        iterator->m_Next = newEmployee;

        iterator = newEmployee->m_Next;
    }

    iterator = src->m_Next;
    while (iterator != NULL)
    {
        if (iterator->m_Bak!=NULL)
            iterator->m_Bak = iterator->m_Bak->m_Next;
        iterator->m_Name = strdup(iterator->m_Name);

        if (iterator->m_Next != NULL)
            iterator = iterator->m_Next->m_Next;
        else
            iterator = NULL;
    }

    newList = src->m_Next;
    newIterator = newList;
    src->m_Next = src->m_Next->m_Next;
    iterator = src->m_Next;

    while(iterator != NULL) {
        newIterator->m_Next = iterator->m_Next;
        newIterator = newIterator->m_Next;

        iterator->m_Next = iterator->m_Next->m_Next;
        iterator = iterator->m_Next;
    }

    return newList;

}
void               freeList     ( TEMPLOYEE       * src )
{
    if (src == NULL)
        return;

    freeList(src->m_Next);

    free(src->m_Name);

    free(src);
}

#ifndef __PROGTEST__
int                main         ( int               argc,
                                  char            * argv [] )
{
    TEMPLOYEE * a, *b;
    char tmp[100];

    /*removed asserts*/
    return 0;
}
#endif /* __PROGTEST__ */
