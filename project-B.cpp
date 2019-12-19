#include<iostream>
#include<fstream>
#include<conio.h>
#include<string>
using namespace std;
class employee
{
private:
char name[30];
int id;
char post[30];
int salary;
public:
void read();
void view();
void writetofile();
void readfromfile();
void anemployee();
void edit();
void erase();
int idd();
};
void employee::read()
{
//system("cls");
cout<<"\n\t\t\tEnter name of an employee:";
cin>>name;
cout<<"\n\t\t\tEnter ID number:";
cin>>id; 
cout<<"\n\t\t\tEnter designation:";
cin>>post;
cout<<"\n\t\t\tEnter salary:";
cin>>salary;

}
void employee::view()
{
//system("cls");	
cout<<"\n\t\tIdentity No.:"<<id<<"\t\tName:"<<name<<"\t\tPost:"<<post<<"\t\tSalary:"<<salary;
}
void employee::writetofile()
{
//system("cls");	
char ch;
ofstream outfile("employee.dat",ios::binary|ios::app);
read();
cout<<"\n\t\t\tDo you wish to save the above details(y/n)	:	";
cin>>ch;
if(ch=='y')
{
outfile.write(reinterpret_cast<char *>(this),sizeof(*this));
cout<<"\n\t\t\tSaved.";
}
	else
		read();
outfile.close();
}
void employee::readfromfile()
{
//system("cls");
ifstream infile("employee.dat",ios::binary);
while(!infile.eof())
{
if(infile.read(reinterpret_cast<char *>(this),sizeof(*this))>0)
view();
}
infile.close();
}
void employee::anemployee()
{
//system("cls");	
employee e,e1;
	int idn;
	cout<<"\n\t\tEnter id number of an employee:";
 cin>>idn;
 fstream file;
 file.open("employee.dat",ios::in|ios::binary);
 file.seekg(0);
 while(file.read((char*)&e,sizeof(e)))
  {
   if(e.idd()==idn)
   {
   	cout<<"\n\t\tHis/Her details are:";
    e1.view();
   }
   else   
   cout<<"\n\t\tID not found.";
 
}

 file.close();
}

void employee::edit()
{
	employee e,e1;
	int idn;
	cout<<"\n\t\tEnter id number of an employee:";
 cin>>idn;
 fstream file;
 file.open("employee.dat",ios::in|ios::out|ios::binary|ios::ate);
 file.seekg(0);
 while(file.read((char*)&e,sizeof(e)))
  {
   if(e.id==idn)
   {
    cout<<"\n\t\t New Value: ";
    e1.read();
    file.seekp(-sizeof(e),ios::cur);
    file.write((char*)&e1,sizeof(e1));
   }
  }
 file.close();
}
int employee::idd()
  {
  return id;
  }
void employee::erase()
{
employee e;
	int idn;
	cout<<"\n\t\tEnter id number of an employee:";
 cin>>idn;
ifstream file1;
file1.open("employee.dat",ios::binary);
ofstream file2;
file2.open("employee1.dat",ios::out|ios::binary);
while(file1.read((char*)&e,sizeof(e)))
{
if(e.idd()!=idn)
{
file2.write((char*)&e,sizeof(e));
}
}
file1.close();
file2.close();
remove("employee.dat");
rename("employee1.dat","employee.dat");
cout<<"\n\t\t\tDeleted.";
}
int main()
{
	string password1="kec";
 string password;
 cout <<"\n\t\t\tPlease type in your password:" ;
 cin >> password;
 if (password == password1)
 {
cout << "\n\t\t\tWELCOME";
cout << "\n";
}   
else
{
cout << "\n\t\t\tPlease type in the correct password.";
cout << "\n";
}
    
employee s;
int choice;
cout<<"\n\t\t\t*************MAIN MENU*************";
cout<<"\n\t\t\t1.Add new employee.";
cout<<"\n\t\t\t2.View list of the employees.";
cout<<"\n\t\t\t3.View details of an employee.";
cout<<"\n\t\t\t4.Edit details of an employee.";
cout<<"\n\t\t\t5.Remove details of an employee.";
cout<<"\n\t\t\t6.Exit.";
while(true)
{
cout<<"\n\n\t\t\tEnter choice:";
cin>>choice;
switch(choice)
{
case 1:s.writetofile();
    break;
case 2:s.readfromfile();
    break;
case 3:s.anemployee();
    break;
case 4:s.edit();
    break;    
case 5:s.erase();
    break;
case 6:exit(0);
    break;
default:
cout<<"\n\tInvalid choice.";
exit(0);
}
}
getch();
return 0;
}
