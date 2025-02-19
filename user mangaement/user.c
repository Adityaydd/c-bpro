#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USER_LENGTH 100
#define MAX_LINE_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
typedef struct {
  char user[MAX_USER_LENGTH];
  char password[MAX_PASSWORD_LENGTH];
} User;

void writeCSV(User user[], int count) {
  FILE *file = fopen("user.csv", "w");
  if (!file) {
    printf("Cant open the file1");
    exit(1);
  }
  fprintf(file, "user,password\n");
  for (int i = 0; i < count; i++) {
    fprintf(file, "%s,%s\n", user[i].user, user[i].password);
  }
  fclose(file);
}

void createCSVfileifNot() {
  FILE *file = fopen("user.csv", "r");
  if (!file) {
    file = fopen("user.csv", "w");
    if (!file) {
      printf("cant create file");
      exit(1);
    }
    fprintf(file, "user,password\n"); // Write header
    fclose(file);

  } else {
    fclose(file);
  }
}

void add_user(User user[], int *count) {

  if (*count >= 100) {
    printf("The maxium entries are made");
    return;
  }
  printf("Enter Username:");
  scanf("%s", user[*count].user);
  printf("Enter your password:");
  scanf("%s", user[*count].password);
  (*count)++;
  writeCSV(user, *count);
  printf("Registration sucesfull\n");
}

void login(User user[], int count, char *user_name, char *user_pass) {
  for (int i = 0; i < count; i++) {
    if (strcmp(user[i].user, user_name) == 0 &&
        strcmp(user[i].password, user_pass) == 0) {
      printf("welcome %s\n", user_name);
      return;
    }
  }
  printf("The username or password is wrong");
}

void read_CSV(User users[], int *count) {
  FILE *file = fopen("user.csv", "r");
  if (!file) {
    printf("Cant open the file2");
    exit(1);
  }
  char line[MAX_LINE_LENGTH];
  fgets(line, sizeof(line), file);
  *count = 0;
  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "%[^,],%s", users[*count].user, users[*count].password);
    (*count)++;
  }
  fclose(file);
}
int main() {
  int run = 1;
  int count;
  int input;
  User users[100];
  char user_name[MAX_USER_LENGTH];
  char user_pass[MAX_USER_LENGTH];
  createCSVfileifNot();
  read_CSV(users, &count);

  printf("\nWelcome To user center\n\n");
  while (run) {
    printf("1.Login\n2.Register\n3.Quit\nEnter you option:");
    scanf("%d", &input);
    switch (input) {
    case 2:
      add_user(users, &count);
      break;
    case 1:
      printf("Enter your Username:");
      scanf("%s", user_name);
      printf("Enter your Password:");
      scanf("%s", user_pass);
      login(users, count, user_name, user_pass);
      break;
    case 3:
      run = 0;
      break;
    default:
      printf("wrong option");
    }
  }
  return 0;
}
