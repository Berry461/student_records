Student Record System in C
This is a console-based C program that allows users to manage student records including adding, modifying, deleting, searching, saving, and sorting data. It demonstrates dynamic memory allocation, file handling, and structured programming techniques.

Features
-  User greeting with name input
-  Student record entry (Name, Roll Number, Marks)
-  Pass/fail evaluation based on marks
-  Display all records
-  Modify student records
-  Search by roll number
-  Delete records by roll number
-  Save/load records from a file
-  Calculate average marks
-  Sort records by marks (ascending or descending)

Code Breakdown
1. Header Files and Definitions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASS_MARKS 40
#define MAX_NAME_LEN 50
#define FILENAME "students.txt"


Imports standard I/O, memory, and string handling. Also defines constants like passing threshold and max name length.

2. Student Data Structure
typedef struct {
    char name[MAX_NAME_LEN];
    int roll;
    float marks;
} Student;


Creates a structure to store student details.

3. Global Variables
Student *records = NULL;
int count = 0;
int capacity = 5;


Manages student records dynamically using a pointer array.

4. Input Buffer Flush
void flushInput() {
    while (getchar() != '\n');
}


Ensures smooth input handling by clearing unwanted characters from the buffer.

5. Welcome and Greeting
void greetUser() {
    char username[MAX_NAME_LEN];
    // ...
}


Prompts the user for their name and displays a welcome message.

6. Check Pass/Fail Status
void checkStatus(float marks) {
    // ...
}


Evaluates if a student passed based on the predefined threshold.

7. Memory Management
void expandMemory() {
    // ...
}


Dynamically doubles the storage array when capacity is reached.

8. Add Student
void addStudent() {
    // ...
}


Adds a new student record, allocates memory if needed, and displays pass/fail status.

9. Display All Records
void displayAll() {
    // ...
}


Shows every student record in a readable format.

10. Modify Student Record
void modifyStudent() {
    // ...
}


Locates a student by roll number and updates their info.

11. Search Student Record
void searchStudent() {
    // ...
}


Searches for a student by roll number and displays their info.

12. Delete Student Record
void deleteStudent() {
    // ...
}


Deletes a student by shifting elements in the array. Decreases count and frees the space logically.

13. Save Records to File
void saveToFile() {
    // ...
}


Writes all student data to students.txt using file I/O.

14. Load Records from File
void loadFromFile() {
    // ...
}


Loads existing student records from students.txt into memory when the program starts.

15. Calculate Average Marks
void calculateAverage() {
    // ...
}


Computes the average of all stored student marks.

16. Sort Records by Marks
void sortRecords() {
    // ...
}


Allows sorting marks in ascending or descending order via basic bubble sort.

17. Main Function & Menu Logic
int main() {
    // ...
}


Initializes memory, greets user, loads saved records, and presents a looped menu with 9 options.
Menu Options:
- Add Student
- Display All
- Modify Student
- Delete Student
- Search Student
- Save to File
- Calculate Average
- Sort Records
- Exit Program

Getting Started
Compile the Program
gcc student_record_system.c -o student_records


Run the Program
./student_records



File Output
All records are saved in a file named:
students.txt


This file is updated every time you choose Save to File.

Algorithm: Student Record System
Step-by-Step Procedure
1. Start
2. Display welcome message and prompt user for name
3. Load existing student records from file (if available)
4. Loop until user selects Exit:
    a. Display menu:
        1) Add Student
        2) Display All
        3) Modify Student
        4) Search Student
        5) Save to File
        6) Calculate Average
        7) Sort Records
        8) Delete Student
        9) Exit
    b. Accept user input for option
    c. Execute corresponding function:
        - If Add Student:
            - Input name, roll, marks
            - Check if student passed/failed
            - Store in dynamic array
        - If Display All:
            - Loop through array and show all student info
        - If Modify:
            - Search by roll
            - Update name and marks
        - If Search:
            - Locate and show student by roll
        - If Save:
            - Write all records to file
        - If Calculate Average:
            - Sum marks and divide by count
        - If Sort:
            - Choose ascending or descending
            - Sort array accordingly
        - If Delete:
            - Search by roll and remove entry
        - If Exit:
            - Break loop
5. Free allocated memory
6. End



Flowchart: Visual Flow
Here’s the logical flow described as a simple chart format. Since I can’t generate visuals in this message, I’ll lay it out as ASCII-style structure:
+----------------------------------+
|           Start                 |
+----------------------------------+
             ↓
+----------------------------------+
|  Greet user & get name          |
+----------------------------------+
             ↓
+----------------------------------+
|  Load records from file         |
+----------------------------------+
             ↓
+----------------------------------+
|         Show Menu               |
| 1-Add  2-Display  ...  9-Exit   |
+----------------------------------+
             ↓
+-------------------------------+
| User selects option (1–9)    |
+-------------------------------+
        ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓
       ┌──┴─┐ ┌──┴─┐ ┌──┴─┐
       ▼    ▼     ▼     ▼
   Add  Display Modify  Search
Student Records  Records Records
   ▼      ▼       ▼        ▼
Check  Show     Update   Locate
Pass   Records   Info     Info
Fail              ↓
         ┌────────────┐
         ▼            ▼
     Save to      Delete
       File       Student
        ↓            ↓
   Write to    Search & Remove
     File         Entry
        ↓            ↓
     Calculate      Sort
     Average        Records
        ↓            ↓
  Show Average    Sort Marks
        ↓            ↓
        └──────┬─────┘
               ↓
+------------------------------+
|      Loop until Exit        |
+------------------------------+
               ↓
+------------------------------+
|     Free memory & Exit      |
+------------------------------+





