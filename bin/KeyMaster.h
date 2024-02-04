#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <openssl/sha.h>
#include <curl/curl.h>

#define PASS 0
#define FAIL -1

using namespace std;

class KeyMaster
{
public:
    string generate(string ip_addr);
private:
    string sha256(const string inputstr);
    void write(string filename, string data);
    string create_random_string(short strlen);
    bool POST(string full_url);
};