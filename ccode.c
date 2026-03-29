#include <stdio.h>

/* Function to calculate grade */
char calculateGrade(float marks) {
    if (marks >= 80.0) {
        return 'A';
    } else if (marks >= 70.0) {
        return 'B';
    } else if (marks >= 60.0) {
        return 'C';
    } else if (marks >= 50.0) {
        return 'D';
    } else {
        return 'F';
    }
}

/* Function to print final result status */
void checkResult(float avg, int attendance) {
    if (avg >= 80.0 && attendance >= 90) {
        printf("Excellent result with very good attendance.\n");
    } else if (avg >= 70.0 && attendance >= 75) {
        printf("Good result and acceptable attendance.\n");
    } else if (avg >= 50.0 && attendance >= 60) {
        printf("Passed, but needs improvement.\n");
    } else if (avg >= 50.0 && attendance < 60) {
        printf("Passed in marks, but attendance is too low.\n");
    } else {
        printf("Failed.\n");
    }
}

int main() {
    /* Constants */
    const int TOTAL_SUBJECTS = 5;
    const float BONUS_MARKS = 2.5;

    /* Initialization */
    int i;
    int attendance = 78;
    int totalMarks = 0;
    float average;
    float marks[TOTAL_SUBJECTS];

    printf("Enter marks for %d subjects:\n", TOTAL_SUBJECTS);

    /* Loop + input + variable update */
    for (i = 0; i < TOTAL_SUBJECTS; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%f", &marks[i]);

        /* Update variable */
        marks[i] = marks[i] + BONUS_MARKS;

        /* Complex if-else-if-else */
        if (marks[i] > 100.0) {
            marks[i] = 100.0;
            printf("Bonus added, but capped at 100.\n");
        } else if (marks[i] >= 80.0) {
            printf("Excellent marks after bonus.\n");
        } else if (marks[i] >= 50.0) {
            printf("Pass marks after bonus.\n");
        } else {
            printf("Still low marks after bonus.\n");
        }

        /* Type casting: float to int */
        totalMarks = totalMarks + (int)marks[i];
    }

    /* Type casting: int to float */
    average = (float)totalMarks / TOTAL_SUBJECTS;

    printf("\n--- Subject Grades ---\n");
    for (i = 0; i < TOTAL_SUBJECTS; i++) {
        printf("Subject %d = %.2f, Grade = %c\n", i + 1, marks[i], calculateGrade(marks[i]));
    }

    printf("\nTotal Marks = %d\n", totalMarks);
    printf("Average Marks = %.2f\n", average);
    printf("Attendance = %d%%\n", attendance);

    /* Function call */
    checkResult(average, attendance);

    return 0;
}