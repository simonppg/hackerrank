#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Person {
    protected:
        string name;
        int age;
    public:
        static int ids[2];
        virtual void getdata() {
            cin >> name >> age;
        }
        virtual void putdata() {
            cout << name << age;
        }
};

int Person::ids[] = {};

class Professor : public Person {
    private:
        int publications;
        int cur_id;
    public:
        Professor() {
            ids[0]++;
            cur_id = Person::ids[0];
        }
        void getdata() {
            cin >> name;
            cin >> age;
            cin >> publications;
        }
        void putdata() {
            cout << name << " " << age << " " << publications << " " << cur_id << endl;
        }
};

class Student : public Person {
    private:
        int marks[6];
        int cur_id;
    public:
        Student() {
            ids[1]++;
            cur_id = Person::ids[1];
        }
        void getdata() {
            cin >> name >> age;
            for(int i = 0; i < 6; i++) {
                cin >> marks[i];
            }
        }
        void putdata() {
            int sum = 0;
            cout << name << " " << age << " ";
            for(int i = 0; i < 6; i++) {
                sum += marks[i];
            }
            cout << sum << " " << cur_id << endl;
        }
};


int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}

