#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASS_MARKS 40
#define MAX_NAME_LEN 50
#define FILENAME "students.txt"

//  Function Prototypes
void flushInput();
void greetUser();
void checkStatus(float marks);
void expandMemory();
void addStudent();
void displayAll();
void modifyStudent();
void searchStudent();
void deleteStudent();
void saveToFile();
void loadFromFile();
void calculateAverage();
void sortRecords();

//  Data Structure
typedef struct
{
    char name[MAX_NAME_LEN];
    int roll;
    float marks;
} Student;

//  Global Variables
Student *records = NULL;
int count = 0;
int capacity = 5;

//  Flush input buffer
void flushInput()
{
    while (getchar() != '\n')
        ;
}

//  Greet user
void greetUser()
{
    char username[MAX_NAME_LEN];
    int valid = 0;

    printf("Welcome to the Student Record System!\n");

    while (!valid)
    {
        printf("Please enter your name: ");
        if (scanf("%s", username) != 1)
        {
            printf("Invalid input.\n");
            flushInput();
            continue;
        }

        // Check if name contains only letters
        valid = 1;
        for (int i = 0; username[i] != '\0'; i++)
        {
            if (!(username[i] >= 'A' && username[i] <= 'Z') &&
                !(username[i] >= 'a' && username[i] <= 'z'))
            {
                valid = 0;
                break;
            }
        }

        if (!valid)
        {
            printf("Error: Name should contain only letters. Please try again.\n");
            flushInput();
        }
    }

    flushInput();
    printf("Hello, %s! Let's get started.\n\n", username);
}

//  Check pass/fail
void checkStatus(float marks)
{
    if (marks >= PASS_MARKS)
        printf("Status: Passed\n");
    else
        printf("Status: Failed\n");
}

//  Expand memory dynamically
void expandMemory()
{
    capacity *= 2;
    Student *temp = realloc(records, capacity * sizeof(Student));
    if (!temp)
    {
        printf("Memory allocation failed.\n");
        free(records);
        exit(1);
    }
    records = temp;
}

//  Add student
void addStudent()
{
    if (count == capacity)
        expandMemory();

    // Input and validate name
    printf("Enter student name: ");
    if (scanf("%s", records[count].name) != 1)
    {
        printf("Invalid name input.\n");
        return;
    }

    // Check if name contains digits
    for (int i = 0; records[count].name[i] != '\0'; i++)
    {
        if (records[count].name[i] >= '0' && records[count].name[i] <= '9')
        {
            printf("Error: Name should not contain numbers.\n");
            return;
        }
    }

    // Input and validate roll number
    printf("Enter roll number: ");
    if (scanf("%d", &records[count].roll) != 1)
    {
        printf("Invalid roll number.\n");
        return;
    }

    // Check for duplicate roll number
    for (int i = 0; i < count; i++)
    {
        if (records[i].roll == records[count].roll)
        {
            printf("Error: Roll number already exists. Please enter a unique roll number.\n");
            return;
        }
    }

    // Input and validate marks
    printf("Enter marks: ");
    if (scanf("%f", &records[count].marks) != 1)
    {
        printf("Invalid marks input.\n");
        return;
    }

    flushInput();
    checkStatus(records[count].marks);
    count++;
}

//  Display all records
void displayAll()
{
    if (count == 0)
    {
        printf("No records to display.\n");
        return;
    }

    printf("\nStudent Records:\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d) Name: %s, Roll: %d, Marks: %.2f\n", i + 1, records[i].name, records[i].roll, records[i].marks);
        checkStatus(records[i].marks);
    }
    printf("\n");
}

//  Modify student
void modifyStudent()
{
    int roll;
    printf("Enter roll number to modify: ");
    if (scanf("%d", &roll) != 1)
    {
        printf("Invalid roll number.\n");
        return;
    }
    flushInput();

    for (int i = 0; i < count; i++)
    {
        if (records[i].roll == roll)
        {
            printf("Enter new name: ");
            if (scanf("%s", records[i].name) != 1)
            {
                printf("Invalid name input.\n");
                return;
            }
            printf("Enter new marks: ");
            if (scanf("%f", &records[i].marks) != 1)
            {
                printf("Invalid marks input.\n");
                return;
            }
            flushInput();
            printf("Record updated!\n");
            return;
        }
    }
    printf("Student not found.\n");
}

//  Search student
void searchStudent()
{
    int roll;
    printf("Enter roll number to search: ");
    if (scanf("%d", &roll) != 1)
    {
        printf("Invalid roll number.\n");
        return;
    }
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

//  Delete student
void deleteStudent()
{
    int roll;
    printf("Enter roll number to delete: ");
    if (scanf("%d", &roll) != 1)
    {
        printf("Invalid roll number.\n");
        return;
    }
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

//  Save to file
void saveToFile()
{
    FILE *fp = fopen(FILENAME, "w");
    if (!fp)
    {
        perror("Error opening file for writing");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%s %d %.2f\n", records[i].name, records[i].roll, records[i].marks);
    }
    fclose(fp);
    printf("Records saved to %s\n", FILENAME);
}

//  Load from file
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

//  Calculate average
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

//  Sort records
void sortRecords()
{
    int choice;
    printf("Sort by marks:\n1) Ascending\n2) Descending\nChoose: ");
    if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2))
    {
        printf("Invalid choice.\n");
        flushInput();
        return;
    }
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

//  Main function
int main()
{
    records = malloc(sizeof(Student) * capacity);
    if (!records)
    {
        printf("Initial memory allocation failed.\n");
        return 1;
    }

    greetUser();
    loadFromFile();

    int option;
    do
    {
        printf("\nMenu:\n");
        printf("1) Add Student\n2) Display All\n3) Modify Student\n4) Delete Student\n");
        printf("5) Search Student\n6) Save to File\n7) Calculate Average\n8) Sort Records\n9) Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &option) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            flushInput();
            continue;
        }
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