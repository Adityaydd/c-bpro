#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#define MAX_NAME_LENGTH 50

typedef struct {
  char name[MAX_NAME_LENGTH];
  int age;
  int id;
} Person;

void createCSVIfNotExists() { // after the call the info of the people is filled
                              // in the people arr
  FILE *file = fopen("data.csv", "r"); // opening the file
  if (!file) {
    file = fopen("data.csv", "w");
    if (!file) {
      printf("Error creating file!\n");
      exit(1);
    }
    fprintf(file, "name,age,id\n"); // Write header
    fclose(file);
  } else {
    fclose(file);
  }
}

void readCSV(Person people[], int *count) {
  FILE *file =
      fopen("data.csv", "r"); // after the loop completes we have a array people
                              // filled with all the info of the people?
  if (!file) {
    printf("Error opening file!\n");
    exit(1);
  }

  char line[MAX_LINE_LENGTH];
  fgets(line, sizeof(line), file); // Skip the header line

  *count = 0;
  while (fgets(line, sizeof(line), file)) {
    sscanf(line, "%[^,],%d,%d", people[*count].name, &people[*count].age,
           &people[*count].id);
    (*count)++;
  }

  fclose(file);
}

void writeCSV(Person people[], int count) {
  FILE *file = fopen("data.csv", "w");
  if (!file) {
    printf("Error opening file!\n");
    exit(1);
  }

  fprintf(file, "name,age,id\n");
  for (int i = 0; i < count; i++) {
    fprintf(file, "%s,%d,%d\n", people[i].name, people[i].age, people[i].id);
  }

  fclose(file);
}

void searchPerson(Person people[], int count, char *name) {
  for (int i = 0; i < count; i++) {
    if (strcmp(people[i].name, name) == 0) {
      printf("Name: %s, Age: %d, ID: %d\n", people[i].name, people[i].age,
             people[i].id);
      return;
    }
  }
  printf("Person not found.\n");
}

void editID(Person people[], int count, char *name, int newID) {
  for (int i = 0; i < count; i++) {
    if (strcmp(people[i].name, name) == 0) {
      people[i].id = newID;
      printf("ID updated successfully.\n");
      writeCSV(people, count);
      return;
    }
  }
  printf("Person not found.\n");
}

void addPerson(Person people[], int *count) {
  if (*count >= 100) {
    printf("Cannot add more entries. Limit reached.\n");
    return;
  }

  printf("Enter name: ");           // here we are updating the arr people
  scanf("%s", people[*count].name); // no need for & cuz name is arr
  printf("Enter age: ");
  scanf("%d", &people[*count].age);
  printf("Enter ID: ");
  scanf("%d", &people[*count].id);

  (*count)++;
  writeCSV(people, *count); // and here we update the csv file
  printf("Person added successfully.\n");
}

int main() {
  Person people[100]; // Person is a struct and made an array name person that
                      // have 100 instances of that struct
  int count; // tracking the number of entries so we can see how many records
             // were read

  createCSVIfNotExists(); // Ensure the file exists
  readCSV(people, &count);

  char name[MAX_NAME_LENGTH];
  int choice, newID;

  while (1) {
    printf("\n1. Search for a person\n2. Edit ID of a person\n3. Add a new "
           "person\n4. Exit\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
      printf("Enter the name to search: ");
      scanf("%s", name);
      searchPerson(people, count, name);
    } else if (choice == 2) {
      printf("Enter the name to edit ID: ");
      scanf("%s", name);
      printf("Enter the new ID: ");
      scanf("%d", &newID);
      editID(people, count, name, newID);
    } else if (choice == 3) {
      addPerson(people, &count);
    } else if (choice == 4) {
      break;
    } else {
      printf("Invalid choice. Please try again.\n");
    }
  }

  return 0;
}
