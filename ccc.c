#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

char currentRole[20];
char currentUser[50];

int loginSystem();
void mainMenu();
void adminMenu();
void userMenu();
void staffMenu();
void guestMenu();

void addStudent();
void displayStudents();
void universalSearchStudent();
void updateStudent();
void deleteStudent();


// ===========================================
//                MAIN FUNCTION
// ===========================================
int main() {
    if (loginSystem()) {
        mainMenu();
    } else {
        printf("\nAccess Denied. Exiting...\n");
    }
    return 0;
}


// ===========================================
//               LOGIN SYSTEM
// ===========================================
int loginSystem() {
    char username[50], password[50];
    char fileUser[50], filePass[50], fileRole[20];
    int attempts = 3;

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (!fp) {
        printf("Error: credentials.txt not found!\n");
        return 0;
    }

    while (attempts > 0) {
        printf("===== LOGIN =====\n");

        printf("Username: ");
        scanf("%s", username);

        printf("Password: ");

        int i = 0;
        char ch;
        while (1) {
            ch = getch();
            if (ch == 13) { // ENTER KEY
                password[i] = '\0';
                break;
            } else if (ch == 8) { // BACKSPACE
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            } else {
                password[i++] = ch;
                printf("*");
            }
        }
        printf("\n");

        rewind(fp);

        while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
            if (strcmp(username, fileUser) == 0 &&
                strcmp(password, filePass) == 0) {

                strcpy(currentRole, fileRole);
                strcpy(currentUser, fileUser);

                fclose(fp);
                return 1; 
            }
        }

        attempts--;
        printf("\nIncorrect username or password! Attempts left: %d\n\n", attempts);
    }

    fclose(fp);
    return 0;
}


// ===========================================
//               MAIN MENU
// ===========================================
void mainMenu() {
    printf("\nLogged in as: %s (%s)\n", currentUser, currentRole);

    if (strcmp(currentRole, "ADMIN") == 0)
        adminMenu();
    else if (strcmp(currentRole, "USER") == 0)
        userMenu();
    else if (strcmp(currentRole, "STAFF") == 0)
        staffMenu();
    else
        guestMenu();
}


// ===========================================
//               ADMIN MENU
// ===========================================
void adminMenu() {
    int choice;
    do {
        printf("\n===== ADMIN MENU =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student (Universal)\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: universalSearchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}


// ===========================================
//           USER / STAFF / GUEST MENUS
// ===========================================
void userMenu() {
    int choice;
    do {
        printf("\n===== USER MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student (Universal)\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: universalSearchStudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

void staffMenu() {
    int choice;
    do {
        printf("\n===== STAFF MENU =====\n");
        printf("1. Display Students\n");
        printf("2. Search Student (Universal)\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayStudents(); break;
            case 2: universalSearchStudent(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    } while (1);
}

void guestMenu() {
    printf("\n===== GUEST MENU =====\n");
    displayStudents();
    printf("\nReturning to main menu...\n");
}


// ===========================================
//              ADD STUDENT
// ===========================================
void addStudent() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "a");

    printf("Enter Roll No: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fprintf(fp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}


// ===========================================
//             DISPLAY STUDENTS
// ===========================================
void displayStudents() {
    struct Student s;
    FILE *fp = fopen(STUDENT_FILE, "r");

    if (!fp) {
        printf("No student records found.\n");
        return;
    }

    printf("\n===== STUDENT LIST =====\n");
    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
}


// ===========================================
//         UNIVERSAL SEARCH STUDENT
// ===========================================
void universalSearchStudent() {
    char key[50];
    struct Student s;

    printf("Enter ANYTHING to search (roll, name, marks): ");
    scanf("%s", key);

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No students found.\n");
        return;
    }

    int found = 0;
    printf("\n===== SEARCH RESULTS =====\n");

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        char temp[100];
        sprintf(temp, "%d %s %.2f", s.roll, s.name, s.marks);

        if (strstr(temp, key) != NULL) {
            found = 1;
            printf("Roll: %d | Name: %s | Marks: %.2f\n",
                   s.roll, s.name, s.marks);
        }
    }

    if (!found)
        printf("No matching results found.\n");

    fclose(fp);
}


// ===========================================
//             UPDATE STUDENT
// ===========================================
void updateStudent() {
    int roll, found = 0;
    struct Student s;

    printf("Enter roll to update: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll == roll) {
            found = 1;
            printf("Enter new name: ");
            scanf("%s", s.name);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
        }
        fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Student updated successfully.\n");
    else
        printf("Student not found.\n");
}


// ===========================================
//             DELETE STUDENT
// ===========================================
void deleteStudent() {
    int roll, found = 0;
    struct Student s;

    printf("Enter roll to delete: ");
    scanf("%d", &roll);

    FILE *fp = fopen(STUDENT_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    while (fscanf(fp, "%d %s %f", &s.roll, s.name, &s.marks) == 3) {
        if (s.roll != roll) {
            fprintf(temp, "%d %s %.2f\n", s.roll, s.name, s.marks);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(STUDENT_FILE);
    rename("temp.txt", STUDENT_FILE);

    if (found)
        printf("Student deleted successfully.\n");
    else
        printf("Student not found.\n");
}

