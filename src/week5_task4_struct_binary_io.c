// week5_task4_struct_binary_io.c   (BONUS)
// Name: Farid  Surname: Hajiyev  Student ID: 251ADB132
//
// Task 4: Save and load a struct in binary format with fwrite()/fread()
// Week 5 – Files & Modular Programming
//
// Build: make lab5   Run: ./bin/week5_task4_struct_binary_io

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
int  save_student_binary(const Student *s, const char *filename);  // 0 on success, -1 on error
int  load_student_binary(const char *filename, Student *out);      // 0 on success, -1 on error
long file_size(const char *filename);                              // bytes, -1 on error

// Helper: writes the record as one text line "name age gpa". Returns 0 on success, -1 on error
static int save_text(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }
    int written = fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);
    int closed = fclose(fp);
    return (written > 0 && closed == 0) ? 0 : -1;
}

int main(void) {
    Student s1 = {0};          // zero-initialised so unused name bytes are not garbage on disk
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *bin_file = "student.bin";
    const char *txt_file = "student.txt";

    printf("Saving student in binary format...\n");
    // TODO: save_student_binary(&s1, bin_file); handle failure
    if (save_student_binary(&s1, bin_file) == -1) {
        fprintf(stderr, "Error: cannot write the binary file %s\n", bin_file);
        return EXIT_FAILURE;
    }

    // TODO: Save the same record as text ("name age gpa") to txt_file for comparison
    if (save_text(&s1, txt_file) == -1) {
        fprintf(stderr, "Error: cannot write the text file %s\n", txt_file);
        return EXIT_FAILURE;
    }

    printf("Loading student from binary file...\n");
    // TODO: load_student_binary(bin_file, &loaded); handle failure
    if (load_student_binary(bin_file, &loaded) == -1) {
        fprintf(stderr, "Error: cannot read the binary file %s\n", bin_file);
        return EXIT_FAILURE;
    }

    // TODO: printf("Loaded student: %s, %d, GPA %.2f\n", ...);
    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);
    // TODO: printf("Text file size: %ld bytes\n", file_size(txt_file));
    printf("Text file size: %ld bytes\n", file_size(txt_file));
    // TODO: printf("Binary file size: %ld bytes\n", file_size(bin_file));
    printf("Binary file size: %ld bytes\n", file_size(bin_file));

    return EXIT_SUCCESS;
}

// TODO: open with "wb", fwrite(s, sizeof(Student), 1, fp) must return 1, close, return 0/-1
int save_student_binary(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }

    // fwrite returns the number of items written; we wrote one struct, so we expect 1
    size_t count = fwrite(s, sizeof(Student), 1, fp);

    // fclose() flushes the buffer, so a failure here also means data was lost
    int closed = fclose(fp);

    return (count == 1 && closed == 0) ? 0 : -1;
}

// TODO: open with "rb", fread(out, sizeof(Student), 1, fp) must return 1, close, return 0/-1
int load_student_binary(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // fread returns the number of items read; we expect exactly 1 struct
    size_t count = fread(out, sizeof(Student), 1, fp);

    // The file is closed in every case
    fclose(fp);

    if (count != 1) {
        memset(out, 0, sizeof(Student));   // do not leave half-read data in the caller's struct
        return -1;
    }
    return 0;
}

// TODO: open with "rb", fseek(fp, 0, SEEK_END), size = ftell(fp), close, return size (-1 on error)
long file_size(const char *filename) {
    if (filename == NULL) {
        return -1;
    }

    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    // Move to the end of the file; if that fails there is no size to report
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }

    // The position at the end of the file equals its size in bytes (-1 if ftell fails)
    long size = ftell(fp);
    fclose(fp);
    return size;
}