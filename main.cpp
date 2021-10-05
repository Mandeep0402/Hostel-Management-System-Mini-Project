#include<iostream>
#include<fstream>
#include<limits>
#include<cstring>
using namespace std;
 
/*--------------------------------------------------------------------------------------------------------------------------------------
Hostel : class
Variable                type                use
***************************************************************************************
name                    string          Name of hostel
capacity                int             Total number of students the hostel can board
curr_num                int             Number of students currently boarding in hostel
 
Methods                 type                use
***************************************************************************************
create()                void                To take input
print()                 void                To print the values to output
retname()               string              Returns the name
retcap()                int                 Returns the capacity
retcurr()               int                 Returns number of students boarding
inc_curr()              void                To increment the value of curr_num
dec_curr()              void                To decrement the value of curr_num
***************************************************************************************
*/
class Hostel{
    char name[15];
    int capacity;
    int curr_num;
public:
    void create(){
        cout << "Enter name of hostel: ";
        cin.getline(name, 15);
        cout << "Enter capacity of hostel: ";
        cin >> capacity;
        curr_num = 0;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    void print(){
        cout << name << "\n";
        cout << "Total capacity: " << capacity << "\n";
        cout << "Number of students currently boarding: " << curr_num << "\n";
    }
    char* retname(){
        return name;
    }
    int retcap(){
        return capacity;
    }
    int retcurr(){
        return curr_num;
    }
    void inc_curr(){
        curr_num++;
    }
    void dec_curr(){
        curr_num--;
    }
};
/* Declaration of find_hostel and inc_hostel functions
for use in Student class*/
bool find_hostel(char hostel_name[]);
void inc_hostel(char hname[]);
 
/*--------------------------------------------------------------------------------------------------------------------------------------
Student : class
Variable                type                use
*******************************************************************************************
fname                   string          First name of student
lname                   string          Surname of student
hname                   string          Name of hostel the student is currently residing at
rollno                  int             Roll number of student
roomno                  int             Room Number of student
phno                    string          Phone Number of student
 
Methods                 type                use
*******************************************************************************************
create()                void                To take input
print()                 void                To print the values to output
retroll()               int                 Returns the roll number
rethname()              string              Returns the hostel name
retfname()              string              Returns the first name
change_room(int)        void                Changes the value of roomno variable
change_hostel(string)   void                Changes the value of hostel variable
*******************************************************************************************
*/
class Student{
    char fname[10];
    char lname[15];
    char hname[15];
    int rollno;
    int roomno;
    char phno[11];
public:
    void create(){
        cout << "Enter First Name: ";
        cin.getline(fname,10);
        cout << "Enter Last Name: ";
        cin.getline(lname,15);
        cout << "Enter Roll Number: ";
        cin >> rollno;
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout << "Enter Hostel Name: ";
        cin.getline(hname,15);
        while(!find_hostel(hname)){
            cout << "Hostel not found, please try again:\n";
            cin.getline(hname,15);
        }
        inc_hostel(hname);
        cout << "Enter Room Number: ";
        cin >> roomno;
        cout << "Enter Phone Number: ";
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cin.getline(phno,11);
    }
    void print(){
        cout << fname << " " << lname << "\n";
        cout << rollno << "\n";
        cout << "Hostel name: " << hname << "\n";
        cout << "Room Number: " << roomno << "\n";
        cout << "Phone Number: " << phno << "\n";
    }
    int retroll(){
        return rollno;
    }
 
    char* rethname(){
        return hname;
    }
 
    char* retfname(){
        return fname;
    }
    void change_room(int room){
        cout << "Old Room: " << roomno << "\n";
        roomno = room;
        cout << "New Room: " << roomno << "\n";
    }
    void change_hostel(char new_hname[15]){
        strcpy(hname,new_hname);
    }
};
/* Function used to find a hostel from file and use
inc_curr() function on it */
void inc_hostel(char hname[]){
    Hostel ht;
    fstream f;
    f.open("hostel.dat",ios::out|ios::in);
    while(f.read((char*)&ht,sizeof(ht))){
        if(strcmp(ht.retname(),hname) == 0){
            ht.inc_curr();
            int pos = -1 * sizeof(ht);
            f.seekp(pos,ios::cur);
            f.write((char*)&ht,sizeof(ht));
        }
    }
    f.close();
    cout << "..........................\n";
}
/* Function used to find a hostel from file and use
dec_curr() function on it */
void dec_hostel(char hname[]){
    Hostel ht;
    fstream f;
    f.open("hostel.dat",ios::out|ios::in);
    while(f.read((char*)&ht,sizeof(ht))){
        if(strcmp(ht.retname(),hname) == 0){
            ht.dec_curr();
            int pos = -1 * sizeof(ht);
            f.seekp(pos,ios::cur);
            f.write((char*)&ht,sizeof(ht));
        }
    }
    f.close();
    cout << "..........................\n";
}
/* Function to be called if a student wishes to
transfer rooms*/
void transfer_rooms(int roll){
    bool flag = false;
    int new_room;
    Student st;
    fstream f;
    f.open("student.dat",ios::out|ios::in);
    while(f.read((char*)&st,sizeof(st))){
        if(roll == st.retroll()){
            cout << "Enter the new room number: ";
            cin >> new_room;
            st.change_room(new_room);
            int pos = -1 * sizeof(st);
            f.seekp(pos,ios::cur);
            f.write((char*)&st,sizeof(st));
            flag = true;
        }
    }
    if(!flag){
        cout << "No student with given roll number\n";
    }
    f.close();
    cout << "..........................\n";
}
/* Function to be called if a student wishes to
transfer hostels*/
void transfer_hostel(int roll){
    char hname[15];
    bool flag = false;
    fstream f;
    Student st;
    f.open("student.dat",ios::in);
    while(f.read((char*)&st,sizeof(st))){
        if(roll == st.retroll()){
            flag = true;
        }
    }
    f.close();
    if(!flag){
        cout << "No student with given roll number\n";
        return;
    }
    flag = false;
    cout << "Enter new hostel name: ";
    cin.getline(hname,15);
    while(!find_hostel(hname)){
            cout << "Hostel not found, please try again:\n";
            cin.getline(hname,15);
    }
    f.open("student.dat",ios::out|ios::in);
    while(f.read((char*)&st,sizeof(st))){
        if(roll == st.retroll()){
            dec_hostel(st.rethname());
            inc_hostel(hname);
            st.change_hostel(hname);
            int room;
            cout << "Enter new room number: ";
            cin >> room;
            st.change_room(room);
            int pos = -1 * sizeof(st);
            f.seekp(pos,ios::cur);
            f.write((char*)&st,sizeof(st));
        }
    }
    f.close();
    cout << "..........................\n";
}
/* Function used to create Student object
and save it to file*/
void write_student(){
    Student st;
    st.create();
    ofstream out;
    out.open("student.dat", ios::app);
    out.write((char*)&st, sizeof(st));
    out.close();
}
/* Function used to create Hostel object
and save it to file*/
void write_hostel(){
    Hostel ht;
    ht.create();
    ofstream out;
    out.open("hostel.dat", ios::app);
    out.write((char*)&ht,sizeof(ht));
    out.close();
}
/* Prints all Student objects in file to output*/
void print_all_students(){
    Student st;
    ifstream in;
    in.open("student.dat");
    while(in.read((char*)&st,sizeof(st))){
        st.print();
        cout << "..........................\n";
    }
    in.close();
}
/* Prints all Hostel objects in file to output*/
void print_all_hostel(){
    Hostel ht;
    ifstream in;
    in.open("hostel.dat");
    while(in.read((char*)&ht,sizeof(ht))){
        ht.print();
        cout << "..........................\n";
    }
    in.close();
}
/* Finds and prints all students who live in given hostel*/
void find_print_students(char hostel_name[]){
    bool flag = false;
    Student st;
    ifstream in;
    in.open("student.dat");
    while(in.read((char*)&st,sizeof(st))){
        if(strcmp(st.rethname(),hostel_name) == 0){
            st.print();
            cout << "..........................\n";
            flag = true;
        }
    }
    in.close();
    if(!flag){
        cout << "No student or hostel doesn't exist\n";
    }
}
/* Finds and prints the student with
given roll number */
void find_print_student(int roll){
    bool flag = false;
    Student st;
    ifstream in;
    in.open("student.dat");
    while(in.read((char*)&st,sizeof(st))){
        if(st.retroll() == roll){
            st.print();
            cout << "..........................\n";
            flag = true;
        }
    }
    in.close();
    if(!flag){
        cout << "No student with given roll number\n";
    }
}
/* Finds and prints all students with given first name*/
void find_print_student(char first_name[]){
    bool flag = false;
    Student st;
    ifstream in;
    in.open("student.dat");
    while(in.read((char*)&st,sizeof(st))){
        if(strcmp(st.retfname(),first_name) == 0){
            st.print();
            cout << "..........................\n";
            flag = true;
        }
    }
    in.close();
    if(!flag){
        cout << "No student with given first name\n";
    }
}
/* Function used to search for a Hostel object and
returns true if that object exists in the file*/
bool find_hostel(char hostel_name[]){
    Hostel ht;
    ifstream in;
    in.open("hostel.dat");
    while(in.read((char*)&ht,sizeof(ht))){
        if(strcmp(ht.retname(),hostel_name) == 0){
            return true;
        }
    }
    in.close();
    return false;
}
/* Finds and prints the hostel with given name*/
void find_print_hostel(char hostel_name[]){
    bool flag = false;
    Hostel ht;
    ifstream in;
    in.open("hostel.dat");
    while(in.read((char*)&ht,sizeof(ht))){
        if(strcmp(ht.retname(),hostel_name) == 0){
            ht.print();
            cout << "..........................\n";
            flag = true;
        }
    }
    in.close();
    if(!flag){
        cout << "Hostel doesn't exist\n";
    }
}
/* Removes a student from file if it exists*/
void rem_student(int roll){
    bool flag = false;
    Student st;
    fstream f1,f2;
    f1.open("student.dat",ios::in|ios::out);
    f2.open("temp.dat",ios::out);
    while(f1.read((char*)&st,sizeof(st))){
        if(st.retroll() == roll){
            dec_hostel(st.rethname());
            flag = true;
        }
        else{
            f2.write((char*)&st,sizeof(st));
        }
    }
    f1.close();
    f2.close();
    remove("student.dat");
    rename("temp.dat","student.dat");
    if(!flag){
        cout << "Student with given roll number doesn't exist\n";
    }
    else{
        cout << "Student Removed\n";
    }
    cout << "..........................\n";
}
/* Removes a hostel from file if it exists
and has no students living in it currently*/
void rem_hostel(char hname[]){
    bool flag = false;
    Student st;
    Hostel ht;
    fstream f, f1,fp;
    fp.open("hostel.dat",ios::in);
    while(fp.read((char*)&ht,sizeof(ht))){
        if(strcmp(hname,ht.retname()) == 0){
            if(ht.retcurr() > 0){
                cout << "Student(s) still present in hostel\n";
                return;
            }
        }
    }
    f.open("hostel.dat",ios::in|ios::out);
    f1.open("temp.dat",ios::out);
    while(f.read((char*)&ht,sizeof(ht))){
        if(strcmp(hname,ht.retname()) == 0){
            flag = true;
        }
        else{
            f1.write((char*)&ht,sizeof(ht));
        }
    }
    f.close();
    f1.close();
    remove("hostel.dat");
    rename("temp.dat","hostel.dat");
    if(!flag){
        cout << "Given hostel doesn't exist\n";
    }
    else{
        cout << "Hostel Removed\n";
    }
    cout << "..........................\n";
}
/* Creates the menu of options to be displayed*/
void create_menu(){
    cout << "\n\t\t\tSelect an option";
    cout << "\n\t\t\t1) Create new student entry";
    cout << "\n\t\t\t2) Create new hostel entry";
    cout << "\n\t\t\t3) Print all student entries";
    cout << "\n\t\t\t4) Print all hostel entries";
    cout << "\n\t\t\t5) Print all student entries residing in a given hostel";
    cout << "\n\t\t\t6) Search for student entry with given roll number";
    cout << "\n\t\t\t7) Print all student entries with the same first name";
    cout << "\n\t\t\t8) Search for hostel entry with given name";
    cout << "\n\t\t\t9) Change the room of student";
    cout << "\n\t\t\t10) Change the hostel of student";
    cout << "\n\t\t\t11) Remove a student entry";
    cout << "\n\t\t\t12) Remove a hostel entry";
    cout << "\n\t\t\t13) Quit";
    cout << "\n\t\t\t Any other button to print this menu again";
    cout << "\n";
}
/* Checks if the hostel.dat file is empty or not created*/
bool isempty(){
    bool res;
    ifstream f("hostel.dat");
    res = f.is_open();
    if(f){
        f.seekg(0,ios::end);
        size_t size = f.tellg();
        if(size == 0){
            res = false;
        }
    }
    f.close();
    return (!res);
}
 
int main(){
    cout << "\n\t\t\tWelcome.....\n";
    if(isempty()){
        cout << "The hostel file is empty\n";
        cout << "Please enter hostel data...\n";
        write_hostel();
    }
    create_menu();
    int op;
    bool quit = false;
    while(!quit){
        cin >> op;
        switch(op){
            case 1: write_student(); break;
            case 2: write_hostel(); break;
            case 3: print_all_students(); break;
            case 4: print_all_hostel(); break;
            case 5: {
                cout << "Enter name of hostel: ";
                char hname[15];
                cin.getline(hname,15);
                find_print_students(hname);
                break;
            }
            case 6:{
                int roll;
                cout << "Enter roll number: ";
                cin >> roll;
                find_print_student(roll);
                break;
            }
            case 7:{
                char fname[10];
                cout << "Enter first name: ";
                cin.getline(fname,10);
                find_print_student(fname);
                break;
            }
            case 8:{
                char hname[15];
                cout << "Enter name of hostel: ";
                cin.getline(hname,15);
                find_print_hostel(hname);
                break;
            }
            case 9:{
                int roll;
                cout << "Enter roll number of student: ";
                cin >> roll;
                transfer_rooms(roll);
                break;
            }
            case 10:{
                int roll;
                cout << "Enter roll number of student: ";
                cin >> roll;
                transfer_hostel(roll);
                break;
            }
            case 11:{
                int roll;
                cout << "Enter roll number of student: ";
                cin >> roll;
                rem_student(roll);
                break;
            }
            case 12:{
                char hname[15];
                cout << "Enter name of hostel: ";
                cin.getline(hname,15);
                rem_hostel(hname);
                break;
            }
            case 13:{
                quit = true;
                break;
            }
            default: create_menu();
        }
    }
}
