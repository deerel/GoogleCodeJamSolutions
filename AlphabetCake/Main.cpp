#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stack>


std::vector<char> str_to_vec_of_char(const std::string& str) {
	std::vector<char> result;
	for (auto c : str) {
		result.push_back(c);
	}
	return result;
}

void fill_back_vec(std::vector<char>& vec, int index, char c) {
	while (index >= 0 && vec.at(index) == '?') {
		vec.at(index) = c;
		--index;
	}
		
}

void flood_fill_horizontal(std::vector<std::vector<char>>& vec) {
	char current_char = '?';
	bool fill_back = false;
	bool copy_from_below = false;
	std::stack<int> copy_to_indices;
	for (auto i = 0; i < vec.size(); ++i) {
		for (auto j = 0; j < vec.at(i).size(); ++j) {
			if (vec.at(i).at(j) != '?') { // Found a character
				current_char = vec.at(i).at(j);
				if (fill_back) {
					fill_back_vec(vec.at(i), j - 1, current_char);
					fill_back = false;
				}
			}
			else if (current_char == '?') { // ? before any character
				fill_back = true;
			}
			else { // Set to current character
				vec.at(i).at(j) = current_char;
			}
		}

		if (fill_back == true) { // Whole line is empty
			if (i > 0 && copy_from_below == false) { // Copy from above
				vec.at(i) = vec.at(i - 1);
				
				fill_back = false;
			}
			else { // Need to fill below and copy up
				copy_from_below = true;
				copy_to_indices.push(i);
			}
		}

		if (copy_from_below == true && current_char != '?' && !copy_to_indices.empty() && copy_to_indices.top() != i) {
			while (!copy_to_indices.empty()) {
				vec.at(copy_to_indices.top()) = vec.at(i);
				copy_to_indices.pop();
			}
			copy_from_below = false;
		}
		current_char = '?';

	}
}

void output(std::vector<std::vector<char>> vec, std::ofstream& output_file) {
	for (auto charvec : vec) {
		for (auto c : charvec) {
			output_file << c;
		}
		output_file << std::endl;
	}
}

void print_to_screen_vector(std::vector<std::vector<char>> vec) {
	for (auto charvec : vec) {
		for (auto c : charvec) {
			std::cout << c;
		}
		std::cout << std::endl;
	}
}

int main() {

	std::ifstream input_file;
	//input_file.open("A-small-practice.in");
	input_file.open("A-large-practice.in");

	std::ofstream output_file;
	output_file.open("output.txt");

	if (!input_file) {
		std::cerr << "Unable to open file";
		exit(1);
	}

	if (!output_file) {
		std::cerr << "Unable to open file";
		exit(1);
	}

	int cases, rows, cols;
	input_file >> cases;

	for (auto i = 0; i < cases; ++i) {

		input_file >> rows >> cols;
		std::vector<std::vector<char>> cake;
		std::string line;
		for (auto j = 0; j < rows; ++j) {
			input_file >> line;
			cake.push_back(str_to_vec_of_char(line));
		}

		//std::cout << "Case #" << i + 1 << ":" << std::endl;
		//print_to_screen_vector(cake);
		// Do the magic trick..
		flood_fill_horizontal(cake);

		std::cout << "Case #" << i+1 << ":" << std::endl;
		output_file << "Case #" << i+1 << ":" << std::endl;
		for (auto charvec : cake) {
			for (auto c : charvec) {
				std::cout << c;
				output_file << c;
			}
			std::cout << std::endl;
			output_file << std::endl;
		}

	}


	int stop;
	std::cin >> stop;
}