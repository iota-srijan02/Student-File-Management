#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

enum
{
    name_len = 64
};

struct student
{
    int roll;
    char name[name_len];
    int subject_count;
    int *marks;
    char **subject_name;
    float percentage;
    char grade;
};
void countSubject(struct student *s)
{
    int count;
    int cut = 1;
    while (cut > 0)
    {
        printf("enter the no. of subjects you want to enter: ");
        scanf("%d", &count);
        if (count > 0)
        {
            s->subject_count = count;
            cut--;
        }
        else
        {
            printf("enter a value greater than 0");
        }
    }
}
void allocateSubjects(struct student *s)
{
    s->marks = malloc((s->subject_count) * sizeof(int));
    s->subject_name = malloc(s->subject_count * sizeof(char *));
    for (int i = 0; i < s->subject_count; i++)
    {
        s->subject_name[i] = malloc(name_len);
    }
}

void nameSubject(struct student *s)
{
    
    for (int i = 0; i < s->subject_count; i++)
    {
    
        printf("Enter subject %d name: ", i + 1);
        fgets(s->subject_name[i], name_len, stdin);
        s->subject_name[i][strcspn(s->subject_name[i], "\n")] = '\0';
    }
}

int myResult(const struct student *s)
{
    if (s->subject_count <= 0)
        return 0;

    int *temp = malloc(s->subject_count * sizeof(int));
    if (temp == NULL)
        return 0;

    for (int i = 0; i < s->subject_count; i++)
    {
        printf("Enter marks for %s: ", s->subject_name[i]);
        scanf("%d", &s->marks[i]);
    }

    for (int i = 0; i < s->subject_count; i++)
    {
        temp[i] = s->marks[i];
    }

    for (int i = 0; i < s->subject_count - 1; i++)
    {
        for (int j = 0; j < s->subject_count - i - 1; j++)
        {
            if (temp[j] < temp[j + 1])
            {
                int swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }

    int limit = (s->subject_count < 5) ? s->subject_count : 5;
    int sum = 0;

    for (int i = 0; i < limit; i++)
        sum += temp[i];

    free(temp);
    return sum;
    
}

void myGradeFromTotal(struct student *s, int total)
{
    int divisor = (s->subject_count < 5) ? s->subject_count : 5;
    (*s).percentage = (float)(total) / divisor;
    int avg = (*s).percentage;

    if (avg >= 90)
    {
        (*s).grade = 'A';
    }
    else if (avg >= 80)
    {
        (*s).grade = 'B';
    }
    else if (avg >= 70)
    {
        (*s).grade = 'C';
    }
    else if (avg >= 60)
    {
        (*s).grade = 'D';
    }
    else if (avg >= 40)
    {
        (*s).grade = 'E';
    }
    else
    {
        (*s).grade = 'F';
    }
}

void add_student(struct student *s)
{

    char temp[name_len];

    float avg;
    printf("enter the roll no of the student\n");
    scanf("%d", &(*s).roll);
    getchar();

    printf("enter the name of the student\n");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    strcpy((*s).name, temp);
}

void write_student(struct student *s)
{
    FILE *fp;

    char filename[6];
    snprintf(filename, sizeof(filename), "%c.txt", s->grade);

    fp = fopen(filename, "ab");
    if (fp == NULL)
    {
        printf("error in file opening ");
        return;
    }
    fprintf(fp, "------------------------------------\n \n");
    fprintf(fp,
            "Roll: %d\n"
            "Name: %s\n",
            s->roll, s->name);
    for (int i = 0; i < s->subject_count; i++)
    {
        fprintf(fp, "%s : %d\n",
                s->subject_name[i], s->marks[i]);
    }
    // getchar(); not required here...
    fprintf(fp,
            "Grade: %c\n",
            s->grade);

    fclose(fp);
}
void read_txt_file(char filename[])
{
    FILE *fp;
    int ch;

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }

    printf("\nReading file: %s\n", filename);
    printf("---------------------------------\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    fclose(fp);
}
void freeStudent(struct student *s)
{
    free(s->marks);
    for (int i = 0; i < s->subject_count; i++)
    {
        free(s->subject_name[i]);
    }
    free(s->subject_name);
}

void deleteStudent()
{
    char filename[6];
    char line[256];
    char arrGrade[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int targetRoll, roll;

    printf("Enter roll number to delete: ");
    scanf("%d", &targetRoll);

    while (targetRoll <= 0)
    {
        printf("Enter roll number > 0: ");
        scanf("%d", &targetRoll);
    }

    for (int i = 0; i < 6; i++)
    {
        snprintf(filename, sizeof(filename), "%c.txt", arrGrade[i]);
        FILE *fp1 = fopen(filename, "r");
        if (!fp1)
            continue;

        FILE *fp2 = fopen("temp.txt", "w");
        if (!fp2)
        {
            fclose(fp1);
            continue;
        }

        int skip = 0;

        while (fgets(line, sizeof(line), fp1))
        {
            if (sscanf(line, "Roll: %d", &roll) == 1 && roll == targetRoll)
                skip = 1;

            if (!skip)
                fputs(line, fp2);

            if (strncmp(line, "Grade:", 6) == 0)
                skip = 0;
        }

        fclose(fp1);
        fclose(fp2);
        remove(filename);
        rename("temp.txt", filename);
    }
}

void editRoll()
{
    char filename[6];
    char line[256];
    char arrGrade[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int changeRoll, roll;
    printf("Enter roll number of the student to update: ");
    scanf("%d", &changeRoll);
    while (changeRoll <= 0)
    {
        printf("Enter roll number > 0: ");
        scanf("%d", &changeRoll);
    }

    for (int i = 0; i < 6; i++)
    {
        snprintf(filename, sizeof(filename), "%c.txt", arrGrade[i]);
        FILE *fp1 = fopen(filename, "r");
        if (!fp1)
            continue;

        FILE *fp2 = fopen("temp.txt", "w");
        if (!fp2)
        {
            fclose(fp1);
            continue;
        }

        int skip = 0;

        while (fgets(line, sizeof(line), fp1))
        {
            if (sscanf(line, "Roll: %d", &roll) == 1 && roll == changeRoll)
            {
                fprintf(fp2, "Roll: %d\n", changeRoll);
            }
            else
            {
                fputs(line, fp2);
            }
        }
        fclose(fp1);
        fclose(fp2);
        remove(filename);
        rename("temp.txt", filename);
    }
}

void editName()
{
    char filename[6];
    char line[256];
    char changeName[100];
    char arrGrade[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int verifyRoll, roll;
    printf("Enter roll number of the student to update: ");
    scanf("%d", &verifyRoll);
    while (verifyRoll <= 0)
    {
        printf("Enter roll number > 0: ");
        scanf("%d", &verifyRoll);
    }
    getchar();
    printf("enter the edited name of the student");
    fgets(changeName, sizeof(changeName), stdin);

    for (int i = 0; i < 6; i++)
    {
        snprintf(filename, sizeof(filename), "%c.txt", arrGrade[i]);
        FILE *fp1 = fopen(filename, "r");
        if (!fp1)
            continue;

        FILE *fp2 = fopen("temp.txt", "w");
        if (!fp2)
        {
            fclose(fp1);
            continue;
        }

        int skip = 0;

        while (fgets(line, sizeof(line), fp1))
        {
            if (sscanf(line, "Roll: %d", &roll) == 1 && roll == verifyRoll)
            {
                skip = 1;
                fputs(line, fp2);
                continue;
            }

            if (!skip)
            {
                fputs(line, fp2);
            }
            if (skip && strncmp(line, "Name:", 5) == 0)
            {
                fprintf(fp2, "Name: %s\n", changeName);
                skip = 0;
            }
            else if (skip)
            {
                fputs(line, fp2);
            }
        }
        fclose(fp1);
        fclose(fp2);
        remove(filename);
        rename("temp.txt", filename);
    }
}

int editMarks()
{
    char filename[6];
    char line[256];
    char arrGrade[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int verifyRoll, roll;
    char targetSubject[100];

    char newTargetSubject[100];
    int i = 0, flag = 0;
    int subjectLen = 0;
    int editSubjectLen = 0, correctLen = 0;
    int editedMarks, rollFound = 0;

    printf("Enter roll number of the student to update: ");
    scanf("%d", &verifyRoll);
    while (verifyRoll <= 0)
    {
        printf("Enter roll number > 0: ");
        scanf("%d", &verifyRoll);
    }
    getchar();
    printf("enter the name of the subject whose marks you want to edit...\n");
    fgets(targetSubject, sizeof(targetSubject), stdin);
    targetSubject[strcspn(targetSubject, "\n")] = '\0';
    
    // Normalize target subject name (remove spaces, convert to lowercase)
    int j = 0;
    for (i = 0; targetSubject[i] != '\0'; i++)
    {
        if (!isspace(targetSubject[i]))
            newTargetSubject[j++] = tolower(targetSubject[i]);
    }
    newTargetSubject[j] = '\0';
    subjectLen = j;

    int skip = 0;
    for (int gradeIdx = 0; gradeIdx < 6; gradeIdx++)
    {
        snprintf(filename, sizeof(filename), "%c.txt", arrGrade[gradeIdx]);
        remove("temp.txt");
        FILE *fp1 = fopen(filename, "r");
        if (!fp1)
            continue;

        FILE *fp2 = fopen("temp.txt", "w");
        if (!fp2)
        {
            fclose(fp1);
            continue;
        }
        
        rollFound = 0;
        flag = 0;
        skip = 0;
        
        while (fgets(line, sizeof(line), fp1))
        {
            editSubjectLen = 0;
            correctLen = 0;
            int k = 0;
            
            if (flag == 0)
            {
                // Check if this is the target roll number
                if (sscanf(line, "Roll: %d", &roll) == 1 && roll == verifyRoll)
                {
                    fputs(line, fp2);
                    skip = 1;
                    rollFound = 1;
                    continue;
                }

                //this is used to copy the part of the file that is not part of the target student's record
                if (!skip && rollFound && strncmp(line, "------------------------------------", 36) != 0)
                {
                    fputs(line, fp2);
                }

                // If we reach Grade line and still we couldnot find the subject, then it simplydoesn't exist
                if (skip == 1 && strncmp(line, "Grade:", 6) == 0)
                {
                    if (flag == 0)
                    {
                        printf("Subject not found...please check the spelling!\n");
                    }
                    fputs(line, fp2);
                    skip = 0;
                    continue;
                }
                
                //parse subject lines when we're inside the target student's data
                if (skip == 1)
                {
                    // Extract subject name from the line (before the colon)
                    char lineSubject[100] = {0}; // this initializes every element of the array to 0...
                    int lineSubjIdx = 0;
                    
                    while (line[k] != ':' && line[k] != '\0' && lineSubjIdx < 99)
                    {
                        if (!isspace(line[k]))
                        {
                            lineSubject[lineSubjIdx++] = tolower(line[k]);
                        }
                        k++;
                    }
                    lineSubject[lineSubjIdx] = '\0';
                    editSubjectLen = lineSubjIdx;
                    
                    // Check if subject names match or not
                    if (editSubjectLen == subjectLen)
                    {
                        int match = 1;
                        for (int m = 0; m < subjectLen; m++)
                        {
                            if (lineSubject[m] != newTargetSubject[m])
                            {
                                match = 0;
                                break;
                            }
                        }
                        
                        if (match == 1)
                        {
                            printf("enter the edited marks: ");
                            scanf("%d", &editedMarks);
                            getchar();
                            fprintf(fp2, "%s : %d\n", targetSubject, editedMarks);
                            flag = 1;
                            skip = 0;
                            continue;
                        }
                    }
                    
                    // If we reach here, this is not the subject we're looking for
                    fputs(line, fp2);
                }
            }
            else
            {
                // If we've already edited the marks, just copy the rest
                fputs(line, fp2);
            }
        }
        
        fclose(fp1);
        fclose(fp2);
        
        if (flag == 1 && rollFound == 1)
        {
            remove(filename);
            rename("temp.txt", filename);
            printf("Marks updated successfully!\n");
            return verifyRoll;
        }
        else
        {
            remove("temp.txt");
        }
    }
    
    if (!rollFound)
    {
        printf("Student with roll number %d not found!\n", verifyRoll);
    }
    
    return verifyRoll;
}

int editGrade(int targetRoll)
{
    char filename[6];
    char line[256];
    char arrGrade[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    char oldGrade = 0, updatedGrade = 0;
    int roll;

    // step 1: find old grade
    for (int i = 0; i < 6; i++)
    {
        snprintf(filename, sizeof(filename), "%c.txt", arrGrade[i]);
        FILE *fp = fopen(filename, "r");
        if (!fp)
            continue;

        while (fgets(line, sizeof(line), fp))
        {
            if (sscanf(line, "Roll: %d", &roll) == 1 && roll == targetRoll)
            {
                oldGrade = arrGrade[i];
                break;
            }
        }
        fclose(fp);
        if (oldGrade)
            break;
    }

    if (!oldGrade)
    {
        printf("Student not found\n");
        return 0;
    }

    // step 2: recalc grade 
    int marks[20], count = 0;
    int skip = 0;

    snprintf(filename, sizeof(filename), "%c.txt", oldGrade);
    FILE *fp = fopen(filename, "r");
    if (!fp)
        return 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "Roll: %d", &roll) == 1)
        {
            if (roll == targetRoll)
                skip = 1;
            else
                skip = 0;
            continue;
        }

        if (!skip)
            continue;

        if (strncmp(line, "Grade:", 6) == 0)
            break;

        if (strchr(line, ':') &&
            strncmp(line, "Name:", 5) != 0 &&
            sscanf(line, "%*[^:]: %d", &marks[count]) == 1)
        {
            count++;
            if (count >= 20)
                break;
        }
    }

    fclose(fp);

    /* sort marks in descending order */
    for (int i = 0; i < count - 1; i++)
        for (int j = i + 1; j < count; j++)
            if (marks[j] > marks[i])
            {
                int t = marks[i];
                marks[i] = marks[j];
                marks[j] = t;
            }

    int limit = (count < 5) ? count : 5;
    int total = 0;
    for (int i = 0; i < limit; i++)
        total += marks[i];

    float percent = (float)total / limit;

    if (percent >= 90)
        updatedGrade = 'A';
    else if (percent >= 80)
        updatedGrade = 'B';
    else if (percent >= 70)
        updatedGrade = 'C';
    else if (percent >= 60)
        updatedGrade = 'D';
    else if (percent >= 40)
        updatedGrade = 'E';
    else
        updatedGrade = 'F';

    // step 3: if grade same → update only 
    if (oldGrade == updatedGrade)
    {
        snprintf(filename, sizeof(filename), "%c.txt", oldGrade);
        FILE *fp1 = fopen(filename, "r");
        FILE *fp2 = fopen("temp.txt", "w");

        skip = 0;
        while (fgets(line, sizeof(line), fp1))
        {
            if (sscanf(line, "Roll: %d", &roll) == 1 && roll == targetRoll)
                skip = 1;

            if (skip && strncmp(line, "Grade:", 6) == 0)
            {
                fprintf(fp2, "Grade: %c\n", updatedGrade);
                skip = 0;
            }
            else
                fputs(line, fp2);
        }

        fclose(fp1);
        fclose(fp2);
        remove(filename);
        rename("temp.txt", filename);
        return 1;
    }

    // step 4: move student to new grade file 
    FILE *fpRemain = fopen("temp.txt", "w");
    FILE *fpBlock = fopen("temp2.txt", "w");

    snprintf(filename, sizeof(filename), "%c.txt", oldGrade);
    fp = fopen(filename, "r");

    skip = 0;
    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "Roll: %d", &roll) == 1 && roll == targetRoll)
        {
            skip = 1;
            fputs(line, fpBlock);
            continue;
        }

        if (skip)
        {
            if (strncmp(line, "Grade:", 6) == 0)
            {
                fprintf(fpBlock, "Grade: %c\n", updatedGrade);
                skip = 0;
            }
            else
                fputs(line, fpBlock);
        }
        else
            fputs(line, fpRemain);
    }

    fclose(fp);
    fclose(fpRemain);
    fclose(fpBlock);

    remove(filename);
    rename("temp.txt", filename);

    /* append to new grade file */
    snprintf(filename, sizeof(filename), "%c.txt", updatedGrade);
    FILE *fpFinal = fopen(filename, "a");
    FILE *fpRead = fopen("temp2.txt", "r");

    while (fgets(line, sizeof(line), fpRead))
        fputs(line, fpFinal);

    fclose(fpFinal);
    fclose(fpRead);
    remove("temp2.txt");

    return 1;
}

void updateStudent()
{
    int targetRoll;
    char choice;
    do
    {
        printf("enter 1 to edit Roll\n");
        printf("enter 2 to edit Name\n");
        printf("enter 3 to edit Marks\n");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            editRoll();
            break;
        case '2':
            editName();
            break;
        case '3':

            targetRoll = editMarks();
            editGrade(targetRoll);
            break;
        default:
            printf("Invalid Choice\n");
        }
        printf("Do you want to edit again?(y/n):");
        scanf(" %c", &choice);
    } while (choice == 'y' || choice == 'Y');
}

int main()
{
    struct student s;
    char ult_choice;
    char choice = 'y';
    char choice2;
    int pass = 1669;

    printf("Press 'R' to read existing students, 'W' to write new students, 'D' to delete the data of the student, 'U' to update student's data : ");
    scanf(" %c", &ult_choice);
    if (ult_choice == 'W' || ult_choice == 'w')
    {

        while (choice == 'y' || choice == 'Y')
        {
            add_student(&s);
            countSubject(&s);
            allocateSubjects(&s);
            getchar();
            nameSubject(&s);
            // myResult(&s);
            int total = myResult(&s);
            myGradeFromTotal(&s, total);
            s.grade = toupper(s.grade);
            write_student(&s);
            freeStudent(&s);
            printf("do you want to enter more student details-->:(y/n)");
            scanf(" %c", &choice);
        }

        printf("Do you want to read student files? (y/n): ");
        scanf(" %c", &choice2);

        while (choice2 == 'y' || choice2 == 'Y')
        {
            char grade;
            char filename[6];

            printf("Enter grade file to read (A/B/C/D/E/F): ");
            scanf(" %c", &grade);
            grade = toupper(grade);

            snprintf(filename, sizeof(filename), "%c.txt", grade);

            read_txt_file(filename);

            printf("Read another file? (y/n): ");
            scanf(" %c", &choice2);
        }
    }
    else if (ult_choice == 'r' || ult_choice == 'R')
    {
        choice2 = 'y';
        while (choice2 == 'y' || choice2 == 'Y')
        {
            char grade;
            char filename[6];

            printf("Enter grade file to read (A/B/C/D/E/F): ");
            scanf(" %c", &grade);
            grade = toupper(grade);
            snprintf(filename, sizeof(filename), "%c.txt", grade);

            read_txt_file(filename);

            printf("Read another file? (y/n): ");
            scanf(" %c", &choice2);
        }
    }
    else if (ult_choice == 'D' || ult_choice == 'd')
    {

        int enteredPass;
        printf("enter your id: ");
        scanf("%d", &enteredPass);
        if (enteredPass == pass)
        {
            deleteStudent();
        }

        else
        {
            printf("invalid password, try again!                                                                              ");
        }
        printf("Program ended.\n");
    }
    else if (ult_choice == 'u' || ult_choice == 'U')
    {
        updateStudent();
        printf("Program ended... ");
    }

    else
    {
        printf("invalid choice is entered!!");
    }
    return 0;
}
