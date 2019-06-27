#include "SudokuClass.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <complex>
#include <memory>
#include <algorithm>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

using namespace std;

int main()
{
	read_and_solve_file_sudoku();
	//test_possibilities();
	//make_a_sudoku_and_print();
	return 0;
}