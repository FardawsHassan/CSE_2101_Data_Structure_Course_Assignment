#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <cstdlib>
#include <conio.h>
#include <sstream>

using namespace std;
int i,j,k;



//Object Oriented design.................

class Subject{
private:
    string course_teacher;
    float course_code;
    float credit;
    float grade;
    string course_title;
    void set_grade(float grade){
        this->grade = grade;
    }
    float get_grade(){
        return grade;
    }
    float get_credit(){
        return credit;
    }
    void set_subject_info(string course_title,string course_teacher,float course_code,float credit){
        this->course_title = course_title;
        this->course_code = course_code;
        this->course_teacher = course_teacher;
        this->credit = credit;
    }
public:
    Subject(){
        course_title="none";
        course_teacher="none";
        course_code=0;
        credit=0;
        grade=0;
    }
    string get_title(){
        return course_title;
    }
    void get_subject_info(){
        cout<<"\tCourse Title: "<<course_title;
        cout<<"\n\tCourse Code: "<<course_code;
        cout<<"\n\tCourse Teacher: "<<course_teacher;
        cout<<"\n\tCourse Credit: "<<credit;
    }

    friend class Semister;
};



class Semister{
private:
    vector<Subject> subjects;   //semister has-a subject (composition)
    void set_grade(int number_of_subjects,float grade){
        subjects[number_of_subjects].set_grade(grade);
    }
    float get_grade(int number_of_subjects){
        return subjects[number_of_subjects].get_grade();
    }
    float get_credit(int number_of_subjects){
        return subjects[number_of_subjects].get_credit();
    }
public:
    void set_semister(vector <Subject> sub){
        this->subjects = sub;
    }
    void set_subject_info(int number_of_subjects,string course_title,string course_teacher,int course_code,float credit){
        subjects[number_of_subjects].set_subject_info(course_title,course_teacher,course_code,credit);
    }
    int number_of_subjects(){
        return subjects.size();
    }
    string get_course_title(int subject_number){
        return subjects[subject_number].get_title();
    }
    void get_semister_info(){
        cout<<"Total Subjects: "<<subjects.size()<<"\n";
        cout<<"Subjects: \n";
        for(int s=0;s<subjects.size();s++){
            subjects[s].get_subject_info();
            cout<<"\n\n";
        }
    }
    friend class Students;
};



class Students{
private:
    vector<Semister> semister;  //students has-a semister (composition)
    string name;
    string roll;
    float CGPA;
    string get_name(){
        return name;
    }
    float get_cgpa(){
        return CGPA;
    }
public:
    void set_student_info(Semister& s,string name,string roll,float grade[]){
        this->name = name;
        this->roll = roll;
        this->semister.push_back(s);
        for(i=0;i<semister.back().number_of_subjects();i++){
            semister.back().set_grade(i,grade[i]);
        }
        float total_sgpa=0;
        for(k=0;k<semister.size();k++){
            float passed_credit=0;
            float grand_total=0;
            for(i=0;i<semister[k].number_of_subjects();i++){
                if(semister[k].get_grade(i)!=0){
                    grand_total += (semister[k].get_grade(i)*semister[k].get_credit(i));
                    passed_credit += semister[k].get_credit(i);
                }
            }
            total_sgpa += grand_total/passed_credit;
        }
        CGPA = total_sgpa/semister.size();
    }
    void add_new_semister(Semister& s,float grade[]){
        this->semister.push_back(s);
        float passed_credit=0;
        float grand_total=0;
        float sgpa=0;
        for(i=0;i<s.number_of_subjects();i++){
            semister.back().set_grade(i,grade[i]);
        }
        for(i=0;i<semister.back().number_of_subjects();i++){
            if(semister.back().get_grade(i)!=0){
                grand_total += (semister.back().get_grade(i)*semister.back().get_credit(i));
                passed_credit += semister.back().get_credit(i);
            }
        }
        sgpa = grand_total/passed_credit;
        CGPA = ((CGPA*(semister.size()-1))+ sgpa)/semister.size();
    }
    string get_roll(){
        return roll;
    }
    void get_SGPA(){
        for(k=0;k<semister.size();k++){
            float passed_credit=0;
            float grand_total=0;
            for(i=0;i<semister[k].number_of_subjects();i++){
                if(semister[k].get_grade(i)!=0){
                    grand_total += (semister[k].get_grade(i)*semister[k].get_credit(i));
                    passed_credit += semister[k].get_credit(i);
                }
            }
            cout<<"\tSGPA of "<<k+1<<"th semister: "<<grand_total/passed_credit<<"\n";
        }
    }
    friend class Informations_library;
};



class Informations_library{
private:
    map <string,int> id_from_roll;
    set <float> cgpa;
    vector <Students> students;
public:
    void Activate_Informations_library(vector<Students>& students){
        //must be reset when new semister or student will be added
        this->students = students;
        cgpa.clear();
        for(int i=0;i<students.size();i++){
            id_from_roll.insert(pair<string,int>(students[i].get_roll(),i));
            cgpa.insert(students[i].get_cgpa());
        }
    }
    //Merit Calculation
    float get_merit(string roll){
        int merit = cgpa.size() - distance(cgpa.begin(),cgpa.find(students[id_from_roll[roll]].get_cgpa()));
        return merit;
    }
    void get_student_info(string roll){
        cout<<"\tName: "<<students[id_from_roll[roll]].get_name()<<"\n";
        cout<<"\tRoll: "<<roll<<"\n";
        students[id_from_roll[roll]].get_SGPA();
        cout<<"\tCGPA: "<<students[id_from_roll[roll]].get_cgpa()<<"\n";
        cout<<"\tMerit Position: "<<get_merit(roll)<<"\n";
    }
};






//Utility Functions.............................

//Add students
void add_students(vector<Students>& stdnt){
    Students temp_student;
    stdnt.push_back(temp_student);
}
//set all subjects to semister
void add_subject_to_semister(vector<Semister>& smstr,int n_sem, int n_sub){
    vector<Subject> sub(n_sub);
    smstr[n_sem].set_semister(sub);
}
//set subjects information of a semister
void set_informations_to_subjects(vector<Semister>& smstr,int n_smstr){
    string course_title;
    string course_teacher;
    float course_code;
    float credit;
    cout<<"Insert the subjects information of your semister.... \n\n";
    for(j=0;j<smstr[n_smstr].number_of_subjects();j++){
        cout<<j+1<<"th Subject:\n";
        cout<<"Insert Course title:";
        cin>>course_title;
        cout<<"Insert Course code:";
        cin>>course_code;
        cout<<"Insert Course teacher:";
        cin>>course_teacher;
        cout<<"Insert Course credit:";
        cin>>credit;
        smstr[n_smstr].set_subject_info(j,course_title,course_teacher,course_code,credit);
        cout<<"\n............................................\n";
    }
}
//initialize subjects to semister
void add_semister(vector<Semister>& smstr,int number_of_semister){
    int number_of_subjects;
    Semister temp_semister;
    smstr.push_back(temp_semister);
    cout<<"Number of Courses :";
    cin>>number_of_subjects;
    add_subject_to_semister(smstr,number_of_semister,number_of_subjects);
    set_informations_to_subjects(smstr,number_of_semister);
    cout<<"\n\n";
}



int main(){
    float grd[20];
    string name;
    string roll;
    string number_of_semister;
    int number_of_students;
    int number_of_semisters;
    int number_of_subjects;





// Setting all Informations..................

    //initial semister
    cout<<"Insert the number of semister: ";
    cin>>number_of_semisters;
    vector <Semister> smstr;
    system("cls");

    //add and set semister information
    for(i=0;i<number_of_semisters;i++){
        cout<<"Insert the informations of semister "<<i+1<<": \n\n";
        add_semister(smstr,i);
    }
    system("cls");

    //initialize students
    cout<<"Insert the number of students: ";
    cin>>number_of_students;
    cout<<"\n\n";
    vector <Students> stdnt(number_of_students);

    //set students information
    for(int m=0;m<number_of_students;m++){
        cout<<m+1<<"th Student:\n\n";
        cout<<"Insert Name:";
        cin>>name;
        cout<<"Insert Roll:";
        cin>>roll;
        for(int semister_number=0;semister_number<smstr.size();semister_number++){
            cout<<semister_number+1<<"th semister: \n";
            for(int subject_number=0;subject_number<smstr[semister_number].number_of_subjects();subject_number++){
                cout<<"\tInsert Grade in "<<smstr[semister_number].get_course_title(subject_number)<<": ";
                cin>>grd[subject_number];
            }

            stdnt[m].set_student_info(smstr[semister_number],name,roll,grd);
        }
        cout<<"\n............................................\n";
    }
    system("cls");

    //Initializing Information_library
    Informations_library info_lib;
    info_lib.Activate_Informations_library(stdnt);






// Functionalities to use Informations...............

    //Functionalities
    string command="-start";
    cout<<"These are some available methods... type method name to use\n\n";
    cout<<"\t\t\t -merit \t -students_information \t -all_students_information \n\t\t -semister_information \t -all_semisters_information \t -add_student \t -add_semister\n\t\t\t\t\t\t\t -exit \n\n";
    while(command!="-exit"){
        system("cls");
        cout<<"These are some available methods... type method name to use\n\n";
        cout<<"\t\t\t -merit \t -students_information \t -all_students_information \n\t\t -semister_information \t -all_semisters_information \t -add_student \t -add_semister\n\t\t\t\t\t\t\t -exit \n\n";
        cout<<"\nMethod name: ";
        cin>>command;
        if(command=="-merit"){
            system("cls");
            cout<<"type -break to exit from merit method...\n";
            while(true){
                cout<<"Insert the roll of student :";
                cin>>roll;
                if(roll=="-break"){
                    break;
                }
                cout<<"Merit: "<<info_lib.get_merit(roll);
                cout<<"\n\n";
            }
        }else if(command=="-students_information"){
            system("cls");
            cout<<"type -break to exit from this method...\n";
            while(true){
                cout<<"Insert the roll of student :";
                cin>>roll;
                if(roll=="-break"){
                    break;
                }
                cout<<"Informations: \n";
                info_lib.get_student_info(roll);
                cout<<"\n\n";
            }
        }else if(command=="-all_students_information"){
            system("cls");
            cout<<"All students information: \n\n";
            for(int s=0;s<stdnt.size();s++){
                info_lib.get_student_info(stdnt[s].get_roll());
                cout<<"\n";
            }
            cout<<"Press any key to exit from this method...\n";
            getch();
        }else if(command=="-semister_information"){
           system("cls");
            cout<<"type -break to exit from this method...\n";
            while(true){
                cout<<"Insert semister number :";
                cin>>number_of_semister;
                if(number_of_semister=="-break"){
                    break;
                }
                else{
                    int n_s;
                    istringstream(number_of_semister)>>n_s;
                    cout<<"\nInformations: \n..............\n";
                    smstr[n_s-1].get_semister_info();
                    cout<<"\n\n";
                }
            }
        }else if(command=="-all_semisters_information"){
            system("cls");
            cout<<"All Semister Information:\n.......................... \n\n";
            for(int s=0;s<smstr.size();s++){
                cout<<"Semister no: "<<s+1<<"\n";
                smstr[s].get_semister_info();
                cout<<"\n";
            }
            cout<<"Press any key to exit from this method...\n";
            getch();
        }else if(command=="-add_student"){
            system("cls");
            add_students(stdnt);
            cout<<"Insert New Students Information:\n.......................... \n\n";
            cout<<"Insert Name:";
            cin>>name;
            cout<<"Insert Roll:";
            cin>>roll;
            for(int semister_number=0;semister_number<smstr.size();semister_number++){
                cout<<semister_number+1<<"th semister: \n";
                for(int subject_number=0;subject_number<smstr[semister_number].number_of_subjects();subject_number++){
                    cout<<"\tInsert Grade in "<<smstr[semister_number].get_course_title(subject_number)<<": ";
                    cin>>grd[subject_number];
                }
                stdnt.back().set_student_info(smstr[semister_number],name,roll,grd);
            }
            cout<<"\n\nStudents information is added successfully.\n\n";
            info_lib.Activate_Informations_library(stdnt);
            cout<<"Press any key to exit from this method...\n";
            getch();
        }else if(command=="-add_semister"){
            system("cls");
            cout<<"Insert New Semister Information:\n.......................... \n\n";
            int semister_number = smstr.size();
            add_semister(smstr,semister_number);
            for(int i=0;i<stdnt.size();i++){
                cout<<"Roll no: "<<stdnt[i].get_roll()<<"\n";
                for(int subject_number=0;subject_number<smstr.back().number_of_subjects();subject_number++){
                    cout<<"\tInsert Grade in "<<smstr[semister_number].get_course_title(subject_number)<<": ";
                    cin>>grd[subject_number];
                }
                stdnt[i].add_new_semister(smstr.back(),grd);
            }
            cout<<"\n\nStudents information is added successfully.\n\n";
            info_lib.Activate_Informations_library(stdnt);
            cout<<"Press any key to exit from this method...\n";
            getch();
        }
    }



    return 0;
}
