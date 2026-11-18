#include<stdio.h>
#include<string.h>

struct student
{
    int sap;
    int roll;
    char name[30];
    char phone[15];
    char email[40];
    int year;
    int sem;
    float sgpa[8];
};

int findBySap(struct student *s,int n,int sap)
{
    int i;
    for(i=0;i<n;i++)
    {
        if((s+i)->sap==sap)
        {
            return i;
        }
    }
    return -1;
}

float calcCgpa(struct student *p)
{
    int i,c;
    float sum;
    sum=0;
    c=0;
    for(i=0;i<8;i++)
    {
        if(p->sgpa[i]>=0)
        {
            sum=sum+p->sgpa[i];
            c++;
        }
    }
    if(c==0)
    {
        return 0;
    }
    return sum/c;
}

void printHeader()
{
    printf("%-10s %-5s %-12s %-11s %-4s %-4s\n","SAP ID","Roll","Name","Phone","Year","Sem");
}

void printRow(struct student *p)
{
    printf("%-10d %-5d %-12s %-11s %-4d %-4d\n",p->sap,p->roll,p->name,p->phone,p->year,p->sem);
}

void loadStudents(struct student *s,int *n)
{
    int i,j;
    int sap[5]={500101001,500102002,500103003,500104004,500105005};
    int roll[5]={1,12,23,34,45};
    char name[5][20]={"Aarav","Priya","Rohan","Ananya","Kabir"};
    char phone[5][15]={"9876500001","9876500002","9876500003","9876500004","9876500005"};
    char email[5][40]={"aarav@example.com","priya@example.com","rohan@example.com","ananya@example.com","kabir@example.com"};
    int year[5]={4,3,2,1,1};
    int sem[5]={8,6,4,2,1};
    float data[5][8]={
        {8.2,8.5,8.9,9.0,8.7,9.1,9.3,9.2},
        {7.5,7.9,8.1,8.0,8.4,8.6,0,0},
        {9.1,9.3,9.0,9.4,0,0,0,0},
        {7.2,7.2,0,0,0,0,0,0},
        {8.0,0,0,0,0,0,0,0}
    };
    for(i=0;i<5;i++)
    {
        (s+i)->sap=sap[i];
        (s+i)->roll=roll[i];
        strcpy((s+i)->name,name[i]);
        strcpy((s+i)->phone,phone[i]);
        strcpy((s+i)->email,email[i]);
        (s+i)->year=year[i];
        (s+i)->sem=sem[i];
        for(j=0;j<8;j++)
        {
            if(j<sem[i])
            {
                (s+i)->sgpa[j]=data[i][j];
            }
            else
            {
                (s+i)->sgpa[j]=-1;
            }
        }
    }
    *n=5;
}

void addStudent(struct student *s,int *n)
{
    struct student *p;
    int i,sap;
    if(*n>=50)
    {
        printf("Record list is full\n");
        return;
    }
    printf("Enter SAP ID\n");
    scanf("%d",&sap);
    if(findBySap(s,*n,sap)!=-1)
    {
        printf("SAP ID already exists\n");
        return;
    }
    p=s+*n;
    p->sap=sap;
    printf("Enter roll no\n");
    scanf("%d",&p->roll);
    printf("Enter name (one word)\n");
    scanf("%29s",p->name);
    printf("Enter phone no\n");
    scanf("%14s",p->phone);
    printf("Enter email id\n");
    scanf("%39s",p->email);
    do
    {
        printf("Enter year (1-4)\n");
        scanf("%d",&p->year);
    }while(p->year<1||p->year>4);
    do
    {
        printf("Enter current semester (%d or %d)\n",2*p->year-1,2*p->year);
        scanf("%d",&p->sem);
    }while(p->sem<2*p->year-1||p->sem>2*p->year);
    for(i=0;i<8;i++)
    {
        if(i<p->sem)
        {
            do
            {
                printf("Enter SGPA of semester %d (0-10)\n",i+1);
                scanf("%f",&p->sgpa[i]);
            }while(p->sgpa[i]<0||p->sgpa[i]>10);
        }
        else
        {
            p->sgpa[i]=-1;
        }
    }
    (*n)++;
    printf("Student added\n");
}

void searchStudent(struct student *s,int n)
{
    int sap,i,j;
    printf("Enter SAP ID to search\n");
    scanf("%d",&sap);
    i=findBySap(s,n,sap);
    if(i==-1)
    {
        printf("No student found with SAP ID %d\n",sap);
        return;
    }
    printf("SAP ID: %d\n",(s+i)->sap);
    printf("Roll No: %d\n",(s+i)->roll);
    printf("Name: %s\n",(s+i)->name);
    printf("Phone: %s\n",(s+i)->phone);
    printf("Email: %s\n",(s+i)->email);
    printf("Year: %d | Semester: %d\n",(s+i)->year,(s+i)->sem);
    for(j=0;j<8;j++)
    {
        if((s+i)->sgpa[j]>=0)
        {
            printf("SGPA Sem %d: %.2f\n",j+1,(s+i)->sgpa[j]);
        }
        else
        {
            printf("SGPA Sem %d: --\n",j+1);
        }
    }
}

void showCgpa(struct student *s,int n)
{
    int i;
    if(n==0)
    {
        printf("No student records\n");
        return;
    }
    printf("%-10s %-12s %-4s %-6s\n","SAP ID","Name","Year","CGPA");
    for(i=0;i<n;i++)
    {
        printf("%-10d %-12s %-4d %-6.2f\n",(s+i)->sap,(s+i)->name,(s+i)->year,calcCgpa(s+i));
    }
}

void yearAverage(struct student *s,int n)
{
    int y,i,c;
    float total;
    for(y=1;y<=4;y++)
    {
        total=0;
        c=0;
        for(i=0;i<n;i++)
        {
            if((s+i)->year==y)
            {
                total=total+calcCgpa(s+i);
                c++;
            }
        }
        if(c==0)
        {
            printf("Year %d: no students\n",y);
        }
        else
        {
            printf("Year %d: %d student(s) | Average CGPA: %.2f\n",y,c,total/c);
        }
    }
}

void displayAll(struct student *s,int n)
{
    int i;
    if(n==0)
    {
        printf("No student records\n");
        return;
    }
    printHeader();
    for(i=0;i<n;i++)
    {
        printRow(s+i);
    }
}

void deleteStudent(struct student *s,int *n)
{
    int sap,i,j;
    printf("Enter SAP ID to delete\n");
    scanf("%d",&sap);
    i=findBySap(s,*n,sap);
    if(i==-1)
    {
        printf("No student found with SAP ID %d\n",sap);
        return;
    }
    for(j=i;j<*n-1;j++)
    {
        *(s+j)=*(s+j+1);
    }
    (*n)--;
    printf("Record deleted\n");
}

void sortBySap(struct student *s,int n)
{
    struct student c[50],temp;
    int i,j;
    if(n==0)
    {
        printf("No student records\n");
        return;
    }
    for(i=0;i<n;i++)
    {
        *(c+i)=*(s+i);
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if((c+j)->sap>(c+j+1)->sap)
            {
                temp=*(c+j);
                *(c+j)=*(c+j+1);
                *(c+j+1)=temp;
            }
        }
    }
    printHeader();
    for(i=0;i<n;i++)
    {
        printRow(c+i);
    }
}

void sortByName(struct student *s,int n)
{
    struct student c[50],temp;
    int i,j;
    if(n==0)
    {
        printf("No student records\n");
        return;
    }
    for(i=0;i<n;i++)
    {
        *(c+i)=*(s+i);
    }
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-1-i;j++)
        {
            if(strcmp((c+j)->name,(c+j+1)->name)>0)
            {
                temp=*(c+j);
                *(c+j)=*(c+j+1);
                *(c+j+1)=temp;
            }
        }
    }
    printHeader();
    for(i=0;i<n;i++)
    {
        printRow(c+i);
    }
}

void advise(float cgpa)
{
    if(cgpa>=9.0)
    {
        printf("Category: Outstanding\n");
        printf("Advice: Outstanding work! You are among the top performers, so keep your routine and try to stretch further.\n");
    }
    else if(cgpa>=7.5)
    {
        printf("Category: Good\n");
        printf("Advice: Solid results. Pick your weakest subjects and give them extra weekly revision time.\n");
    }
    else if(cgpa>=6.0)
    {
        printf("Category: Average\n");
        printf("Advice: Your results are average. Revise tough topics regularly and solve more practice problems.\n");
    }
    else
    {
        printf("Category: At Risk\n");
        printf("Advice: Your CGPA is low. Strengthen the basics and meet your teachers for guidance as soon as possible.\n");
    }
}

void trendAdvice(float latest,float prev)
{
    if(latest<prev)
    {
        printf("Trend: Your last semester went down compared to the one before. Find out what went wrong and work on it.\n");
    }
    else if(latest>prev)
    {
        printf("Trend: Your last semester was better than the one before. Keep following the study plan that worked.\n");
    }
    else
    {
        printf("Trend: Your last two semesters are the same. Aim a little higher in the next semester.\n");
    }
}

void adviceMenu(struct student *s,int n)
{
    int sap,i,last;
    float cgpa;
    printf("Enter SAP ID for advice\n");
    scanf("%d",&sap);
    i=findBySap(s,n,sap);
    if(i==-1)
    {
        printf("No student found with SAP ID %d\n",sap);
        return;
    }
    cgpa=calcCgpa(s+i);
    printf("Name: %s | CGPA: %.2f\n",(s+i)->name,cgpa);
    advise(cgpa);
    last=(s+i)->sem-1;
    if(last==0)
    {
        printf("Trend: Only one semester available, so there is nothing to compare yet.\n");
    }
    else
    {
        printf("Previous SGPA: %.2f | Latest SGPA: %.2f\n",(s+i)->sgpa[last-1],(s+i)->sgpa[last]);
        trendAdvice((s+i)->sgpa[last],(s+i)->sgpa[last-1]);
    }
}

int main()
{
    struct student s[50];
    int n,choice;
    n=0;
    loadStudents(s,&n);
    do
    {
        printf("\n===== STUDENT RECORD SYSTEM =====\n");
        printf("1. Add student\n");
        printf("2. Search student by SAP ID\n");
        printf("3. CGPA of each student\n");
        printf("4. Average CGPA of each year\n");
        printf("5. Display all students\n");
        printf("6. Delete student\n");
        printf("7. Display sorted by SAP ID\n");
        printf("8. Display sorted by Name\n");
        printf("9. Academic advice\n");
        printf("0. Exit\n");
        printf("Enter choice\n");
        if(scanf("%d",&choice)!=1)
        {
            return 0;
        }
        switch(choice)
        {
            case 1: addStudent(s,&n); break;
            case 2: searchStudent(s,n); break;
            case 3: showCgpa(s,n); break;
            case 4: yearAverage(s,n); break;
            case 5: displayAll(s,n); break;
            case 6: deleteStudent(s,&n); break;
            case 7: sortBySap(s,n); break;
            case 8: sortByName(s,n); break;
            case 9: adviceMenu(s,n); break;
            case 0: printf("Goodbye\n"); break;
            default: printf("Invalid choice\n");
        }
    }while(choice!=0);
    return 0;
}