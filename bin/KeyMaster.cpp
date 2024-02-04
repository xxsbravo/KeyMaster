#include "KeyMaster.h"

/*
To use KeyMaster simply call this function. Calling this function creates a secret key
that is written to the file 'key.db'. If the file doesn't exist, it will be created in the same 
directory as the executable, where the key is then written. If the file exists, execution 
will cause the previous key to be overwritten,
*/
string KeyMaster::generateKey()
{
    string message = create_random_string(64);  //Generates a random 64-character string
    string key = sha256(message);               //Creates a sha256 hash from the randomly generated 64-character string.

    write("passphrase.db", message);            //Writes the passphrase to a file named key.db
    write("key.db", key);                       //Writes the secret key (a SHA-256 hash) to a file named key.db

    return key;
}

/*The sha256 function generates a hash with a given input string*/
string KeyMaster::sha256(const string inputstr)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    const unsigned char* data = (const unsigned char*)inputstr.c_str();
    SHA256(data, inputstr.size(), hash);

    stringstream stream;

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        stream << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    return stream.str();
}

/*Creates a randomly generated string. Using strlen allows the developer to specify the amount of characters
the string should have.*/
string KeyMaster::create_random_string(short strlen)
{
    const char chars[] = {"abcdefghijklmnopqrstuvwxyz" 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ" 
    "0123456789"};

    int random;
    string str;

    srand(time(0));

    for(int i=0; i < strlen; i++)
    {
        random = rand() % 62;
        str += chars[random];
    }

    return str;
}

/*Writes plaintext data to a file of a specified name*/
void KeyMaster::write(string filename, string data)
{
    ofstream file;

    file.open(filename);
    file << data;
    file.close();
}