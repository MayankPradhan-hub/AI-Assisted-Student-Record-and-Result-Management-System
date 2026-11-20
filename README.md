# Student Record Management System

A console-based, menu-driven application written in C. It keeps records of up to 50 students and lets you add, search, delete and sort them, calculate CGPA, and get simple academic advice. Five students are pre-loaded so you can test without typing anything.

## What it does

Each student record stores:

| Field | Notes |
|---|---|
| SAP ID | 9-digit number, must be unique |
| Roll No. | integer |
| Name | one word (no spaces) |
| Phone No. | up to 14 characters |
| Email ID | up to 39 characters |
| Year | 1 to 4 |
| Semester | current semester: 1 or 2 for year 1, 3 or 4 for year 2, and so on |
| SGPA | up to 8 values, one per semester |

SGPAs are stored only for semesters up to the student's current semester. The remaining semesters are marked as "not available" and are skipped in every calculation.

## Menu

```
1. Add student
2. Search student by SAP ID
3. CGPA of each student
4. Average CGPA of each year
5. Display all students
6. Delete student
7. Display sorted by SAP ID
8. Display sorted by Name
9. Academic advice
0. Exit
```

## Features

1. **Add student:** asks for every field. It rejects a duplicate SAP ID, a SAP ID that is not 9 digits, a year outside 1-4, a semester that does not match the year, and an SGPA outside 0-10. It asks only for SGPAs up to the current semester. Every numeric prompt re-asks when the input is not a valid number in range.
2. **Search by SAP ID:** shows the full record, including all 8 SGPA slots (`--` where not available).
3. **CGPA of each student:** CGPA is the average of the available SGPAs.
4. **Average CGPA by year:** averages the CGPAs of the students in each year (1 to 4). A year with no students prints "no students".
5. **Display all students:** prints a table in the order the records were added.
6. **Delete student:** removes a record by SAP ID. The later records are shifted one place to the left.
7. **Sort by SAP ID:** displays records in increasing order of SAP ID.
8. **Sort by Name:** displays records in increasing order of name. Names are compared with `strcmp` on lowercase copies, so `zebra` sorts before `Zed`.
9. **Academic advice:** takes a SAP ID, calculates the CGPA, and prints a category with an advice message. It then compares the latest SGPA with the previous one and prints a trend message.

Both sorts use **bubble sort on a copy** of the array, so the original order of the records is never changed.

### Advice categories

| CGPA | Category |
|---|---|
| 9.0 and above | Outstanding |
| 7.5 to 8.99 | Good |
| 6.0 to 7.49 | Average |
| Below 6.0 | At Risk |

### Trend message

| Latest SGPA compared with previous | Message |
|---|---|
| Lower | Performance went down; find out what went wrong |
| Higher | Performance improved; keep following the same plan |
| Equal | Performance is stable; aim a little higher |

A student with only one semester gets "nothing to compare yet".

## Pre-loaded data

| SAP ID | Name | Year | Semester |
|---|---|---|---|
| 500101001 | Aarav | 4 | 8 |
| 500102002 | Priya | 3 | 6 |
| 500103003 | Rohan | 2 | 4 |
| 500104004 | Ananya | 1 | 2 |
| 500105005 | Kabir | 1 | 1 |

## Program structure

- `struct student` holds one record.
- The array of students lives in `main()` and is passed to each function along with the student count.
- Each menu option has its own function (`addStudent`, `searchStudent`, `showCgpa`, `yearAverage`, `displayAll`, `deleteStudent`, `sortBySap`, `sortByName`, `adviceMenu`).
- Helpers: `findBySap`, `calcCgpa`, `advise`, `trendAdvice`, `printHeader`, `printRow` and `loadStudents`.

## Limitations

- Records are kept in memory only, so they are lost when the program exits.
- Names, phone numbers and emails are one word each; anything after the first space is ignored.
- Maximum of 50 students.
