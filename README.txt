COMP_SCI_4280
Project: P4
BY: MICHAEL SAGO                                                                                                         2 Project: P3                                                                                                           3 BY: MICHAEL SAGO
Language C++


*****	* 
SOME	* I noticed in my expressions that they worked best when the variable was on the  
	* right side. Also didnt get all the way through my label and goto. P4.test5.sp2020
ISSUES	* explains some issues there. Also had some trouble with dealing with expressions
	* inside my iffy staements and or loops. Before turning it in I checked my  
	* < < and > > and they werent working agin somehow, so confused on that.
*****	* 

This is the final project is done in the C++ programming language. This program 
is a simple compiler that generates code for an assembly language that our  
professor created. Like before it uses a scanner, parser, and STATIC SEMANTICS to 
make sure all variables are global,declared and also checks if they have previously 
been declared. I have implemented, included, and explained my own test files for this 
project. The later test files include more and more code with loops and if statements. 
After the program runs it will tell you if the file parsed and ifthe sematics were 
ok; after that it will print out a ".asm" out_file.

*This assembly language only works with integers.It also uses all temporary variables 
I also implemented this program with only spaces not tabs and not spaces at the end of 
each line. Also every token should be seperated by a space

-+-+Also can uncomment print_preorder(root, root->level); in main to see parse tree

P4.test1.sp2020 - Simply prints 'out' the number 6

P4.test2.sp2020 - Declares a vaiable uses assignment to assign 11 to that variable 
		  and prints it 'out'

P4.test3.sp2020 - Declares a variable accepts user input 'in' and prints that number 'out'

P4.test4.sp2020 - Declares a variable then allows user input 'in' and does a calculation
		  with that input. Shows use of parenthesis and not (USES EXPRESSIONS)

P4.test5.sp2020 - *NOT TOO BAD* - ALL conditionals work they just print out the subtraction...
		  Declares a variable then accepts user input and checks
		  if that input is less than 5 in an if 'iffy' statement and
		  suppose to print out the input.

P4.test6.sp2020 - Declares a variable then accepts user input and checks
		  if that input is less than or equal to 0 in an if 'iffy' statement 
		  and if true then checks again in an 'iffy' statement that it 
		  is not equal to zero.
		  (nested iffy statements)

P4.test7.sp2020 - Declares a variable then accepts user input and checks if that
		  input is greater or equal to 0 in a loop 'loop' statement if it 
		  is greater or equal it allows for user input again prints that 
		  user input out to the screen until the condtion is false.

P4.test8.sp2020 - Declares a variable then accepts user input and checks if that
		  input is less than or equal to 0 in a loop 'loop' statement if it 
		  is less than or equal it assigns that variable to 6 and prints it
		  out

P4.test9.sp2020 - Declares a variable then accepts user input and checks if that
		  input is greater than 0 in a loop 'loop' statement if it 
		  is greater it allows for user input again and prints that 
		  user input out to the screen until the integer entered is less
		  than zero.

P4.test10.sp2020 - Declares a variable then accepts user input and checks if that
		   input is equal to 0 in a loop 'loop' statement if it 
		   is equal it assigns that variable to 16 and prints it
		   out

P4.test11.sp2020 - Declares a variable then checks if that variable is greater than 0
		   in a 'loop' statement and if so it checks if that variable is not
		   equal to zero in an 'iffy' statement and if so allows for user input
		   again and contimues through the loop until the input is less than or 
		   equal to zero. (NESTED IFFY INSIDE LOOP)

//To compile the program:
      >make comp

//Then you have two options to run the program:
       1.
          >./comp [filename]
          /*
             Testing files are included above
          */
       2.
          >./comp
 /*
    If using option 2 you will then be able to enter diferent strings or
    integers of your choice but it must fit the BNF. I use a simulated end of
    file so you should enter either eof or EOF on a line by itself to end your
    input and the scanner will start going through that input and
    indicating tokens. At the end it will then tell you if it parsed ok. It will
    also show you a parse tree ouputed to the screen.
 */
