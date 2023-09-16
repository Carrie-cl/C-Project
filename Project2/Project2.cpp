// Project Two
// Carol Lance

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Course {
	string courseNum;
	string courseName;
	vector<string> prerex;
};

vector<string> tokenize(string line, string delim = "") {
	char* cLine = _strdup(line.c_str());
	vector<string> tokens;
	char* token = nullptr, * nextToken = nullptr;
	token = strtok_s(cLine, delim.c_str(), &nextToken);
	while (token != nullptr) {
		// Create a string object from each token (char *) that had been returned by the strtok function
		tokens.push_back(string(token)); // Put the token (string) at the end of the vector

		// Call strtok_s to get the next token
		token = strtok_s(nullptr, delim.c_str(), &nextToken);
	}

	return tokens;
	
}

vector<Course> loadDataStructure() {

	ifstream file("ABCU_Advising_Program_Input.txt");  // read file

	vector<Course> courses;

	string line;
		
	while (getline(file, line)) {
		Course course;		
		vector<string> courseTokens = tokenize(line, ",");			// Split each line into tokens
		course.courseNum = courseTokens[0];				// First token of each line goes to courseNum
		course.courseName = courseTokens[1];			// Second token of each line goes to courseName

		for (int i = 2; i < courseTokens.size(); i++) { // If there are 3+ values, store prerequisites until end of line
			course.prerex.push_back(courseTokens[i]);
		}

		courses.push_back(course);		
	}
	

	return courses;
	
}

void printCourses(Course course) {
	

	string courseNum = course.courseNum;
	string courseName = course.courseName;
	vector<string> prerex = course.prerex;
	cout << courseNum << " " << courseName << " " << "prerequisites: "; // print course number, name, and prerequisites

	for (int i = 0; i < prerex.size(); i++) {
		cout << prerex[i] << " ";				// list of prerequisites if any
	}
	cout << endl;
}

void printCourseList(vector<Course> courses) {  // list of all course names only
	vector<string> coursesNames;
	for (int i = 0; i < courses.size(); i++) {
		coursesNames.push_back(courses[i].courseName);
	}
	std::sort(coursesNames.begin(), coursesNames.end());

	for (int i = 0; i < coursesNames.size(); i++) {
		cout << coursesNames[i] << endl;
	}

	// coursesNames will be sorted names of courses

}

void searchCourse(vector<Course> courses){ 
	
	string userEntry;

	cout << "What course would you like to know about?";
	cin >> userEntry;
	transform(userEntry.begin(), userEntry.end(), userEntry.begin(), ::toupper); // allows user to enter case insensitive course name

	for (int i = 0; i < courses.size(); i++) {   // search for course number entered
		if (courses[i].courseNum == userEntry) {
			printCourses(courses[i]);	// if found, display course number, name, and prerequisites
			break;
		}
		else if (i == courses.size() - 1) {			// not found
			cout << "That course was not located in this degree program." << endl; 
		}
	
	
	}
}

void printMenu() {
	cout << "1. Load Data Structure\n" << "2. Print Course List\n" << "3. Print Course\n" << "4. Exit\n";
}

int main(int argc, char* argv[]) {

	vector<Course> courses;
	int userInput = 0;	
	cout << "Select an option: \n";
	printMenu();
	cin >> userInput;

	while (userInput != 4) {
		
		switch (userInput) {
		case 1: {			// do this first
			courses = loadDataStructure();
			break;
		}

		case 2: printCourseList(courses);
			break;

		case 3: searchCourse(courses);
			break;

		case 4: cout << "Goodbye"; 
			break;

		default: cout << "Invalid option.\n";
			break;

	
		}
		cout << "Select an option: \n";
		printMenu();
		cin >> userInput;
	}
	

}