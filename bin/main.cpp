#include "KeyMaster.h"

//TODO: Implement args so that user may specify ip address in command line
int main(int argc, char* argv[]) 
{
    if(argc == 2)
    {
        KeyMaster* keymaster;
        cout << argv[2] << endl;
        keymaster->generate(argv[1]);
    }
    else
    {
        cout << "[-]  error: Please provide a valid IPv4 Address" << endl;
    }

    return 0;
}