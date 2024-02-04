# KeyMaster

Welcome to **KeyMaster**, the tool *Li3D* uses that allows certain developers to upload
3D Models to the platform. KeyMaster's job is to generate a secret developer key every 15 days,
whereby inserting this key to the Li3D Client allows the developer to upload URL's to the platform 
where they will be stored on the server so they may be downloaded by users.

## Pre-Requisites

1. Install g++
2. Install OpenSSL
3. Install libssl-dev
4. Install libcurl4-openssl-dev
5. Build
6. Execute

## Build

Upon installation of g++, OpenSSL, libcurl4 and libssl-dev development package, proceed by building KeyMaster with
the following command:

```bash
g++ -o KeyMasterClient KeyMaster.cpp main.cpp -O3 -lssl -lcurl -lcrypto
```
