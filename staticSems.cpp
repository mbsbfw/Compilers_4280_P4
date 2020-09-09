#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include "staticSems.h"
#include "token.h"
#include "node.h"

using namespace std;

static int temp_var = 0;

//This variable is for if a single variable has been defined
static stacked temp;

//The stack, which will hold all the variables defined.
vector<stacked> stack;

//Current location on the stack
int stack_location = 0;

//Variables currently on the stack
int stack_vars = 0;

int nums_on = 0;

string rem = "Integer ";

void static_sems(node *root){

    if(root->literal == "<program>"){

        //cout << endl << "root is <program>" << endl;
        static_sems(root->child_1); //<vars>
        static_sems(root->child_2); //<block>

        //Print stop at the end of created program
        target << "STOP" << endl;

        cout << "+=+=+ SEMANTICS are OK +=+=+" << endl << endl;

        while (temp_var > 0){
            target << "T" << (temp_var - 1) << " 0" << endl;
            temp_var--;
        }

        return;
    }

    //<vars> => empty | declare Identifier := Integer ; <vars>
    if(root->literal == "<vars>"){

        temp.token = root->all_toks.front();
        root->all_toks.erase(root->all_toks.begin());

        if(temp.token.tok_string != "EMPTY"){

            //Declare variable if it has not already been declared
            declare_var(temp);

            //Increment the number of variables on the stack
            stack_vars++;

            //process <vars>
            static_sems(root->child_1);
        }
    }

    //<block> => { <vars> <stats> }
    if(root->literal == "<block>"){

        static_sems(root->child_1); //<vars>
        static_sems(root->child_2); //<stats>

        return;
    }

    //<expr> => <N> - <expr> | <N>
    if(root->literal == "<expr>"){
        //If empty, then production was <N>
        if(root->all_toks.empty()){

            static_sems(root->child_1); //<N>
        }else{

            int var = temp_var;
            temp_var++;

            static_sems(root->child_2); //process <expr>

            target << "STORE T" << var << endl;

            static_sems(root->child_1); //process <N>

            if (root->all_toks.at(0).tok_string == "Operator -"){
                //Subtract the temporary variable
                target << "SUB T" << var << endl;
            }

            return;
        }
    }

    //<N> => <A> / <N> | <A> * <N> | <A>
    if (root->literal == "<N>"){

        //If empty, then the production was <N> => <A>
        if (root->all_toks.empty()){

            static_sems(root->child_1); //<A>
        }else{
            int var = temp_var;
            temp_var++;

            static_sems(root->child_2); //<N>

            target << "STORE T" << var << endl;

            static_sems(root->child_1); //<A>

            if (root->all_toks.at(0).tok_string == "Operator /"){
                //Divide the temporary variable by the value in the
                target << "DIV T" << var << "\n";

            }else if (root->all_toks.at(0).tok_string == "Operator *"){
                //Multiply the temporary variable
                target << "MULT T" << var << endl;
            }

            return;

        }
    }

    //A => <M> + <A> | <M>
    if(root->literal == "<A>"){
        //If empty, then production was <M> + <A>
        if(root->all_toks.empty()){
            static_sems(root->child_1); //process <M>
        }else{
            //create temporary var
            int var = temp_var;
            temp_var++;

            static_sems(root->child_2); //process <A>

            //STORE T so it is back to an arg
            target << "STORE T" << var << endl;

            static_sems(root->child_1); //process <M>

            if (root->all_toks.at(0).tok_string == "Operator +"){
                //Add the temporary variable
                target << "ADD T" << var << endl;
            }

            return;
        }
    }

    //<M> => * <M> | <R>
    if(root->literal == "<M>"){

        static_sems(root->child_1); //process <M> or <R>

        if (!root->all_toks.empty()){
            //Multiply itself
            target << "MULT 1" << endl;
        }

        return;
    }

    //<R> => ( <expr> ) | Identifier | Integer
    if (root->literal == "<R>"){
        //If empty, then production was <R> => ( <expr> )
        if (root->all_toks.empty()){
            static_sems(root->child_1); //process <expr>
        }else{

            temp.token = root->all_toks.front();

            if (temp.token.ID == ID_tk){
                //Check to determine if this variable may be accessed
                lookup_var(temp);

            //Remove "Integer" from my parsed token
            }else if(temp.token.ID == INT_tk){
                size_t pos = temp.token.tok_string.find(rem);

                if(pos != string::npos){
                    temp.token.tok_string.erase(pos, rem.length());
                }

                //Load the temporary variable
                target << "LOAD " << temp.token.tok_string << endl;
                return;
            }

            return;
        }
    }

    //<stats> => <stat> <mStat>
    if(root->literal == "<stats>"){
        static_sems(root->child_1); //<stat>
        static_sems(root->child_2); //<mStat>
    }

    //<mStat> => empty | <stat> <mStat>
    if(root->literal == "<mStat>"){
        //The <mStat> production will normally not have any tokens,
        if (root->all_toks.empty()){
            static_sems(root->child_1); //process <stat>
            static_sems(root->child_2); //process <mStat>
        }
    }

    //<stat> => <in>; | <out>; | <block> | <if>; |
        //<loop>; | <assign>; | <goto>; | <label>;
    if(root->literal == "<stat>"){
        static_sems(root->child_1); //RHS production
    }

    //<in> =>  in Identifier
    if(root->literal == "<in>"){

        //Create my temporary token and variable
        temp.token = root->all_toks.front();
        int var = temp_var;
        temp_var++;

        //Verify that the identifier exists, and was declared
        lookup_var(temp);

        target << "READ T" << var << endl;
        target << "LOAD T" << var << endl;

        return;
    }

    //<out> => out <expr>
    if(root->literal == "<out>"){

        //Create temp variable
        int var = temp_var;
        temp_var++;

        static_sems(root->child_1); //process <expr>

        //Store and write to target
        target << "STORE T" << var << endl;
        target << "WRITE T" << var << endl;

        return;
    }

    //<if> => iffy [ <expr> <RO> <expr>] then <stat>
    if(root->literal == "<if>"){

        //Create two temp variables for iffy and variable
        int iffy = ++nums_on;
        int var = temp_var;
        temp_var++;

        //Followed our guide to store sub and out to nothing
        target << "IFFY" << iffy << ": ";

        static_sems(root->child_1); //<expr>

        target << "STORE T" << var << endl;

        static_sems(root->child_3); //<expr>

        target << "SUB T" << var << endl;

        static_sems(root->child_2); //<RO>

        static_sems(root->child_4); //<stat>

        target << "OUT" << iffy << ": NOOP" << endl;

        return;
    }

    //<loop> => loop [ <expr> <RO> <expr> ] <stat>
    if(root->literal == "<loop>"){
        //Create two temp variables for loop and variable
        int loop = ++nums_on;
        int var = temp_var;
        temp_var++;

        //Followed our guide to store sub and out to nothing
        target << "LOOP" << var << ": ";

        static_sems(root->child_1); //<expr>

        target << "STORE T" << var << endl;

        static_sems(root->child_3); //<expr>

        target << "SUB T" << var << endl;

        static_sems(root->child_2); //<RO>

        static_sems(root->child_4); //<stat>

        target << "BR LOOP" << loop << endl;

        target << "OUT" << loop << ": NOOP" << endl;
    }

    //<assign> => Identifier := <expr>
    if(root->literal == "<assign>"){
        //cout << "<assign>" << endl;
        //Check if the identifier has been defined
        temp.token = root->all_toks.front();

        int define = lookup_var(temp);

        //if variable isn't found, then it wasn't declared else push on stack
        if(define == -1){
            cout << "Semantics Error: The -*" << temp.token.tok_string
            << "*- has NOT been declared in this scope." << endl;
            exit(EXIT_FAILURE);
        }
//        else{
//            //Push the variable onto the stack and increment the stack location.
//            stack.push_back(temp);
//            stack_location++;
//            //print_stack();
//        }

        static_sems(root->child_1); //<expr>

        return;
    }

    //<label> => label Identifier
    if(root->literal == "<label>"){
        temp.token = root->all_toks.front();

        if (temp.token.ID == ID_tk){
            //Check to determine if this variable may be accessed
            lookup_var(temp);

            return;
        }
    }

    //<goto => goto Identifier

    //<RO> => < | < < (two tokens >) | > | > > (two tokens) | == (one token==)
    if(root->literal == "<RO>"){

        temp.token = root->all_toks.front();

        if ((token_names[temp.token.ID] == "Operator")){

            //is LESS THAN
            if((temp.token.tok_string == "Operator <")){

                if(!root->all_toks.empty()){

                    root->all_toks.erase(root->all_toks.begin());
                    stacked temp_2;
                    temp_2.token = root->all_toks.front();

                    //NOT EQUAL
                    if((temp_2.token.tok_string == "Operator >")){

                        target << "BRZERO OUT" << nums_on << endl;
                        return;
                    }

                    //is LESS
                    else if((temp_2.token.tok_string == "Operator <")){

                        target << "BRZNEG OUT" << nums_on << endl;
                        return;
                    }

                    else{
                        target << "BRNEG OUT" << nums_on << endl;
                        return;
                    }
                }
            }

            else if((temp.token.tok_string == "Operator >")){
                if(!root->all_toks.empty()){

                    //root->all_toks.erase(root->all_toks.begin());
                    stacked temp_2;
                    temp_2.token = root->all_toks.front();

                    //is GREATER EQUAL
                    if((temp_2.token.tok_string == "Operator >")){

                        target << "BRZPOS OUT" << nums_on << endl;
                        //return;
                    }
                    //is GREATER
                    else{
                        target << "BRPOS OUT" << nums_on << endl;
                        //return;
                    }

                    return;
                }
            }
            //is EQUAL 0
            else if((temp.token.tok_string == "Operator ==")){
                if(!root->all_toks.empty()){

                    target << "BRPOS OUT" << nums_on << endl;
                    target << "BRNEG OUT" << nums_on << endl;
                    return;

                }
            }
        }//end OPERATOR if()
    }//RO
}//end static sems

void declare_var(stacked vars){

    //cout << "Declare " << vars.token.tok_string << endl;

    int define = lookup_var(vars);

    if(define != -1){
        cout << "Semantics Error: The -*" << vars.token.tok_string
      << "*- has already been defined in this scope." << endl;
        exit(EXIT_FAILURE);
    }else{
        //Push the variable onto the stack and increment the stack location.
        stack.push_back(vars);
        stack_location++;
        //print_stack();

    }
}

int lookup_var(stacked vars){

    //cout << "Looking up " << vars.token.tok_string << endl;
    for(int iter = 0; iter < stack.size(); iter++){
        //If the given identifier matches the identifier at this location
        //in the stack, return the location of this variable in the stack
        if((stack.at(iter).token.tok_string == vars.token.tok_string)){
            return iter;
        }
    }

    return -1;
}//end lookup_var

