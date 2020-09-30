#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <stdlib.h>
using namespace std;

const int n_subject = 2;
const int n_semister = 1;
int i,j,k;


class Subject{
public:
    string course_title;
    string course_teacher;
    float course_code;
    float credit;
    float grade;
    Subject(){
        course_title="none";
        course_teacher="none";
        course_code=0;
        credit=0;
        grade=0;
    }
    void set_subject_info(string course_title,string course_teacher,float course_code,float credit){
        this->course_title = course_title;
        this->course_code = course_code;
        this->course_teacher = course_teacher;
        this->credit = credit;
    }
    void show_subject_info(){
        cout<<"\n\ncourse title is : "<<course_title;
        cout<<"\ncourse code is : "<<course_code;
        cout<<"\ncourse teacher is : "<<course_teacher;
        cout<<"\ncourse credit is : "<<credit;
    }

};


//abstract class
class Semister{
public:
    float semister_number;
    virtual void set_semister(float semister_number) = 0;
};

class Semister_1_1:public Semister{
public:
    Subject subjects[n_subject];
    void set_semister(float semister_number){
        this->semister_number = semister_number;
    }
};






class Students{
private:
    string name;
    float merit_position;
public:
    string roll;
    float CGPA;
    Semister_1_1 semister;
    Students(){
        merit_position=0;
        roll="none";
        name="none";
    }
    void set_student_info(Semister_1_1& s,string name,string roll,float grade[]){
        semister = s;
        this->name = name;
        this->roll = roll;
        for(i=0;i<n_subject;i++){
            semister.subjects[i].grade = grade[i];
        }
        float passed_credit=0;
        float grand_total=0;
        for(i=0;i<n_subject;i++){
            if(semister.subjects[i].grade!=0){
                grand_total += (semister.subjects[i].grade*semister.subjects[i].credit);
                passed_credit += semister.subjects[i].credit;
            }
        }
        CGPA = grand_total/passed_credit;
    }
};



class Merit{
private:
    map <string,float> list_of_cgpa;
public:
    set <float> cgpa;
    int merit;
    float students_cgpa;
    void Activate_merit_list(vector <Students> s){
        for(i=0;i<s.size();i++){
            list_of_cgpa.insert(pair<string,float>(s[i].roll,s[i].CGPA));
            cgpa.insert(s[i].CGPA);
        }
    }
    float get_merit(string r){
        merit = cgpa.size() - distance(cgpa.begin(),cgpa.find(list_of_cgpa.at(r)));
        //merit = list_of_cgpa.at(r);
        return merit;
    }


};




int main(){
    float grd[n_subject];
    string course_title;
    string course_teacher;
    float course_code;
    float credit;
    string name;
    string roll;
    int n_student;


    //Initializing Subject Information
    Semister_1_1 semister_1_1;
    cout<<"Insert the subjects information of your semister.... \n\n\n";
    for(i=0;i<n_subject;i++){
        cout<<i+1<<"th Subject:\n";
        cout<<"Insert Course title:";
        cin>>course_title;
        cout<<"Insert Course code:";
        cin>>course_code;
        cout<<"Insert Course teacher:";
        cin>>course_teacher;
        cout<<"Insert Course credit:";
        cin>>credit;
        semister_1_1.subjects[i].set_subject_info(course_title,course_teacher,course_code,credit);
        cout<<"\n............................................\n";
    }
    system("cls");



//  Initializing Students
    cout<<"Insert the students information.... \n\n\n";
    cout<<"Insert the number of students: ";
    cin>>n_student;
    vector <Students> student(n_student);
    for(k=0;k<n_student;k++){
        cout<<k+1<<"th Student:\n";
        cout<<"Insert Name:";
        cin>>name;
        cout<<"Insert Roll:";
        cin>>roll;
        for(j=0;j<n_subject;j++){
            cout<<"Insert Grade in "<<semister_1_1.subjects[j].course_title<<" :";
            cin>>grd[j];
        }
        student[k].set_student_info(semister_1_1,name,roll,grd);
        cout<<"\n............................................\n";
    }
    system("cls");


//  Find merit

    Merit merit;
    merit.Activate_merit_list(student);
    while(true){
        cout<<"Insert the roll of student :";
        cin>>roll;
        cout<<"Merit: "<<merit.get_merit(roll);
        cout<<"\n\n";
    }

    return 0;
}

/*

math 2101 rafiqul_islam 3
physics 2102 tariq_rahman 3
5
asif 10 3 3
nirob 11 3 4
kaif 12 4 4
jabir 13 4 3
siyam 14 3 3

*/


