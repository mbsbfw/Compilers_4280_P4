//#include <iostream>
//#include <fstream>
//#include <string>
//#include "t_scanner.h"
//#include "token.h"
//#include "scanner.h"
//
//using namespace std;
//
//int line;
//int line_pos;
//
//void tst_scanner(fstream &file){
//
//    Token get_token;
//    string input = " ";
//    line = 1;
//
//    //If file opens properly
//    if(file){
//
//        //Read from file line by line
//        while(getline(file, input)){
//            //cout << "+++ Reading from file +++" << endl;
//
//            //Filter out comments and erase beginning white spaces
//            filter(input);
//            if(input.at(0) == ' '){
//                input.erase(0,1);
//            }
//
//            //Reinitialize line_pos to 0 after each line
//            line_pos = 0;
//
//            if(input.length() > 0){
//
//                while(scanner(input, get_token) == 0){
//                    display(get_token);
//                }//end while
//            }//end if
//            line++;
//
//        }//end while
//
//        //If end of file reached
//        if(file.eof()){
//            get_token.ID = EOF_tk;
//            get_token.tok_string = token_names[EOF_tk];
//            get_token.line_number = line;
//            display(get_token);
//        }
//    }//end if(file)
//}
//
//void filter(string &input_filter){
//
//    //Variables for current and next char
//    char cha, next_cha;
//
//    if(line_pos >= input_filter.length()){
//        cout << line_pos << " >= " << input_filter.length() << endl;
//    }
//
//    /*
//        For loop to loop through and look for
//        beginning # and ending # which are comments
//        and erase everything in between
//    */
//    for(int i = 0; i < input_filter.length(); i++){
//
//        cha = input_filter.at(i);
//
//        if(cha == '#'){
//
//            while(1){
//
//                input_filter.erase(i, 1);
//                next_cha = input_filter.at(i);
//
//                if(next_cha == '#'){
//                    input_filter.erase(i, 1);
//                    break;
//                }//endif
//            }//end while
//        }//end if
//    }//end for
//}
//
//void display(Token get_token){
//    //cout << "++++++display token+++++++" << endl;
//    cout << "Line #" << get_token.line_number << " " << get_token.tok_string << endl;
//}
