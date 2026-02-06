Student File Management

Student File Management is a beginner-friendly command-line project written in C

Designed for students learning C programming and working on academic or practice projects

Uses text files instead of databases to store and manage student records

Helps understand how real programs handle persistent data using files

Data Organization

Student records are stored in grade-wise files (A.txt to F.txt)

Each student record follows a fixed and readable structure:

Separator line

Roll number

Student name

Subject-wise marks

Final grade

This format makes files easy to read, debug, and update manually

Features

Add Student Records

Enter roll number, name, number of subjects, subject names, and marks

Uses dynamic memory allocation for subjects and marks

Automatically calculates percentage and grade

Read Student Data

View records grade-wise from text files

Edit Student Details

Update roll number, name, or subject marks

Uses temporary files to safely modify data

Automatic Grade Recalculation

Grade is recalculated after marks are edited

Student record is moved to the correct grade file if grade changes

Delete Student Records

Remove students by roll number without affecting other data

Learning Outcomes

File handling in C (fopen, fgets, fprintf, rename, remove)

Dynamic memory allocation

String parsing and validation

Safe file updates using temporary files

Logical flow for real-world applications

Code is written in a step-by-step and readable manner

Suitable for college projects, beginners, and self-learning

Can be extended to binary files or database-based systems in the future
