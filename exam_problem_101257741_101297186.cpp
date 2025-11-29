/**
 * @file exam_problem.cpp
 * @author Kyra Fingas
 * @brief main.cpp file for Assignment 3 Part 2 of SYSC4001
 * 
 */

#include"exam_problem_101257741_101297186.hpp"

exam current_exam;   //The current exam
std::vector<char*> exam_list; //The list of exam file names
int next_exam_number; //the index of the next exam file name

std::vector<rubric_line> rubric;

std::vector<ta> tas;

std::tuple<std::string> run_simulation() {
    while(next_exam_number<exam_list.size()){
        for(ta current_ta : tas){
            for(rubric_line linez : rubric){
                bool correct = rand() < 0.5;
                if(correct){
                    correct
                }
            }
        }
    }
}

void load_exam(){
    //Open the exam file
    char* exam_file_name = exam_list[next_exam_number];
    std::ifstream exam_file;
    exam_file.open(exam_file_name);

    //Ensure that the file actually opens
    if (!exam_file.is_open()) {
        std::cerr << "Error: Unable to open file: " << exam_file_name << std::endl;
        return;
    }

    //Parse the entire exam input file and populate a vector of exams.
    //To do so, the add_exam() helper function is used (see include file).
    std::string line;
    while(std::getline(exam_file, line)) {
        auto input_tokens = split_delim(line, ", ");
        auto new_exam = add_exam(input_tokens, rubric.size());
        current_exam = new_exam;
    }
    exam_file.close();   
    next_exam_number++;
}

//deals with opening and reading file and writing to the execution file
int main(int argc, char** argv) {

    //Get the input file from the user
    if(argc != 21) {
        std::cout << "ERROR!\nExpected 3 argument, received " << argc - 1 << std::endl;
        std::cout << "To run the program, do: ./exam_problem <your_exam_file.txt> <your_rubric_file.txt> <your_ta_file.txt>" << std::endl;
        return -1;
    }

    //open the rubric file
    auto rubric_file_name = argv[1];
    std::ifstream rubric_file;
    rubric_file.open(rubric_file_name);

    //Parse the entire rubric input file and populate a vector of rubric lines.
    //To do so, the add_rubric_line() helper function is used (see include file).
    std::string line;
    while(std::getline(rubric_file, line)) {
        auto input_tokens = split_delim(line, ", ");
        auto new_rubric_line = add_rubric_line(input_tokens);
        rubric.push_back(new_rubric_line);
    }
    rubric_file.close();

    //Open the TA file
    auto ta_file_name = argv[2];
    std::ifstream ta_file;
    ta_file.open(ta_file_name);

    //Parse the ta input file to get # of tas
    //To do so, the add_tas() helper function is used (see include file).
    while(std::getline(ta_file, line)) {
        auto input_tokens = split_delim(line, ", ");
        auto new_tas = add_tas(input_tokens);
        tas = new_tas;
    }
    ta_file.close();

    for(int i = 3; i<21; i++){
        exam_list.push_back(argv[i]);
    }

    load_exam();

    //With the list of processes, run the simulation
    auto [exec] = run_simulation();

    //write_output(exec, "execution.txt");

    return 0;
}