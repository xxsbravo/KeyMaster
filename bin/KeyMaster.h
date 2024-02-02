#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <openssl/sha.h>

using namespace std;

class KeyMaster
{
public:
    string generateKey();

protected:
    string sha256(const string inputstr);

private:
    void write(string filename, string data);
    string create_random_string(short strlen);
};