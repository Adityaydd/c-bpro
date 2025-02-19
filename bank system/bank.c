#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMER_LENGTH 50
#define MAX_LINE_LENGTH 100

typedef struct {
  char customer_name[MAX_CUSTOMER_LENGTH];
  int acc_num;
  int money;
} Customer;

void writeCSV(Customer customer[], int count) {
  FILE *file = fopen("bank.csv", "w");
  if (!file) {
    printf("Cant open the file");
    exit(1);
  }
  fprintf(file, "name,acc_num,money\n");
  for (int i = 0; i < count; i++) {
    fprintf(file, "%s,%d,%d\n", customer[i].customer_name, customer[i].acc_num,
            customer[i].money);
  }
  fclose(file);
}

void add_customer(Customer customer[], int *count) {
  if (*count >= 100) {
    printf("Sry we are full");
    return;
  }
  printf("Enter Username:");
  scanf("%s", customer[*count].customer_name);
  printf("Enter your Account Number:");
  scanf("%d", &customer[*count].acc_num);
  (*count)++;
  writeCSV(customer, *count);
  printf("Congrats you are now cuatomer of our bank");
}

void depositmoney(Customer customer[], char *customer_name, int money,
                  int acc_num, int *count) {
  for (int i = 0; i < (*count); i++) {
    if (strcmp(customer[i].customer_name, customer_name) == 0 &&
        customer[i].acc_num == acc_num) {
      customer[i].money += money;
      writeCSV(customer, *count);
    }
  }
}

void checkbalance(Customer customer[], char *customer_name, int acc_num,
                  int *count) {
  for (int i = 0; i < (*count); i++) {
    if (strcmp(customer[i].customer_name, customer_name) == 0 &&
        customer[i].acc_num == acc_num) {
      printf("Your balance is %d", customer[i].money);
      return;
    }
  }
}
void withdrawmoney(Customer customer[], char *customer_name, int money,
                   int acc_num, int *count) {
  for (int i = 0; i < (*count); i++) {
    if (strcmp(customer[i].customer_name, customer_name) == 0 &&
        customer[i].acc_num == acc_num) {
      if (customer[i].money < money) {
        printf("You dont have enough balance your balance is %d",
               customer[i].money);
        return;
      } else {
        customer[i].money -= money;
        writeCSV(customer, *count);
        printf("$%d withdrawn", money);
      }
    }
  }
}

void createCsvfileifnot() {
  FILE *file = fopen("bank.csv", "r");
  if (!file) {
    FILE *file = fopen("bank.csv", "w");
    if (!file) {
      printf("Cant create file");
    }
    fprintf(file, "name,acc_num,money");
    fclose(file);

  } else {
    fclose(file);
  }
}

void readCSV(Customer customers[], int *count) { // here count is a pointer
  FILE *file = fopen("bank.csv", "r");
  if (!file) {
    printf("Cant open the file");
    exit(1);
  }
  char line[MAX_LINE_LENGTH];
  fgets(line, sizeof(line), file);
  *count = 0;
  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "%[^,],%d,%d", customers[*count].customer_name,
           &customers[*count].acc_num, &customers[*count].money);
    (*count)++;
  }
  fclose(file);
}

int main() {
  int run = 1;
  int option;
  int count;
  char customer_name[MAX_CUSTOMER_LENGTH];
  int acc_num;
  int money;
  Customer customers[100];

  createCsvfileifnot();
  readCSV(customers, &count);
  printf("\n**** Banking system ****\n\n");
  while (run) {
    printf("1.Create Account\n2.Deposit Money\n3.Withdraw money\n4.check "
           "balance\n5.exit\nEnter your option:");
    scanf("%d", &option);
    switch (option) {
    case 1:
      add_customer(customers, &count);
      break;
    case 2:
      printf("Enter your name");
      scanf("%s", customer_name);
      printf("Enter your account Number");
      scanf("%d", &acc_num);
      printf("Enter your amount to be depositted");
      scanf("%d", &money);

      depositmoney(customers, customer_name, money, acc_num, &count);
      printf("\nMoney depositted\n");
      break;
    case 3:
      printf("Enter your name");
      scanf("%s", customer_name);
      printf("Enter your account Number");
      scanf("%d", &acc_num);
      printf("Enter your amount to Withdraw");
      scanf("%d", &money);
      withdrawmoney(customers, customer_name, money, acc_num, &count);
      printf("\nMoney gone\n");
      break;
    case 4:
      printf("Enter your name");
      scanf("%s", customer_name);
      printf("Enter your account Number");
      scanf("%d", &acc_num);
      checkbalance(customers, customer_name, acc_num, &count);
      printf("\nno money\n");
      break;
    case 5:
      printf("\nThanks for Banking\n");
      run = 0;
      break;
    default:
      printf("\nWrong option\n");
    }
  }
  return 0;
}
