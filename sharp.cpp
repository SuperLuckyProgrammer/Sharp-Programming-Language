#include <iostream>
#include <fstream>
#include <cstdlib> // for exit function
#include <cstring>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
using namespace std;

// make the endl faster
#define endl "\n"

// create the public code data values
// code data -normal
vector<string> code_data {
    "print",
    "input",
    "exit",
    "system",
    "INT",
    "STRING",
    "LONG",
    "FLOAT",
    "DOUBLE",
    "<-",
    "->"
};

// code data -special
vector<char> code_wrappers {
    '\"',
    '\'',
    '(',
    ')',
    '[',
    ']'
};
// code keys
vector<string> code_keys{
    "function",
    "function",
    "function",
    "function",
    "datatype",
    "datatype",
    "datatype",
    "datatype",
    "datatype",
    "function_method_output",
    "function_method_input"
};
// opening the file
string open_file(string filename)
{
    // create the variable
    ifstream indata;         // indata is like cin
    indata.open(filename); // opens the file
    if (!indata)
    { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    // convert data to string format using stringstream
    string data;
    stringstream data_buffered;
    // input the data to the data buffered variable
    data_buffered << indata.rdbuf();
    // give the data to the variable data (string datatype)
    data = data_buffered.str();
    // close the indata ifstream file
    indata.close();
    return data;
}

// tokenize the program (.sha file not this one)
vector<string> tokenize(string str, char seperator)
{
    // vector for tokens
    vector<string> toks;
    // define the string length
    int string_length = str.length();
    // define substring (for elements)
    string sub_str = "";
    // creating i (index)
    int i = 0;
    // start the while loop
    while (i < string_length)
    {
        // check if the character is a wrapper (string)
        if (str[i] == '\"')
        {
            // do the do while loop (first at least get the " character without exit loop)
            do {
                // add the value to sub_str
                sub_str += str[i];
                // increment i
                i++;
            }
            while (str[i] != '\"');
            // add the last value to sub_str (")
            sub_str += str[i];
            // increment i
            i++;
            // add to tokens
            toks.push_back(sub_str);
            // reset sub_str
            sub_str = "";
        }
        else // if not a wrapper (string)
        {
            // check if it is a seperator
            if (str[i] == seperator || str[i] == '\n')
            {
                // also check if sub_str is blank (because if they added more than 1 space)
                if (sub_str != "")
                {
                    // add sub_str to toks
                    toks.push_back(sub_str);
                }
                // increment i
                i++;
                // reset sub_str
                sub_str = "";
            }
            // if it is a normal character, then add the current char to sub_str and increment i
            else
            {
                // add current char to sub_str
                sub_str += str[i];
                // increment i
                i++;
            }
        }
    }
    // return result
    return toks;
}

// displaying vector function
void display_vector(vector<string> to_print)
{
    // print the "{" symbol
    cout << "{" << endl;
    // loop through everything
    for (int i = 0; i < to_print.size(); i++)
    {
        // check if the current element (to_print[i]) ain't the last element
        if (i != to_print.size() - 1) // if true...
            cout << to_print[i] << ", " << endl; // print the element also adding ", "
        else // if it IS the last element...
            // then print the element itself adding "\n}" (end)
            cout << to_print[i] << endl 
                 << "}" << endl;
    }
}

// MAYBE USED LATER - DO NOT DELETE
/*void display_map(map<string, string> to_print)
{
    for (map<string, string>::iterator it = to_print.begin(); it != to_print.end(); ++it)
    {

        cout << (*it).first << ": " << (*it).second << endl;
    }
}
*/

// lexifier
vector<vector<string>> lexer(vector<string> tokens)
{
    // initialize variables
    // token length
    int toklen = tokens.size();
    // lexer keys and code
    vector<string> lexk;
    vector<string> lexc;

    // for loop
    for (int i=0; i<toklen; i++)
    {
        // looping through the code data
        for (int j=0; j<code_data.size(); j++)
        {
            // check if it is a part of code data
            if (tokens[i] == code_data[j])
            {
                // add it to the lexes
                lexk.push_back(code_keys[j]);
                lexc.push_back(tokens[i]);
                // break the loop
                break;
            }
            // check if it is a part of code wrappers
            else if (find(code_wrappers.begin(), code_wrappers.end(), tokens[i][0]) != code_wrappers.end())
            {
                // add it to the lexes
                lexk.push_back("value_wrap");
                lexc.push_back(tokens[i]);
                // break the loop
                break;
            }
        }
    }
    // result
    vector<vector<string>> result;
    result.push_back(lexk);
    result.push_back(lexc);
    // return the value
    return result;
}

// main function
int main()
{
    // create a variable called fname
    string fname;
    // input the filename
    // 1. ask the user
    cout << "filename: ";
    // 2. input the user
    cin >> fname;
    // open file
    string file = open_file(fname);
    // add eof - at least a seperator is ok :)
    file += ' ';
    // tokenize the file and assign it to a variable called tokens
    vector<string> tokens = tokenize(file, ' ');
    // lexify the file and assign it to a variable called lexes
    vector<vector<string>> lexes = lexer(tokens);
    // display the result
    // keys
    cout << "KEYS: ";
    display_vector(lexes[0]);
    cout << "CODE VALUES: ";
    display_vector(lexes[1]);
    return 0;
}