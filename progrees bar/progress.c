#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


typedef struct{
int id;
float progress;
int step;
}Task ;

const int BAR_LENGHT=50;
const int NO_OF_TASK=5;


void print_bar(Task task);//Task namm ka struct jo task as  var use
int main()
{
    Task tasks[NO_OF_TASK];//array that contain instance of the struct is being made 
    srand(time(NULL));

    for (int i=0;i<NO_OF_TASK;i++) {//initializing the the tasks
        tasks[i].id=i+1;
        tasks[i].progress=0;
        tasks[i].step=rand() % 5 + 1;
}
    int task_incomplete=1;
    while(task_incomplete){
        task_incomplete=0;
        system("clear");//we clear after every update 

        for (int i=0;i<NO_OF_TASK;i++) {//updating the progrees bar every sec
            tasks[i].progress+=tasks[i].step;
            if (tasks[i].progress<100) {
                task_incomplete=1;

            }else if (tasks[i].progress>100) {
                tasks[i].progress=100;
            
            }
        print_bar(tasks[i]);//printing every task afteradding the progress
        }
        sleep(1);
    }
    printf("all task complete");
      return 0;
}

void print_bar(Task task){
    int bar_to_show=(task.progress/100)*BAR_LENGHT;

    printf("Task %d: [",task.id);

    for (int i=1;i<BAR_LENGHT;i++) {
        if (i<bar_to_show) {
            printf("=");
        
        }else {
        printf(" ");
        }

    }

    printf("] %.2f%%\n",task.progress);
}
