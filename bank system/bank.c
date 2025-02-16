#include <stdio.h>
void createCsvfileifnot() { FILE *file = fopen("bank", const char *) }
int main() {
  int run = 1;
  int option;

  createCsvfileifnot();
  printf("**** Banking system ****\n");
  while (run) {
    printf("1.Create Account\n2.Deposit Money\n3.Withdraw money\n4.check "
           "balance\n5.exit\nEnter your option:");
    scanf("%d", &option);
    switch (option) {
    case 1:
      printf("Account Created\n");
      break;
    case 2:
      printf("Money depositted\n");
      break;
    case 3:
      printf("Money gone\n");
      break;
    case 4:
      printf("no money\n");
      break;
    case 5:
      printf("Thanks for Banking\n");
      run = 0;
      break;
    default:
      printf("Wrong option\n");
    }
  }
  return 0;
}
