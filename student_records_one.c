//this file contains error handing code

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PASS_MARKS 40
#define MAX_NAME_LEN 50
#define FILENAME "students.txt"

typedef struct
{
    char name[MAX_NAME_LEN];
    int roll;
    float marks;
} Student;

Student *records = NULL;
int count = 0;
int capacity = 5;

void flushInput()
{
    while (getchar() != '\n')
        ;
}

void greetUser()
{
    char username[MAX_NAME_LEN];
    printf("Welcome to the Student Record System!\n");
    printf("Please enter your name: ");
    scanf("%s", username);
    flushInput(); // Clear buffer
    printf("Hello, %s! Let's get started.\n\n", username);
}

void checkStatus(float marks)
{
    if (marks >= PASS_MARKS)
        printf("Status: Passed\n");
    else
        printf("Status: Failed\n");
}

void expandMemory()
{
    capacity *= 2;
    records = realloc(records, capacity * sizeof(Student));
    if (!records)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }
}

int isValidRoll(char *input)
{
    if (strlen(input) != 8)
        return 0;
    for (int i = 0; i < 8; i++)
    {
        if (!isdigit(input[i]))
            return 0;
    }
    return 1;
}

int isValidName(char *input)
{
    for (int i = 0; input[i] != '\0'; i++)
    {
        if (!isalpha(input[i]))
            return 0;
    }
    return 1;
}

void inputValidName(char *buffer)
{
    while (1)
    {
        printf("Enter student name: ");
        scanf("%s", buffer);
        flushInput();
        if (isValidName(buffer))
            break;
        else
            printf("Name must contain only letters. Please re-enter.\n");
    }
}

int inputValidRoll()
{
    char buffer[20];
    while (1)
    {
        printf("Enter 8-digit roll number: ");
        scanf("%s", buffer);
        flushInput();
        if (isValidRoll(buffer))
            return atoi(buffer);
        else
            printf("Invalid roll number. Must be exactly 8 digits and numeric.\n");
    }
}

float inputValidMarks()
{
    float marks;
    while (1)
    {
        printf("Enter marks: ");
        if (scanf("%f", &marks) != 1)
        {
            flushInput();
            printf("Invalid input. Enter a valid number.\n");
            continue;
        }
        flushInput();
        if (marks >= 0)
            return marks;
        else
            printf("A student cannot score less than 0. Re-enter the score.\n");
    }
}

void addStudent()
{
    if (count == capacity)
        expandMemory();
    
    inputValidName(records[count].name);
    records[count].roll = inputValidRoll();
    records[count].marks = inputValidMarks();

    flushInput();
    checkStatus(records[count].marks);
    count++;
}

void displayAll()
{
    printf("\nStudent Records:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d) Name: %s, Roll: %d, Marks: %.2f\n", i + 1, records[i].name, records[i].roll, records[i].marks);
        checkStatus(records[i].marks);
    }
    printf("\n");
}

void modifyStudent()
{
    int roll;
    printf("Enter roll number to modify: ");
    scanf("%d", &roll);
    flushInput();

    for (int i = 0; i < count; i++)
    {
        if (records[i].roll == roll)
        {
            inputValidName(records[i].name);
            records[i].marks = inputValidMarks();
            printf("Record updated!\n");
            return;
        }
    }
    printf("Student not found.\n");
}

void searchStudent()
{
    int roll;
    printf("Enter roll number to search: ");
    scanf("%d", &roll);
    flushInput();

    for (int i = 0; i < count; i++)
    {
        if (records[i].roll == roll)
        {
            printf("Found: Name: %s, Roll: %d, Marks: %.2f\n", records[i].name, records[i].roll, records[i].marks);
            checkStatus(records[i].marks);
            return;
        }
    }
    printf("Student not found.\n");
}

void deleteStudent()
{
    int roll;
    printf("Enter roll number to delete: ");
    scanf("%d", &roll);
    flushInput();

    int found = 0;
    for (int i = 0; i < count; i++)
    {
        if (records[i].roll == roll)
        {
            found = 1;
            for (int j = i; j < count - 1; j++)
            {
                records[j] = records[j + 1];
            }
            count--;
            printf("Student with roll number %d deleted.\n", roll);
            break;
        }
    }
    if (!found)
    {
        printf("Student with roll number %d not found.\n", roll);
    }
}

void saveToFile()
{
    FILE *fp = fopen(FILENAME, "w");
    if (!fp)
    {
        printf("Error saving file.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %d %.2f\n", records[i].name, records[i].roll, records[i].marks);
    }
    fclose(fp);
    printf("Records saved to %s\n", FILENAME);
}

void loadFromFile()
{
    FILE *fp = fopen(FILENAME, "r");
    if (!fp)
    {
        printf("No previous records found.\n");
        return;
    }
    while (!feof(fp))
    {
        if (count == capacity)
            expandMemory();
        if (fscanf(fp, "%s %d %f", records[count].name, &records[count].roll, &records[count].marks) == 3)
        {
            count++;
        }
    }
    fclose(fp);
    printf("Records loaded from %s\n", FILENAME);
}

void calculateAverage()
{
    if (count == 0)
    {
        printf("No student records available.\n");
        return;
    }

    float total = 0;
    for (int i = 0; i < count; i++)
    {
        total += records[i].marks;
    }
    printf("Average marks: %.2f\n", total / count);
}

void sortRecords()
{
    int choice;
    printf("Sort by marks:\n1) Ascending\n2) Descending\nChoose: ");
    scanf("%d", &choice);
    flushInput();

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            int shouldSwap = (choice == 1 && records[i].marks > records[j].marks) ||
                             (choice == 2 && records[i].marks < records[j].marks);
            if (shouldSwap)
            {
                Student temp = records[i];
                records[i] = records[j];
                records[j] = temp;
            }
        }
    }
    printf("Records sorted!\n");
}

int main()
{
    records = malloc(sizeof(Student) * capacity);
    greetUser();
    loadFromFile();

    int option;
    do
    {
        printf("\nMenu:\n");
        printf("1) Add Student\n2) Display All\n3) Modify Student\n4) Delete Student\n");
        printf("5) Search Student\n6) Save to File\n7) Calculate Average\n8) Sort Records\n9) Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        flushInput();

        switch (option)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            modifyStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            searchStudent();
            break;
        case 6:
            saveToFile();
            break;
        case 7:
            calculateAverage();
            break;
        case 8:
            sortRecords();
            break;
        case 9:
            printf("Exiting... Goodbye!\n");
            break;
        default:
            printf("Invalid option.\n");
        }
    } while (option != 9);

    free(records);
    return 0;
}
