#ifndef FILEOPS_H
#define FILEOPS_H

#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Person.h"
#include "Skill.h"


int skillToInt(std::string skill){
	int num;

	if(skill == "IR")
		num = 1;
	else if(skill == "DB")
		num = 2;
	else if(skill == "AI")
		num = 3;
	else if(skill == "DM")
		num = 4;
	else
		num = 0;

	return num;
}

std::vector<Person> loadPeople(){
	std::vector<Person> people;
	std::ifstream inputFile("people.txt", std::ios::in);

	std::cout << "Checking file..." << std::endl;

	if(!inputFile){
		std::cerr << "ERROR: File not found." << std::endl;
		exit(1);
	}

	std::cout << "Loading file..." << std::endl;

	std::string line;

	while(!inputFile.eof()){
		std::string name;
		std::vector<Skill> skills;
		unsigned int lineIndex = 0;
		getline(inputFile, line);

		std::cout << "Getting name..." << std::endl;
		//get name
		for(unsigned int i = 0; i < line.size(); i++){
			if(line.at(i) == ';'){
				name = line.substr(0, i);
				lineIndex = i + 1;
				break;
			}
		}

		std::cout << "Getting skills..." << std::endl;
		//get skills
		for(unsigned int i = lineIndex; i < line.size(); i++){
			//add skill at ';'
			if(line.at(i) == ';'){
				skills.push_back(Skill(line.substr(lineIndex, i - lineIndex)));
				lineIndex = i + 1;
			}
				//add last skill on line
			if(i == line.size() - 1){
				skills.push_back(Skill(line.substr(lineIndex, i - lineIndex + 1)));
			}
		}

		std::cout << "Adding person..." << std::endl;

		people.push_back(Person(name, skills));
	}

	std::cout << "Files loaded" << std::endl;

	return people;
}

#endif
