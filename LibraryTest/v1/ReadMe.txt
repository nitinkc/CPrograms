The header, library and main file all in same directory

//Creating onject file, by compliling the library file
gcc -c libTest1.c -o libTest1.o

//Linking the library and executing
gcc mainLibTest1.c libTest1.o