#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NUM_SEMESTERS 8
#define NAME_LEN 50
#define PHONE_LEN 16
#define EMAIL_LEN 60
#define NA_SGPA -1.0f   /* marks an SGPA that is not available yet */

typedef struct {
    long long sap_id;
    int roll_no;
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
    int year;                      /* 1..4 */
    int semester;                  /* current semester, 1..8 */
    float sgpa[NUM_SEMESTERS];     /* NA_SGPA where not available */
} Student;

static Student students[MAX_STUDENTS];
static int student_count = 0;

/* ---------- input helpers ---------- */

static void read_line(const char *prompt, char *buf, size_t size) {
    for (;;) {
        printf("%s", prompt);
        if (!fgets(buf, (int)size, stdin)) {      /* EOF: exit cleanly */
            printf("\nInput closed. Exiting.\n");
            exit(0);
        }
        buf[strcspn(buf, "\r\n")] = '\0';
        if (buf[0] != '\0') return;
        printf("  Input cannot be empty.\n");
    }
}

static long long read_long(const char *prompt, long long min, long long max) {
    char buf[64], *end;
    for (;;) {
        read_line(prompt, buf, sizeof buf);
        long long v = strtoll(buf, &end, 10);
        if (*end == '\0' && v >= min && v <= max) return v;
        printf("  Enter a whole number between %lld and %lld.\n", min, max);
    }
}

static float read_sgpa(const char *prompt) {
    char buf[64], *end;
    for (;;) {
        read_line(prompt, buf, sizeof buf);
        float v = strtof(buf, &end);
        if (*end == '\0' && v >= 0.0f && v <= 10.0f) return v;
        printf("  Enter an SGPA between 0 and 10.\n");
    }
}

/* ---------- helpers ---------- */

static int find_by_sap(long long sap_id) {
    for (int i = 0; i < student_count; i++)
        if (students[i].sap_id == sap_id) return i;
    return -1;
}

static void print_student(const Student *s) {
    printf("SAP ID : %lld\n", s->sap_id);
    printf("Roll No: %d\n", s->roll_no);
    printf("Name   : %s\n", s->name);
    printf("Phone  : %s\n", s->phone);
    printf("Email  : %s\n", s->email);
    printf("Year   : %d    Semester: %d\n", s->year, s->semester);
    printf("SGPA   :");
    for (int i = 0; i < NUM_SEMESTERS; i++) {
        if (s->sgpa[i] < 0) printf("  S%d=--", i + 1);
        else                printf("  S%d=%.2f", i + 1, s->sgpa[i]);
    }
    printf("\n");
}

static void print_table_header(void) {
    printf("%-11s %-6s %-20s %-12s %-4s %-4s\n",
           "SAP ID", "Roll", "Name", "Phone", "Year", "Sem");
    printf("-------------------------------------------------------------\n");
}

static void print_table_row(const Student *s) {
    printf("%-11lld %-6d %-20.20s %-12s %-4d %-4d\n",
           s->sap_id, s->roll_no, s->name, s->phone, s->year, s->semester);
}

/* ---------- pre-loaded data ---------- */

static void add_preloaded(long long sap, int roll, const char *name, const char *phone,
                          const char *email, int year, int sem, const float *sgpa) {
    Student *s = &students[student_count++];
    s->sap_id = sap;
    s->roll_no = roll;
    snprintf(s->name, NAME_LEN, "%s", name);
    snprintf(s->phone, PHONE_LEN, "%s", phone);
    snprintf(s->email, EMAIL_LEN, "%s", email);
    s->year = year;
    s->semester = sem;
    for (int i = 0; i < NUM_SEMESTERS; i++)
        s->sgpa[i] = (i < sem) ? sgpa[i] : NA_SGPA;
}

static void preload_students(void) {
    float a[] = {8.2f, 8.5f, 8.9f, 9.0f, 8.7f, 9.1f, 9.3f, 9.2f};
    float b[] = {7.5f, 7.9f, 8.1f, 8.0f, 8.4f, 8.6f, 0, 0};
    float c[] = {9.1f, 9.3f, 9.0f, 9.4f, 0, 0, 0, 0};
    float d[] = {6.8f, 7.2f, 0, 0, 0, 0, 0, 0};
    float e[] = {8.0f, 0, 0, 0, 0, 0, 0, 0};

    add_preloaded(500101001LL, 1, "Aarav Sharma",  "9876500001", "aarav.sharma@example.com", 4, 8, a);
    add_preloaded(500102002LL, 12, "Priya Singh",  "9876500002", "priya.singh@example.com",  3, 6, b);
    add_preloaded(500103003LL, 23, "Rohan Verma",  "9876500003", "rohan.verma@example.com",  2, 4, c);
    add_preloaded(500104004LL, 34, "Ananya Gupta", "9876500004", "ananya.gupta@example.com", 1, 2, d);
    add_preloaded(500105005LL, 45, "Kabir Mehta",  "9876500005", "kabir.mehta@example.com",  1, 1, e);
}

/* ---------- implemented features ---------- */

static void add_student(void) {
    if (student_count >= MAX_STUDENTS) {
        printf("Record list is full (%d students).\n", MAX_STUDENTS);
        return;
    }

    Student s;
    memset(&s, 0, sizeof s);

    s.sap_id = read_long("SAP ID (9 digits): ", 100000000LL, 999999999LL);
    if (find_by_sap(s.sap_id) != -1) {
        printf("A student with SAP ID %lld already exists.\n", s.sap_id);
        return;
    }
    s.roll_no = (int)read_long("Roll No.: ", 1, 99999);
    read_line("Name: ", s.name, sizeof s.name);
    read_line("Phone No.: ", s.phone, sizeof s.phone);
    read_line("Email ID: ", s.email, sizeof s.email);
    s.year = (int)read_long("Year (1-4): ", 1, 4);

    char prompt[64];
    snprintf(prompt, sizeof prompt, "Current semester (%d-%d): ", 2 * s.year - 1, 2 * s.year);
    s.semester = (int)read_long(prompt, 2 * s.year - 1, 2 * s.year);

    for (int i = 0; i < NUM_SEMESTERS; i++) {
        if (i < s.semester) {
            snprintf(prompt, sizeof prompt, "SGPA for semester %d (0-10): ", i + 1);
            s.sgpa[i] = read_sgpa(prompt);
        } else {
            s.sgpa[i] = NA_SGPA;
        }
    }

    students[student_count++] = s;
    printf("Student added successfully.\n");
}

static void display_all(void) {
    if (student_count == 0) {
        printf("No student records available.\n");
        return;
    }
    printf("\nAll students (%d):\n", student_count);
    print_table_header();
    for (int i = 0; i < student_count; i++)
        print_table_row(&students[i]);
}

static void search_student(void) {
    long long sap = read_long("Enter SAP ID to search: ", 0, 999999999999LL);
    int idx = find_by_sap(sap);
    if (idx == -1) {
        printf("No student found with SAP ID %lld.\n", sap);
        return;
    }
    printf("\nRecord found:\n");
    print_student(&students[idx]);
}

static void delete_student(void) {
    long long sap = read_long("Enter SAP ID to delete: ", 0, 999999999999LL);
    int idx = find_by_sap(sap);
    if (idx == -1) {
        printf("No student found with SAP ID %lld.\n", sap);
        return;
    }
    for (int i = idx; i < student_count - 1; i++)   /* shift left */
        students[i] = students[i + 1];
    student_count--;
    printf("Record deleted.\n");
}

/* ---------- CGPA ---------- */

/* CGPA = average of the available SGPAs (entries that are not NA_SGPA). */
static float compute_cgpa(const Student *s, int *count_out) {
    float sum = 0.0f;
    int n = 0;
    for (int i = 0; i < NUM_SEMESTERS; i++) {
        if (s->sgpa[i] >= 0) {
            sum += s->sgpa[i];
            n++;
        }
    }
    if (count_out) *count_out = n;
    return (n > 0) ? sum / n : 0.0f;
}

static void calculate_cgpa(void) {
    if (student_count == 0) {
        printf("No student records available.\n");
        return;
    }
    printf("\nCGPA of each student:\n");
    printf("%-11s %-20s %-4s %-9s %-6s\n", "SAP ID", "Name", "Year", "Sem count", "CGPA");
    printf("-------------------------------------------------------\n");
    for (int i = 0; i < student_count; i++) {
        int n;
        float cgpa = compute_cgpa(&students[i], &n);
        printf("%-11lld %-20.20s %-4d %-9d %-6.2f\n",
               students[i].sap_id, students[i].name, students[i].year, n, cgpa);
    }
}

static void average_cgpa_by_year(void) {
    if (student_count == 0) {
        printf("No student records available.\n");
        return;
    }
    printf("\nAverage CGPA by year:\n");
    printf("%-6s %-9s %-12s\n", "Year", "Students", "Average CGPA");
    printf("------------------------------\n");
    for (int year = 1; year <= 4; year++) {
        float total = 0.0f;
        int n = 0;
        for (int i = 0; i < student_count; i++) {
            if (students[i].year == year) {
                total += compute_cgpa(&students[i], NULL);
                n++;
            }
        }
        if (n == 0) printf("%-6d %-9d %-12s\n", year, 0, "--");
        else        printf("%-6d %-9d %-12.2f\n", year, n, total / n);
    }
}

/* ---------- sorted displays (bubble sort on a copy) ---------- */

static void print_sorted(const Student *list, int n, const char *title) {
    printf("\n%s (%d students):\n", title, n);
    print_table_header();
    for (int i = 0; i < n; i++)
        print_table_row(&list[i]);
}

static void display_sorted_by_sap(void) {
    if (student_count == 0) {
        printf("No student records available.\n");
        return;
    }
    Student copy[MAX_STUDENTS];                       /* original stays intact */
    for (int i = 0; i < student_count; i++) copy[i] = students[i];

    for (int pass = 0; pass < student_count - 1; pass++) {
        int swapped = 0;
        for (int j = 0; j < student_count - 1 - pass; j++) {
            if (copy[j].sap_id > copy[j + 1].sap_id) {
                Student tmp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;                          /* already sorted */
    }
    print_sorted(copy, student_count, "Students in increasing order of SAP ID");
}

static void display_sorted_by_name(void) {
    if (student_count == 0) {
        printf("No student records available.\n");
        return;
    }
    Student copy[MAX_STUDENTS];                       /* original stays intact */
    for (int i = 0; i < student_count; i++) copy[i] = students[i];

    for (int pass = 0; pass < student_count - 1; pass++) {
        int swapped = 0;
        for (int j = 0; j < student_count - 1 - pass; j++) {
            if (strcmp(copy[j].name, copy[j + 1].name) > 0) {
                Student tmp = copy[j];
                copy[j] = copy[j + 1];
                copy[j + 1] = tmp;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    print_sorted(copy, student_count, "Students in increasing order of Name");
}

/* ---------- menu ---------- */

static void print_menu(void) {
    printf("\n=========== STUDENT RECORD SYSTEM ===========\n");
    printf(" 1. Add student\n");
    printf(" 2. Search student by SAP ID\n");
    printf(" 3. Calculate CGPA of each student\n");
    printf(" 4. Average CGPA of each year\n");
    printf(" 5. Display all students\n");
    printf(" 6. Delete student\n");
    printf(" 7. Display sorted by SAP ID\n");
    printf(" 8. Display sorted by Name\n");
    printf(" 0. Exit\n");
    printf("=============================================\n");
}

int main(void) {
    preload_students();

    for (;;) {
        print_menu();
        int choice = (int)read_long("Enter choice: ", 0, 8);
        switch (choice) {
            case 1: add_student();            break;
            case 2: search_student();         break;
            case 3: calculate_cgpa();         break;
            case 4: average_cgpa_by_year();   break;
            case 5: display_all();            break;
            case 6: delete_student();         break;
            case 7: display_sorted_by_sap();  break;
            case 8: display_sorted_by_name(); break;
            case 0: printf("Goodbye!\n");     return 0;
        }
    }
}