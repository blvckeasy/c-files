#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  char name[16];
  char surname[32];
  int birth_date[3];
  bool gender;
} User;

void printUser(User *odam) {
  printf("name: %s\n", odam->name);
  printf("surname: %s\n", odam->surname);
  printf("birth date: [%d, %d, %d]\n", odam->birth_date[0], odam->birth_date[1], odam->birth_date[2]);
  printf("gender: %s\n", odam->gender ? "Erkak" : "Ayol");
  puts("");
}

void printUsers(User *odamlar, int length) {
  for (int i = 0; i < length; i++) {
    printUser(&odamlar[i]);
  }
}

void printMaleUsers(User *odamlar, int length) {
  for (int i = 0; i < length; i++) {
    if (odamlar[i].gender == true) {
      printUser(&odamlar[i]);
    }
  }
}

void addFemaleUsersToFile(User *odamlar, int length) {
  FILE *file = fopen("./database/female.txt", "a");

  for(int i = 0; i < length; i++) {
    if (odamlar[i].gender == false) {
      fprintf(file, "%s ", odamlar[i].name);
      fprintf(file, "%s ", odamlar[i].surname);
      fprintf(file, "%d.%d.%d ", odamlar[i].birth_date[0], odamlar[i].birth_date[1], odamlar[i].birth_date[2]);
      fprintf(file, "%s\n", odamlar[i].gender ? "Erkak" : "Ayol");
    }
  }

  printf("Ayollar malumoti yozildi.\n");
}

void printFemaleUsers(User *odamlar, int length) {
  for (int i = 0; i < length; i++) {
    if (odamlar[i].gender == false) {
      printUser(&odamlar[i]);
    }
  }
}

void sortByBirthYear(User *odamlar, int length) {
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (odamlar[i].birth_date[2] > odamlar[j].birth_date[2]) {
        User temp = odamlar[i];
        odamlar[i] = odamlar[j];
        odamlar[j] = temp;
      }
    }
  }
}

void sortBySurname(User *odamlar, int length) {
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (strcmp(odamlar[i].surname, odamlar[j].surname) > 0) {
        User temp = odamlar[i];
        odamlar[i] = odamlar[j];
        odamlar[j] = temp;
      }
    }
  }
}

void sortByName(User *odamlar, int length) {
  for (int i = 0; i < length; i++) {
    for (int j = i + 1; j < length; j++) {
      if (strcmp(odamlar[i].name, odamlar[j].name) > 0) {
        User temp = odamlar[i];
        odamlar[i] = odamlar[j];
        odamlar[j] = temp;
      }
    }
  }
}

void addMaleUsersToFile(User *odamlar, int length) {
  FILE *file = fopen("./database/male.txt", "a");

  for(int i = 0; i < length; i++) {
    if (odamlar[i].gender == true) {
      fprintf(file, "%s ", odamlar[i].name);
      fprintf(file, "%s ", odamlar[i].surname);
      fprintf(file, "%d.%d.%d ", odamlar[i].birth_date[0], odamlar[i].birth_date[1], odamlar[i].birth_date[2]);
      fprintf(file, "%s\n", odamlar[i].gender ? "Erkak" : "Ayol");
    }
  }

  printf("Erkaklar malumoti yozildi.\n");
}

void addSortedBySurnameUsersToFile(User *odamlar, int length) {
  FILE *file = fopen("./database/sort_from_surname.txt", "a");
  
  sortBySurname(odamlar, length);

  for (int i = 0; i < length; i++) {
    fprintf(file, "%s ", odamlar[i].surname);
    fprintf(file, "%s ", odamlar[i].name);
    fprintf(file, "%d.%d.%d ", odamlar[i].birth_date[0], odamlar[i].birth_date[1], odamlar[i].birth_date[2]);
    fprintf(file, "%s\n", odamlar[i].gender ? "Erkak" : "Ayol");
  }
  puts("Sortlab yozib qo'yildi.");
}

int main() {
  system("cls");

  User *odamlar = (User*)malloc(0*sizeof(User));
  int length = 0;
  FILE *file = fopen("database/users.txt", "r");

  for (int i = 0; !feof(file); i++) {
    odamlar = realloc(odamlar, (length + 1)*sizeof(User));

    fscanf(file, "%s", odamlar[i].name);
    fscanf(file, "%s", odamlar[i].surname);
    fscanf(file, "%d.%d.%d", &odamlar[i].birth_date[0], &odamlar[i].birth_date[1], &odamlar[i].birth_date[2]);
    
    char gender[6];
    fscanf(file, "%s", gender);
    if (!strcmp(gender, "Ayol")) {
      odamlar[i].gender = false;
    } else {
      odamlar[i].gender = true;
    }
    length++;
  }

  // addFemaleUsersToFile(odamlar, length);
  // addMaleUsersToFile(odamlar, length);

  addSortedBySurnameUsersToFile(odamlar, length);

  return 0;
}