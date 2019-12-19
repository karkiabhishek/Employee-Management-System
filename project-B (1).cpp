#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
using namespace std;

class Employee
{
    char name[30];
    char post[30];
    long salary;
    int id;
public:
    Employee():name(""),post(""),salary(0){}
    char *getname(){return name;}
    int getid(){return id;}
    void inputData()
    {
        cout<<"Enter employee name:";
        fflush(stdin);
        cin.getline(name,30);
        cout<<"Enter ID:";
        cin>>id;
        cout<<"Enter designation:";
        cin>>post;
        cout<<"Enter the salary:";
        cin>>salary;
    }
    void showEmployee()
    {
        cout<<setw(10)<<""<<setw(4)<<left<<id<<setw(16)<<""<<setw(30)<<left<<name<<setw(30)<<left<<post<<setw(10)<<left<<salary<<endl;
    }

};

void addEmployee()
{
    system("cls");
    Employee newEmployee;
    newEmployee.inputData();
    ofstream outFile;
    outFile.open("Employee.dat",ios::binary|ios::app);
    outFile.write(reinterpret_cast<char*>(&newEmployee),sizeof(newEmployee));
    outFile.close();
    getch();
}

void viewEmployeeFromFile()
{
    system("cls");
    Employee emp;
    ifstream inputFile("Employee.dat",ios::binary);
    cout<<setw(10)<<""<<setw(4)<<left<<"ID"<<setw(16)<<""<<setw(30)<<left<<"NAME"<<setw(30)<<left<<"POST"<<setw(10)<<left<<"SALARY"<<endl;
    cout<<setw(7)<<""<<setfill('-')<<setw(93)<<left<<" "<<endl;
    cout.fill('\0');
    while(inputFile.read(reinterpret_cast<char*>(&emp),sizeof(emp)))
    {
        emp.showEmployee();

    }
    inputFile.close();
    getch();
}

void editEmployee()
{
    system("cls");
    Employee emp;
    char name[30];
    fstream ioutFile("Employee.dat",ios::binary|ios::in|ios::out);
    cout<<"1. Edit by ID"<<endl;
    cout<<"2. Edit by Name"<<endl;
    char choice;
    fflush(stdin);
    cout<<"\nSelect the method:";
    choice=getch();
    if(choice=='1')
    {
        system("cls");
        cout<<"Enter the ID:";
        int id;
        cin>>id;
        while(ioutFile.read(reinterpret_cast<char*>(&emp),sizeof(emp)))
        {
        if(id==emp.getid())
            {
            emp.inputData();
            ioutFile.seekp((int)ioutFile.tellg()-sizeof(emp));
            ioutFile.write((char*)(&emp),sizeof(emp));

            }
        }
    }
    else if(choice=='2')
    {system("cls");
    fflush(stdin);
    cout<<"Enter the name of Employee:";
    cin.getline(name,30);
    while(ioutFile.read(reinterpret_cast<char*>(&emp),sizeof(emp)))
    {
        if(strcmp(emp.getname(),name)==0)
        {
            emp.inputData();
            ioutFile.seekp((int)ioutFile.tellg()-sizeof(emp));
            ioutFile.write((char*)(&emp),sizeof(emp));

        }
    }
    }
    ioutFile.close();
}
void removeEmployee()
{
    system("cls");
    Employee emp;
    char name[30];
    fstream ioutFile("Employee.dat",ios::binary|ios::in);
    fstream outFile("temp.dat",ios::binary|ios::out);
    cout<<"1. Remove by ID"<<endl;
    cout<<"2. Remove by Name"<<endl;
    char choice;
    fflush(stdin);
    cout<<"\nSelect the method:";
    choice=getch();
    int flag=0;
    if(choice=='1')
    {
        system("cls");
        cout<<"Enter the ID:";
        int id;
        cin>>id;
        while(ioutFile.read(reinterpret_cast<char*>(&emp),sizeof(emp)))
        {
        if(id==emp.getid()) {flag=1;continue;}
        outFile.write((char*)(&emp),sizeof(emp));
        }
    }
    else if(choice=='2')
    {system("cls");
    fflush(stdin);
    cout<<"Enter the name of Employee:";
    cin.getline(name,30);
    while(ioutFile.read(reinterpret_cast<char*>(&emp),sizeof(emp)))
    {
        if(strcmp(emp.getname(),name)==0) {flag=1;continue;}
        outFile.write((char*)(&emp),sizeof(emp));
    }
    }
    ioutFile.close();
    outFile.close();
    remove("Employee.dat");
    rename("temp.dat","Employee.dat");
    if(flag)cout<<"Record Deleted Successfully!";
    else cout<<"No Such Record Found!!";
    getch();
}
void sortEmployee()
{
    system("cls");
    Employee emp,e;
    char name[30];
    fstream ioutFile("Employee.dat",ios::binary|ios::in|ios::out);
    cout<<"1. Sort by ID"<<endl;
    cout<<"2. Sort by Name"<<endl;
    char choice;
    fflush(stdin);
    cout<<"\nSelect the method:";
    choice=getch();
    int totalEmployees=0;
    while(ioutFile.read(reinterpret_cast<char*>(&emp),sizeof(emp))) totalEmployees++;
    cout<<totalEmployees;
    getch();
    int loc;
    ioutFile.clear();
    if(choice=='1')
    {
        system("cls");
        Employee temp;
        for(int i=0;i<totalEmployees;i++)
        {

            ioutFile.seekg(i*sizeof(emp));
            ioutFile.read(reinterpret_cast<char*>(&emp),sizeof(emp));
            temp=emp;
            loc=0;
            for(int j=i+1;j<totalEmployees;j++)
            {
                ioutFile.read(reinterpret_cast<char*>(&e),sizeof(e));
                if(e.getid()<temp.getid()) {loc=j;temp=e;}

            }

            if(loc){ioutFile.seekp(loc*sizeof(emp));
            ioutFile.write((char*)(&emp),sizeof(emp));
            ioutFile.seekp(i*sizeof(emp));
            ioutFile.write((char*)(&temp),sizeof(temp));
            }
        }

    }
    else if(choice=='2')
    {
        system("cls");
        Employee temp;
        for(int i=0;i<totalEmployees;i++)
        {

            ioutFile.seekg(i*sizeof(emp));
            ioutFile.read(reinterpret_cast<char*>(&emp),sizeof(emp));
            temp=emp;
            loc=0;
            for(int j=i+1;j<totalEmployees;j++)
            {
                ioutFile.read(reinterpret_cast<char*>(&e),sizeof(e));
                if(strcmp(e.getname(),temp.getname())<0) {loc=j;temp=e;}

            }

            if(loc){ioutFile.seekp(loc*sizeof(emp));
            ioutFile.write((char*)(&emp),sizeof(emp));
            ioutFile.seekp(i*sizeof(emp));
            ioutFile.write((char*)(&temp),sizeof(temp));
            }
            ioutFile.clear();
        }

    }
    ioutFile.close();
    getch();
}
int main()
{
    char choice;
    while(true)
    {
    system("cls");
    cout<<"\n\t\t\t*************MAIN MENU*************";
    cout<<"\n\t\t\t1.Add new employee.";
    cout<<"\n\t\t\t2.View list of the employees.";
    cout<<"\n\t\t\t3.View details of an employee.";
    cout<<"\n\t\t\t4.Remove details of an employee.";
    cout<<"\n\t\t\t5.Exit.";
    cout<<"\n\n\t\t\tEnter the choice:";
    choice=getch();
    cout<<choice<<endl;
    if (choice=='1') addEmployee();
    else if (choice=='2') viewEmployeeFromFile();
    else if (choice=='3') editEmployee();
    else if (choice=='4') removeEmployee();
    else if (choice=='5') sortEmployee();
    else break;
    }
    getch();
    return 0;
}
