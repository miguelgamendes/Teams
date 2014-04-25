#ifndef FILEOPS_H
#define FILEOPS_H

#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "Person.h"

std::vector<Person> loadPeople(){
	std::ifstream inputFile("people.txt", std::ios::in);

	if(!inputFile){
		std::cerr << "ERROR: File not found." << std::endl;
		exit(1);
	}

	std::vector<Person> people;
	std::string line;

	while(!inputFile.eof()){
		std::string name;
		std::vector<int> skills;
		int index = 0;
		line = getline(inputFile, line);

		//get name
		for(unsigned int i = 0; i < line.size(); i++){
			if(line[i] == ";"){
				index = i - 1;
				name = line.substr(0, index);
				index = i + 1;
			}
		}

		//get skills
		do{
			for(unsigned int i = index; i < line.size(); i++){
				//add skill at ';'
				if(line[i] == ";"){
					skills.push_back(skillToInt(line.substr(index, i - index)));
					index = i + 1;
				}

				//add last skill on line
				if(i == line.size() - 1){
					skills.push_back(skillToInt(line.substr(index, i - index + 1)));
				}
			}
		}while(index < line.size() - 1);

		people.push_back(Person(name, skills));
	}

	return people;
}

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

#endif
