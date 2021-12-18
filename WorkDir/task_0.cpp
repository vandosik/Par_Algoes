#include <iostream>
#include "omp.h" // no need now

using namespace std;

int main(int argc, char** argv)
{
    unsigned w_num = 0;


    if (argc < 2)
    {
        cout << "No argument passed" << endl;
        return 1; // Exit with failure
    }

    char*       string = argv[1];
    char        new_symb, prev_symb;
    unsigned    i = 1;

    prev_symb = new_symb = string[0];

    while (new_symb != '\0') // Check End of line
    {
        new_symb = string[i];

        // Check the end of symbols and begining og separators
        if (not(prev_symb == ' ' or prev_symb == '\t' or prev_symb == '\n') and
            (new_symb == ' ' or new_symb == '\t' or new_symb == '\n' or new_symb == '\0'))
        {
            w_num++; // Increment words number
//             cout << "Increment: prev: " << prev_symb << " new: " << new_symb << endl;
        }
        prev_symb = new_symb;
        i++;
    }

    cout << "Number of words:" << w_num << endl;

    return 0;
}
