#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

// Include the header of the Sudoku solver
// #include "sudoku.h" // Uncomment and adjust based on actual header file

// Mock Sudoku solver function
int solveSudoku(int grid[9][9]) {
    // Implement the function or link to the actual solver
    return 1; // Return 1 if solved, 0 otherwise
}

void test_solvable_puzzle(void) {
    int grid[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    CU_ASSERT(solveSudoku(grid) == 1);
}

void test_unsolvable_puzzle(void) {
    int grid[9][9] = {
        {5, 5, 0, 0, 7, 0, 0, 0, 0}, // Invalid row with duplicate '5'
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    CU_ASSERT(solveSudoku(grid) == 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("SudokuSolverTestSuite", 0, 0);

    CU_add_test(suite, "Test Solvable Puzzle", test_solvable_puzzle);
    CU_add_test(suite, "Test Unsolvable Puzzle", test_unsolvable_puzzle);

    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}
