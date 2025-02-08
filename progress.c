#include <stdio.h>

const int BAR_LENGHT=50;
int main()
{
    int id=3;
    float progress=50;
    int bar_to_show=(progress/100)*BAR_LENGHT;

    printf("\nTask %d: [",id);

    for (int i=1;i<BAR_LENGHT;i++) {
        if (i<bar_to_show) {
            printf("=");
        
        }else {
        printf(" ");
        }

    }

    printf("] %.2f%%\n",progress);

    return 0;
}
