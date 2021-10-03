#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

#include "../includes/constants.h"
#include "../includes/utilities.h"
using namespace std;

//if you are debugging the file must be in the project parent directory
std::string DoubleToString(double Number) {
	std::ostringstream ss;
	ss << Number;
	return ss.str();
}

//if myString does not contain a string rep of number returns 0
//if int not large enough has undefined behaviour, 
//this is a very fragile function
//ex. string a="3";
//    int i = stringToInt(a.c_str()); //i contains 3
//    a="s";
//    i = stringToInt(a.c_str()); //i receives 0
int stringToInt(const char *myString) {
	return atoi(myString);
}

//if myString does not contain a string rep of number returns 0
//this is a very fragile function
//ex. string b="4.5";
//    double d = stringToDouble(b.c_str()); //d receives 4.5
double stringToDouble(const char *myString) {
	return atof(myString);
}

/***
 * Clears allStudentData, Opens file, For each line; parses name, midterm1,midterm2 and an
 * optional finalgrade (if present in file)from that line. Puts this info into a studentData struct,
 * adds this struct to allstudentData vector.
 * NOTE:
 * Ignore empty lines
 * Non empty lines will contain 4 or 5 values to be parsed.
 * the default param separator_char is defined in the header file declaration of readFile ONLY, it is not in the readFile definition.
 * @param file - where student data is stored
 * @param allstudentData - a vector that holds the student data info after it has been read from file
 * @param separator_char - the character that separates each bit of data in a line of student data
 * @return COULD_NOT_OPEN_FILE
 *         SUCCESS
 */
int readFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char){
	std::string line;
	std::string token;
	stringstream ss;

	KP::studentData data;
	allstudentData.clear();
	ifstream myInputFile;
	myInputFile.open(file.c_str(), ios::in);

	if (myInputFile.is_open()) {
		std::string line;
		while(getline(myInputFile, line)){
			ss.clear();
			ss.str(line);

			data.clear();

			getline(ss, data.name, separator_char);
			getline(ss, token, separator_char);
			data.midterm1 = stringToDouble(token.c_str());
			getline(ss, token, separator_char);
			data.midterm2 = stringToDouble(token.c_str());
			if(getline(ss, token, separator_char)) {
				getline(ss, token, separator_char);
				data.finalgrade = stringToDouble(token.c_str());
			}

			allstudentData.push_back(data);

	}
		myInputFile.close();
		return KP::SUCCESS;
	}
	return KP::COULD_NOT_OPEN_FILE;

}

/***
 * Iterates over all students in vector, and averages midterm1 and midterm2 to get the finalgrade
 * @param allstudentData
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int calculateFinalGrade(std::vector<KP::studentData> &allstudentData){
	if (allstudentData.empty()){
			return KP::VECTOR_CONTAINS_NO_STUDENTS;
		}
	std::vector<KP::studentData>::iterator student = allstudentData.begin();
	for (student = allstudentData.begin(); student != allstudentData.end(); student++) {
		(*student).finalgrade = ((*student).midterm1 + (*student).midterm2)/2.0;
	}
	return KP::SUCCESS;
}

/***
 * Opens file, serializes data from allstudentData to file, closes file
 * the default param seperator_char is defined in the header file ONLY
 * @param file - where student data is stored
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param separator_char - the character that separates each bit of data in a line of student data
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         COULD_NOT_OPEN_FILE
 *         SUCCESS
 */
int writeFile(std::string &file, std::vector<KP::studentData> &allstudentData, char separator_char){

	if (allstudentData.empty()){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;
	}

	ofstream myOutputFile;
	myOutputFile.open(file.c_str(), ios::out);

	if(!myOutputFile.is_open()){
			return KP::COULD_NOT_OPEN_FILE;
		}

	myOutputFile.clear();
	string data = "";
	for (KP::studentData student : allstudentData) {
		data += student.name + separator_char + DoubleToString(student.midterm1) + separator_char + DoubleToString(student.midterm2);

		if(student.finalgrade != -1){
			data += separator_char +  DoubleToString(student.finalgrade) + "\n";
		}
	}
	myOutputFile << data;
	myOutputFile.close();
	return KP::SUCCESS;

}

bool compareName(KP::studentData const& allstudentData1, KP::studentData const& allstudentData2) {
	string person1 = allstudentData1.name;
	string person2 = allstudentData2.name;
	return person1 < person2;

}

bool compareFinal(KP::studentData const& allstudentData1, KP::studentData const& allstudentData2){
	double final1 = allstudentData1.finalgrade;
	double final2 = allstudentData2.finalgrade;
	return final1 > final2;
}

//sorts studentdata based on SORT_TYPE
/***
 *
 * @param allstudentData - a vector that holds student data info that will be written to file
 * @param st - how to sort the vector
 * @return VECTOR_CONTAINS_NO_STUDENTS
 *         SUCCESS
 */
int sortStudentData(std::vector<KP::studentData> &allstudentData,KP::SORT_TYPE st){

	if (allstudentData.empty()){
		return KP::VECTOR_CONTAINS_NO_STUDENTS;
	}
	switch(st){
		case KP::NAME:
			std::sort(allstudentData.begin(), allstudentData.end(), compareName);
			break;

		case KP::FINAL_GRADE:
			std::sort(allstudentData.begin(), allstudentData.end(), compareFinal);
			break;
	}
}























