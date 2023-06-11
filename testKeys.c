#include <stdio.h>
#include <conio.h>

/* Press Esc to quit */
#define ESC 27
int main()
{
    int ch;
    while ((ch=getch()) != ESC)
    {
        printf("%d",ch);
        while (kbhit())
        {
            printf(" %d",getch());
        }
        printf("\n");
    }
    printf("ESC %d\n",ch);
    return 0;
}