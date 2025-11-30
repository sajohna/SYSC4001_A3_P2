/**
 * @file exam_problem.hpp
 * @author Kyra Fingas
 * @brief main.hpp file for Assignment 3 Part 2 of SYSC4001
 * 
 */

#ifndef INTERRUPTS_HPP_
#define INTERRUPTS_HPP_

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<tuple>
#include<random>
#include<utility>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include <chrono>
#include <thread>

//An enumeration of actions to make assignment easier
enum action {
    READ,
    WRITE,
    ETC,
};

struct exam{
    int                 student_id;
    std::vector<bool>   questions_marked;
};

struct rubric_line{
    int             exercise;
    char            text;
};

struct ta{
    int             id;
    action          current_action;
    int             rubric_line;
};

std::vector<std::string> split_delim(std::string input, std::string delim) {
    std::vector<std::string> tokens;
    std::size_t pos = 0;
    std::string token;
    while ((pos = input.find(delim)) != std::string::npos) {
        token = input.substr(0, pos);
        tokens.push_back(token);
        input.erase(0, pos + delim.length());
    }
    tokens.push_back(input);

    return tokens;
}

exam add_exam(std::vector<std::string> tokens, int num_questions) {
    exam examz;
    examz.student_id = std::stoi(tokens[0]);
    for(int i = 0; i<num_questions; i++){
        examz.questions_marked[i] = false;
    }

    return examz;
}

rubric_line add_rubric_line(std::vector<std::string> tokens) {
    rubric_line linez;
    linez.exercise = std::stoi(tokens[0]);
    linez.text = std::stoi(tokens[1]);
}

std::vector<ta> add_tas(std::vector<std::string> tokens){
    std::vector<ta> list_tas;
    int ta_num = std::stoi(tokens[0]);
    for(int i = 0; i < ta_num; i++){
        ta new_ta;
        new_ta.id = i;
        new_ta.current_action = READ;
        new_ta.rubric_line = 0;
        list_tas.push_back(new_ta);
    }
    return list_tas;
}

void write_output(std::string execution, const char* filename) {
    std::ofstream output_file(filename);

    if (output_file.is_open()) {
        output_file << execution;
        output_file.close();  // Close the file when done
        std::cout << "File content overwritten successfully." << std::endl;
    } else {
        std::cerr << "Error opening file!" << std::endl;
    }

    std::cout << "Output generated in " << filename << ".txt" << std::endl;
}

#endif