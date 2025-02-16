#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main()
{
    srand(time(NULL));//seeding the random function using time

//  int random_num=rand();
//  printf("random_num=%d\n",random_num);
    int random_num_in_range=rand()%(100+1);//here 100 is the limit
    printf("random_num_in_range=%d\n",random_num_in_range);
    printf("WELCOME TO GUES NUMBER GAME\n");
    printf("gues the number\n");
    int run =1;
    int guess;

    while (run) {
        scanf("%d",&guess);
        if (guess<random_num_in_range) {
            printf("guess a higher number\n");

        }else if (guess>random_num_in_range) {
            printf("guess a lower number\n");
        
        }else if (guess==random_num_in_range) {
            printf("Congrats you guessed the number\n");
            run=0;
        
        }
    
    }
    return 0;
}
