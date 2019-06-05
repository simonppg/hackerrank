#include <iostream>
#include <sstream>

using namespace std;

class Student {
	private:
		int age;
		string first_name;
		string last_name;
		int standard;
	public:
		void set_age(int age);
		void set_standard(int std);
		void set_first_name(string str);
		void set_last_name(string str);
		int get_age();
		int get_standard();
		string get_first_name();
		string get_last_name();
		string to_string();
};

void Student::set_age(int age) {
	this->age = age;
}

void Student::set_standard(int std) {
	this->standard = std;
}

void Student::set_first_name(string first_name) {
	this->first_name = first_name;
}

void Student::set_last_name(string last_name) {
	this->last_name = last_name;
}

int Student::get_age() {
	return this->age;
}

int Student::get_standard() {
	return this->standard;
}

string Student::get_first_name() {
	return this->first_name;
}

string Student::get_last_name() {
	return this->last_name;
}

string Student::to_string() {
	return ""+std::to_string(this->age) +
		"," + this->first_name +
		"," + this->last_name +
		"," + std::to_string(this->standard);
}

/*
   Enter code for class Student here.
   Read statement for specification.
   */

int main() {
	int age, standard;
	string first_name, last_name;

	cin >> age >> first_name >> last_name >> standard;

	Student st;
	st.set_age(age);
	st.set_standard(standard);
	st.set_first_name(first_name);
	st.set_last_name(last_name);

	cout << st.get_age() << "\n";
	cout << st.get_last_name() << ", " << st.get_first_name() << "\n";
	cout << st.get_standard() << "\n";
	cout << "\n";
	cout << st.to_string();

	return 0;
}
