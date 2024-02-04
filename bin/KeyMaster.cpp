#include "KeyMaster.h"

/*
To use KeyMaster simply call this function. Calling this function creates a secret key
that is written to the file 'key.db'. If the file doesn't exist, it will be created in the same 
directory as the executable, where the key is then written. If the file exists, execution 
will cause the previous key to be overwritten.
*/
string KeyMaster::generate(string ip_addr)
{
    string message = create_random_string(64);  //Generates a random 64-character string
    string key = sha256(message);               //Creates a sha256 hash from the randomly generated 64-character string.

    write("passphrase.db", message);            //Writes the passphrase to a file named key.db

    POST("http://" + ip_addr + ":" +            //Uploads the sha256 hash to the server with the specified IPv4 address.
    "8001/api/upload?key=" + key);

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

bool KeyMaster::POST(string full_url)
{
    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();

    if(curl)
    {
        struct curl_slist *headers = NULL;

        curl_easy_setopt(curl, CURLOPT_URL, full_url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
        {
            fprintf(stderr, "[-]  error!: %s\n", curl_easy_strerror(res));
            return FAIL;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return PASS;
}
