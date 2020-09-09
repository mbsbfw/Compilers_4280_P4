#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include "scanner.h"
#include "parser.h"
#include "node.h"
#include "test_tree.h"
#include "staticSems.h"

using namespace std;

fstream target;

int main(int argc, char *argv[]){

    fstream in_file;
    char data[100];
    char src_file[25];
    string out_file;

    /*
        No file was given so I created a new file and will write the
        user input into that new file
    */
    if(argc == 1){

        //create new file to insert input from user
        in_file.open("input.dat", ios::out);

        //If file doesn't get created report error
        if(in_file.fail()) {
            cout << "ERROR: File was not created" << endl;
            return(-1);
        }

        while(cin.getline(data, sizeof(data))){

            //Used to simulate "end of file"
            if(!strncmp(data, "eof", sizeof(data)) || !strncmp(data, "EOF", sizeof(data))){
                //cout << "eof" << endl;
                break;
            }

            in_file << data << endl;
        }
        in_file.close();
        in_file.open("input.dat", ios::in);

        out_file = "out.asm";

        char *last_call = new char[out_file.length() + 1];
        strcpy(last_call, out_file.c_str());

        target.open(last_call, ios::out);

    }//end if(argc==1)

    //if the file argument is given then we read from that file
    if(argc == 2){

        //Check if ".sp2020" is in the file given
        strncpy(src_file, argv[1], sizeof(src_file));
        char search[] = ".sp2020";
        char *find_ptr = strstr(src_file, search);

        // Substring found
        if (find_ptr != NULL){

            printf("%s contains %s\n", src_file, search);

            string s = ".sp2020";
            out_file = src_file;
            size_t pos = out_file.find(s);

            if(pos != string::npos){
                out_file.erase(pos, s.length());
            }

            out_file.append(".asm");

            char *last_call = new char[out_file.length() + 1];
            strcpy(last_call, out_file.c_str());

            target.open(last_call, ios::out);

        } else /* Substring not found*/{

            printf("%s doesn't contain %s\n", src_file, search);in_file.open("input.dat", ios::out);
            printf("Program Terminating\n");
            return(-1);
        }

        in_file.open(src_file, ios::in);

        if(in_file.fail()){
            printf("ERROR: File unable to open");
            cout << endl;
            return(-1);
        }
    }//end if(argc==2)

    //TOO many arguments program terminates
    else if(argc > 2){
        printf("ERROR: Too many arguments");
        return(-1);
    }

    load_vector(in_file);
    //cout << vector_string.size() << endl;

//    for(int i = 0; i < vector_string.size(); i++){
//
//        cout << vector_string.at(i) << endl;
//    }
//
//    cout << endl;

    in_file.close();

    node *root = parser();

    //uncomment below to print tree
    //print_preorder(root, root->level);

    static_sems(root);

    cout << "out_file name: " << out_file << endl << endl;

    target.close();

    return 0;
}
