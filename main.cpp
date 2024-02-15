#include <iostream>
#include "Avl.h"
#include <regex>
#include "vector"
#include <string>

using namespace std;
/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/


int main(){

	Avl t;

    int command;
    vector<string> names;
    cin >> command; //take in number of commands
    for(int i = 0 ; i <= command; i++){
        string commands;
        string operation;
        getline(cin, commands);
  //use get line and iss to break up the input into parts for parsing
        istringstream iss(commands);
        iss >> operation;
        if(operation == "search"){ //if the first word is search
          //find where first quotation and second quotation occurs
            int firstpos = 0;
            int secondpos = 0;
            string searchfield;
            for (int j = 0; j < commands.length(); j++) { // loop through entire string to find the quotations
                if (commands[j] == '"') {
                    if (firstpos == 0) {
                        firstpos = j;

                    } else {
                        secondpos = j;
                    }
                }
            }
            if(firstpos != 0){ // check if there is a first quotation
                if(secondpos != 0){ //check if there is a second quotation
                    searchfield = commands.substr(firstpos+1, secondpos - firstpos-1); //the position from first to second quotation is the name
                    t.searchName(searchfield); //search for the name

                }
                else {
                    cout << "unsuccessful" << endl;
                }
            }
            else{
                iss >> searchfield;

                try{ //if the value is not a string, then try to search for a number
                    t.search(searchfield);

                }
                catch(...){
                    cout << "unsuccessful" << endl;
                }
            }

        }
        else if(operation == "insert") {  //if the first word is insert
            string name, ufid;
            int firstpos = 0; // check if there is a first quotation
            int secondpos = 0;// check if there is a second quotation

            for (int j = 0; j < commands.length(); j++) { // loop through entire string to find the quotations
                if (commands[j] == '"') {
                    if (firstpos == 0) {
                        firstpos = j;

                    } else {
                        secondpos = j;
                    }
                }
            }
            if (secondpos != 0) {
                name = commands.substr(firstpos, secondpos - firstpos + 1);
                if (secondpos != commands.length() - 2) {  //the position from first to second quotation is the name
                    secondpos+=2;   //the position from first to second quotation to the end of the string is the ufid
                    ufid = commands.substr(secondpos, commands.length() - secondpos);
                    t.insert(name, ufid);

                    continue;
                }
                cout << "unsuccessful" << endl;
            } else {
                cout << "unsuccessful" << endl;
            }


        }
        else if(operation == "remove"){  //if the first word is remove
            string ufid;
            iss >> ufid;
            t.remove(ufid);
        }
        else if(operation == "printInorder"){  //if the first word is printinorder
            names = t.getInOrder();

            for(int j = 0; j<names.size()-1; j++){ //print everything in the in order vector one by one
                cout<< names.at(j)+", ";
            }
            cout<<names.at(names.size()-1) << endl;

        }
        else if(operation == "printPreorder"){  //if the first word is printpreorder
            names = t.getPreOrder();

            for(int j = 0; j<names.size()-1; j++){ //print everything in the pre order vector one by one
                cout<< names.at(j)+", ";
            }
            cout<<names.at(names.size()-1)<< endl;

        }
        else if(operation == "printPostorder"){  //if the first word is printpostorder
            names = t.getPostOrder();

            for(int j = 0; j<names.size()-1; j++){ //print everything in the post order vector one by one
                cout<< names.at(j)+", ";
            }
            cout<<names.at(names.size()-1) << endl;

        }
        else if(operation == "removeInorder"){  //if the first word is removeinorder
            unsigned int position;
            iss >> position; //remove the specified number
            t.removeInorder(position);
        }
        else if(operation == "printLevelCount"){  //if the first word is printlevelcount
            t.printLevelCount();
        }


    }
	return 0;
}
