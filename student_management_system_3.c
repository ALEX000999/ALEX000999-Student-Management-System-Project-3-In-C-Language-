#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mainmenu();
void addstudent();
void viewstudent();
void searchstudent();
void updatestudent();

struct students {
    char student_name[50];
    int id_no;
    int mobile_no;
    char department[3];
    float cgpa;
    char gender[6];
    int age;
};

int main() {
    printf("\n\t***** Students Records Management System *****\n\n");
    printf("\tPRESS ENTER KEY TO CONTINUE.\n");
    getchar();
    mainmenu();
    return 0;
}

void mainmenu() {
    int choice;

    printf("\n\n***** MAIN MENU *****\n\n");
    printf("Enter Your Choice Number.\n\n");
    printf("1: Add Student Record\n");
    printf("2: Search Student Record\n");
    printf("3: Modify Student Record\n");
    printf("4: View Student Record\n");
    printf("5: Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addstudent();
            break;
        case 2:
            searchstudent();
            break;
        case 3:
            updatestudent();
            break;
        case 4:
            viewstudent();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Invalid Choice.\n");
    }
    mainmenu();
}

void addstudent() 
{
    FILE *fp;
    struct students std;
    char another = 'y';
    

    fp = fopen("file.txt", "ab+");
    if (fp == NULL) {
        printf("File Not Opening");
        exit(1);
    }
    while (another == 'y') {
        printf("\n***** ADD STUDENT RECORD *****\n");
        printf("Enter Details Of Student.\n");

        printf("Enter Student Name : \n");
        scanf("%s", std.student_name);

        printf("Enter Student ID No : \n");
        scanf("%d", &std.id_no);

        printf("Enter Student Mobile Number : \n");
        scanf("%d", &std.mobile_no);

        printf("Enter Student Department (BBA/CSE/EEE/MSJ): \n");
        scanf("%s", std.department);

        printf("Enter Student CGPA: \n");
        scanf("%f", &std.cgpa);

        printf("Enter Student Gender (Male/Female): \n");
        scanf("%s", std.gender);

        printf("Enter Student Age : \n");
        scanf("%d", &std.age);

        fwrite(&std, sizeof(std), 1, fp);
        printf("If you Want to add another record? Then type 'y' else 'n'.\n");
        fflush(stdin);
        scanf(" %c", &another);
    }
    fclose(fp);
    
    
    
    
    mainmenu();
}

void searchstudent() 
{
    FILE *fp;
    struct students std;
    int id_num, found = 0;

    printf("\n***** SEARCH STUDENT RECORD *****\n");

    printf("Enter Student ID Number To Search: \n");
    scanf("%d", &id_num);

    fp = fopen("file.txt", "rb");

    if (fp == NULL) {
        printf("File Not Opening\n");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (std.id_no == id_num) {
            printf("Student Name: %s\n", std.student_name);
            printf("Student ID No: %d\n", std.id_no);
            printf("Student Mobile Number: %d\n", std.mobile_no);
            printf("Student Department: %s\n", std.department);
            printf("Student CGPA: %.2f\n", std.cgpa);
            printf("Student Gender: %s\n", std.gender);
            printf("Student Age: %d\n", std.age);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("ID Number %d Not Found.\n", id_num);
    }

    fclose(fp);

    

    

    mainmenu();
}

void updatestudent() 
{
    int id_num, found = 0;
    FILE *fp, *temp_fp;
    struct students std;
     

    printf("\n***** UPDATE STUDENT RECORD *****\n");

    printf("Enter Student ID Number To Update: \n");
    scanf("%d", &id_num);

    fp = fopen("file.txt", "rb");

    if (fp == NULL) {
        printf("File Not Opening\n");
        exit(1);
    }

    temp_fp = fopen("temp.txt", "wb");

    if (temp_fp == NULL) {
        printf("Error! Temporary File Not Possible To Creating\n");
        fclose(fp);
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (std.id_no == id_num) {
            printf("Enter New Details For Update Student:\n");

            printf("Enter New CGPA: ");
            scanf("%f", &std.cgpa);

            printf("Enter New Mobile Number: ");
            scanf("%d", &std.mobile_no);

            found = 1;
        }
        fwrite(&std, sizeof(std), 1, temp_fp);
    }
    fclose(fp);
    if (!found) {
        printf("ID %d not found.\n", id_num);
        remove("temp.txt");
    } else {
        fclose(temp_fp);

        remove("file.txt");
        rename("temp.txt", "file.txt");
        printf("Record Updated Successfully.\n");
    }

    

    

    mainmenu();
}

void viewstudent() 
{
    FILE *fp;
    struct students std;
    int found = 0;
    char searchdep[10];
    int studentCount = 1;

    printf("\n***** VIEW STUDENT RECORD *****\n");

    printf("Enter Department (CSE/EEE/BBA/MSJ) To View Details Of Students: \n");
    scanf("%s", searchdep);

    if (strcmp(searchdep, "CSE") != 0 && strcmp(searchdep, "EEE") != 0 &&
        strcmp(searchdep, "BBA") != 0 && strcmp(searchdep, "MSJ") != 0) {
        printf("Invalid department code. Please try again.\n");
        mainmenu();
        return;
    }

    fp = fopen("file.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (strcmp(std.department, searchdep) == 0) {
            printf("%d.\n", studentCount);
            printf("Student Name: %s\n", std.student_name);
            printf("Student ID No: %d\n", std.id_no);
            printf("Student Mobile Number: %d\n", std.mobile_no);
            printf("Student Department: %s\n", std.department);
            printf("Student Gender: %s\n", std.gender);
            printf("Student Age: %d\n", std.age);
            printf("Student CGPA: %.2f\n", std.cgpa);
            found = 1;
            studentCount++;
        }
    }

    if (!found) {
        printf("No student record found for the entered department.\n");
    }

    fclose(fp);

    

    mainmenu();
}
