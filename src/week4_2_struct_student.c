/*
 * week4_2_struct_student.c
 * Author: Farid Hajiyev
 * Student ID: 251ADB190
 * Description:
 *   Demonstrates defining and using a struct in C.
 *   Define a 'Student' struct with name, id and grade, create two
 *   instances with the values from the instructions, and print them.
 *
 *   This program reads no input. Output must match the format in the
 *   Week 4 instructions exactly (it is checked by the autograder).
 */

#include <stdio.h>
#include <string.h>

// TODO: Define struct Student with fields: name (char[50]), id (int), grade (float)
// Example:
// struct Student {
//     char name[50];
//     int id;
//     float grade;
// };
typedef struct Student {
    char name[50];
    int id;
    float grade;
} Student;

int main(void) {
    // TODO: Declare two Student variables
    Student first;
    Student second;
    Student *list[2] = { &first, &second };

    // TODO: Assign the values (use strcpy for the name):
    //       Student 1: Alice Johnson, 1001, 9.1
    //       Student 2: Bob Smith,     1002, 8.7
    strcpy(first.name, "Alice Johnson");
    first.id = 1001;
    first.grade = 9.1f;

    strcpy(second.name, "Bob Smith");
    second.id = 1002;
    second.grade = 8.7f;

    // TODO: Print each student exactly as:
    //       Student <k>: <name>, ID: <id>, Grade: <grade with 1 decimal, %.1f>
    for (int k = 0; k < 2; k++) {
        printf("Student %d: %s, ID: %d, Grade: %.1f\n",
               k + 1, list[k]->name, list[k]->id, list[k]->grade);
    }

    return 0;
}