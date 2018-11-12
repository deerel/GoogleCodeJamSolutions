#include <iostream>
#include <algorithm>
#include <fstream>

#define DEBUG 1

/*
Bathroom Stalls

Solution:
(Visualized as a binary tree)
1. Find the depth in which the last person will be placed.
2. Calculate the size of large and small spaces with available stalls.
3. Calculate the number of large spaces.
4. Determine whether the last person will have a large or small space.
5. Calculate the left and right space.
*/

// Returns floored log2 of x, for 64 bit unsigned integers
unsigned long long log2_64(unsigned long long x) {
	unsigned long long result = 0;
	while (x > 1) {
		x = x >> 1;
		++result;
	}
	return result;
}

int main() {

	std::ifstream input_file;
	input_file.open("C-large-practice.in");
	//input_file.open("C-small-practice-2.in");
	//input_file.open("C-small-practice-1.in");

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

	int test_cases;
	int case_num = 1;

	input_file >> test_cases;

	while (case_num <= test_cases) {

		unsigned long long stalls_count = 0;
		unsigned long long people = 0;

		// Read text case data from file.
		input_file >> stalls_count >> people;

		// (1.)
		// Number of levels in the imaginary binary tree.
		const unsigned long long levels = (unsigned long long)log2_64(people);

		// (2.)
		// The number of sections with empty stalls (the breadth of the tree at the current level).
		const unsigned long long sections = (unsigned long long)1 << levels;
		// Number of occupied stalls up to current level.
		const unsigned long long occupied = sections - 1;
		// The total number of available stalls.
		const unsigned long long available = stalls_count - occupied;
		// The size of the small available spaces.
		const unsigned long long small_size = (unsigned long long)(available / sections);
		// The size of the large available spaces.
		const unsigned long long large_size = small_size + 1;

		// (3.)
		// The number of large spaces.
		const unsigned long long number_of_large = available - (small_size * sections);

		// (4.) / (5.)
		// Decrease the number of people with the number of people already in a stall.
		people -= occupied;

		unsigned long long small_space;
		unsigned long long large_space;

		// If the remaining number of people are larger than the number of large spaces
		// the last person picks a small space, otherwise a large space.
		if (people > number_of_large) {
			small_space = (unsigned long long)((small_size - 1) / 2);
			large_space = (unsigned long long)(small_size / 2);
		}
		else {
			small_space = (unsigned long long)((large_size - 1) / 2);
			large_space = (unsigned long long)(large_size / 2);
		}

		// Print to screen and write to file.
		output_file << "Case #" << case_num << ": " << large_space << " " << small_space << std::endl;


		#if DEBUG == 1
			std::cout << "Case #" << case_num << ": " << large_space << " " << small_space << std::endl;
		#endif // DEBUG

		
		// Next case
		++case_num;

	}


	input_file.close();
	std::cin.get();
}