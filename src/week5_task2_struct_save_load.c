// week5_task2_struct_save_load.c
// Name: Farid  Surname: Hajiyev  Student ID: 231ADB132
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
// TODO: Complete the function implementations and the file handling logic.
//
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int save_student(const Student *s, const char *filename);  // 0 on success, -1 on error
int load_student(const char *filename, Student *out);      // 0 on success, -1 on error

int main(void) {
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *filename = "student.txt";

    printf("Saving student to file...\n");
    // TODO: Call save_student(&s1, filename). If it fails, print an error and return EXIT_FAILURE.
    if (save_student(&s1, filename) == -1) {
        fprintf(stderr, "Error: cannot save the student record to %s\n", filename);
        return EXIT_FAILURE;
    }

    printf("Loading student from file...\n");
    // TODO: Call load_student(filename, &loaded). If it fails, print an error and return EXIT_FAILURE.
    if (load_student(filename, &loaded) == -1) {
        fprintf(stderr, "Error: cannot load the student record from %s\n", filename);
        return EXIT_FAILURE;
    }

    // TODO: Print the loaded data in exactly this format:
    //       printf("Loaded student: %s, %d, GPA %.2f\n", ...);
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    return EXIT_SUCCESS;
}

// TODO: Implement save_student()
// Open the file for writing ("w"), return -1 if fopen() fails,
// write "name age gpa" on one line with fprintf(), close the file and return 0.
int save_student(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    // fprintf returns a negative number if writing failed
    int written = fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);

    // fclose() returns 0 on success; it also flushes the buffered data to disk
    int closed = fclose(fp);

    // Success only if the write worked and the file was closed cleanly
    return (written > 0 && closed == 0) ? 0 : -1;
}

// TODO: Implement load_student()
// Open the file for reading ("r"), return -1 if fopen() fails,
// read the three fields with fscanf(fp, "%49s %d %f", ...) and check that it returned 3,
// close the file in every case, and return 0 on success / -1 on failure.
int load_student(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    // Separate local variables: *out is only changed when all three fields were read
    char name[MAX_NAME_LEN];
    int age = 0;
    float gpa = 0.0f;

    // %49s leaves one byte for the '\0', so a long name cannot overflow name[50]
    int fields_read = fscanf(fp, "%49s %d %f", name, &age, &gpa);

    // The file is closed in every case, success or not
    fclose(fp);

    if (fields_read != 3) {
        return -1;
    }

    strcpy(out->name, name);   // safe: name holds at most 49 characters plus '\0'
    out->age = age;
    out->gpa = gpa;
    return 0;
}