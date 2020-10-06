#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <stdlib.h>

using namespace std;
int i,j,k;



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
    void show_subject_info(){
        cout<<"\n\ncourse title is : "<<course_title;
        cout<<"\ncourse code is : "<<course_code;
        cout<<"\ncourse teacher is : "<<course_teacher;
        cout<<"\ncourse credit is : "<<credit;
    }

    friend class Semister;
};



class Semister{
private:
    vector<Subject> subjects;
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
    friend class Students;
};



class Students{
private:
    string name;
    float merit_position;
    string roll;
    float CGPA;
    vector<Semister> semister;
    string get_roll(){
        return roll;
    }
    float get_cgpa(){
        return CGPA;
    }
public:
    Students(){
        merit_position=0;
        roll="none";
        name="none";
    }
    void set_student_info(Semister& s,string name,string roll,float grade[]){
        this->semister.push_back(s);
        this->name = name;
        this->roll = roll;
        for(i=0;i<semister.back().number_of_subjects();i++){
            semister.back().set_grade(i,grade[i]);
        }
        float passed_credit=0;
        float grand_total=0;
        for(k=0;k<semister.size();k++){
            for(i=0;i<semister[k].number_of_subjects();i++){
                if(semister[k].get_grade(i)!=0){
                    grand_total += (semister[k].get_grade(i)*semister[k].get_credit(i));
                    passed_credit += semister[k].get_credit(i);
                }
            }
        }
        CGPA = grand_total/passed_credit;
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
            cout<<"SGPA of "<<k+1<<"th semister: "<<grand_total/passed_credit<<"\n";
        }
    }
    friend class Merit;
};



class Merit{
private:
    map <string,float> list_of_cgpa;
    set <float> cgpa;
    float students_cgpa;
public:
    void Activate_merit_list(vector<Students> students){
        for(i=0;i<students.size();i++){
            list_of_cgpa.insert(pair<string,float>(students[i].get_roll(),students[i].get_cgpa()));
            cgpa.insert(students[i].get_cgpa());
        }
    }
    float get_merit(string roll){
        int merit = cgpa.size() - distance(cgpa.begin(),cgpa.find(list_of_cgpa.at(roll)));
        return merit;
    }
};







//initialize subjects to semister
void add_semister(vector<Semister>& smstr){
    Semister temp_semister;
    smstr.push_back(temp_semister);
}
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



int main(){
    float grd[20];
    string name;
    string roll;
    int n_student;
    int number_of_students;



    int number_of_semisters;
    int number_of_subjects;

    //initial semister
    cout<<"Insert the number of semister: ";
    cin>>number_of_semisters;
    vector <Semister> smstr;
    system("cls");

    //set semister information
    for(i=0;i<number_of_semisters;i++){
        add_semister(smstr);
        cout<<"Insert the informations of semister "<<i+1<<": \n\n";
        cout<<"Number of Courses :";
        cin>>number_of_subjects;
        add_subject_to_semister(smstr,i,number_of_subjects);
        set_informations_to_subjects(smstr,i);
        cout<<"\n\n";
    }
    system("cls");


    //initial semister
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



//  Find merit
    Merit merit;
    merit.Activate_merit_list(stdnt);
    while(true){
        cout<<"Insert the roll of student :";
        cin>>roll;
        cout<<"Merit: "<<merit.get_merit(roll);
        cout<<"\n\n";
    }

    return 0;
}
