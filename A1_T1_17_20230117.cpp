// File: A1_T1_17_20230117.cpp
// Purpose: problem 1 , 4 , 7 , 10
// Author:Habeba Hossam AbdAlKader Alagamy
// Section:s17
// ID:20230117
// TA:
// Date: 10 Oct 2024
//github:https://github.com/rawdaraafat/OOP-Assignment_1
//please make sure to add lookupfile.txt & message.txt to be able to run problem 10
//________________________________________________________________________
#include <iostream>
#include <deque>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <codecvt>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;
unordered_map<wstring, vector<wstring>> loadLookupTable() { //to fill lookup map
    unordered_map<wstring, vector<wstring>> lookup;
    wifstream lookupfile("lookupfile.txt");
    wstring line;
    while (getline(lookupfile, line)) {
        wstringstream ss(line);
        wstring key;
        getline(ss, key, L':'); // Read the key
        wstring alternative;
        while (getline(ss, alternative, L' ')) { // Read alternatives separated by space //(L) for unicode
            lookup[key].push_back(alternative);
        }
    }
    lookupfile.close(); //close the file after  using it
    return lookup;
}
void edit(wifstream &inputfile, wofstream &outputfile, const unordered_map<wstring, vector<wstring>> &lookup) {
    wstring inputline;
    while (getline(inputfile, inputline)) {
        wstringstream ss(inputline);
        wstring word;
        wstring updatedLine;
        while (ss >> word) {
            auto it = lookup.find(word); //cheek if the word exist in the lookup map
            if (it != lookup.end()) { //the word exist
                const vector<wstring> &alternatives = it->second;
                int randomIndex = rand() % alternatives.size(); // Generate random index
                updatedLine += alternatives[randomIndex] + L" "; // Add random alternative to the updated line
            } else {
                updatedLine += word + L" "; // Keep the original word
            }
        }
        outputfile << updatedLine << endl; // Write the updated line to the output file
    }
}
vector<int>num;
struct Dominot{
    int leftDots;
    int rightDots;
    Dominot(int r , int l ){ //constructor
        rightDots = r;
        leftDots = l;
    }
};
bool trychain(vector<Dominot>dominos , int current_right , int current_left){ //try to form chain
    if (dominos.empty()) {
        return true;
    }
    for (int i = 0; i < dominos.size(); i++) {
        if (dominos[i].leftDots == num.back()) { //cheek match
            num.push_back(dominos[i].leftDots);//add to output vector
            num.push_back(dominos[i].rightDots); //add to output vector
            current_right=dominos[i].rightDots; //update current left
            Dominot temp = dominos[i]; // to store it
            dominos.erase(dominos.begin() + i);//remove it
            if (trychain(dominos, current_right, current_left)) { // recursion
                return true; // If chain is formed, return true
            }
            dominos.insert(dominos.begin() + i, temp);//if chain  can not form chain return it again and continue
            num.pop_back();//remove it
            num.pop_back(); //remove it
        } else if (dominos[i].rightDots == num.front()) {
            num.insert(num.begin(), dominos[i].rightDots); //add to output vector
            num.insert(num.begin(), dominos[i].leftDots); //add to output vector
            current_left=dominos[i].leftDots; //update current right
            Dominot temp = dominos[i];//to store it
            dominos.erase(dominos.begin() + i); //remove it
            if (trychain(dominos, current_right, current_left)) { //recurion
                return true; // If chain is formed, return true
            }
            dominos.insert(dominos.begin() + i, temp); //if chain  can not form chain return it again and continue
            num.erase(num.begin(), num.begin() + 2);
        }
    }
    return false; // No valid chain found
}
bool FormsDominoChain(vector<Dominot> & dominos){
    int current_left = dominos[0].leftDots, current_right = dominos[0].rightDots; //insilize current right & current left
    num.push_back(current_left);//add to output vector
    num.push_back(current_right);//add to output vector
    dominos.erase(dominos.begin()); //remove it
    return trychain(dominos, current_right, current_left); //return true or false
}
int main(){
    cout << "Welcome!" << endl;
    while(true) {
        cout << "1)problem 1 (words correction)\n2)problem 4 (prime)\n3)problem7 (domino)\n4)problem 10\n5)Exit\n";
        string o;
        getline(cin, o );
        if (o[0] == '1') {
            string s;
            string result;
            cout << "Enter your line :";
            getline(cin, s , '.');//take the input line with . as delimeter
            if(isalpha(s[0])){
                result += toupper(s[0]); // change fisrt char to uppercase
            }
            s.erase(0, 1); // remove the first char
            for (char c: s) {
                if (isalpha(c)) {
                    result += tolower(c); //add to the output string
                } else if (isdigit(c)) {
                    result += char(c); //add to the output string
                } else if (ispunct(c)) {
                    result += char(c); //add to the output string
                }
                if (isspace(char(c)) && result.back() != ' ') { //to make only one space between words
                    result += ' ';
                }
            }
            if(result.front() == ' '){//to avoid the line from begining with space
                result.erase(0, 1);
                result[0] = toupper(result[0]);
            }
            if(result.back() != '.'){ //make the line end with .
                if(result.back() == ' '){
                    result.pop_back();
                }
                result.push_back('.');
            }
            cout << result << endl; //output the final result
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

        } else if (o[0] == '2') {

            string num;
            cout << "Enter number :";
            getline(cin , num);
            bool is_num = false;
            for(int i = 0 ; i < num.size() ;i++){ //cheeck the input is integer
                if(isdigit(num[i])){
                    is_num = true;
                }else{
                    is_num= false;
                }
            }
            if(is_num) {
                int n = stoi(num);
                vector<int> dq;
                vector<int> res;
                for (int i = 2; i <= n; i++) {  // put numbers in vector to check if they are prime or not
                    dq.push_back(i);
                }
                for (int j = 0; j < dq.size(); j++) {
                    res.push_back(dq[j]);
                    for (int k = j + 1; k < dq.size(); k++) {
                        if (dq[k] % dq[j] == 0) {
                            dq.erase(dq.begin() + k); // remove the multiple of the selected number
                        }
                    }
                }
                cout << "prime :";
                if(res.empty()){
                    cout << "none";
                }else{
                    for (int i = 0; i < res.size(); i++) {
                        cout << res[i] << ' ';
                    }
                }
                cout << endl;
            }else{
                cout << "invalid num!" << endl;
            }
        } else if (o[0] == '3') {
            num.clear();
            int n;
            cout << "Enter number of dimonos :";
            cin >> n;
            vector<Dominot> dominos;
            for (int i = 0; i < n; i++) {
                int l, r;
                cout << "Enter left dots number of dimino #" << i + 1 << " :";
                cin >> l;
                while (l < 0 || l > 6) {//cheek
                    cout << "Invalid enter number from 0_6 !" << endl;
                    cin >> l;
                }
                cout << "Enter right dots number of dimino #" << i + 1 << " :";
                cin >> r;
                while (r < 0 || r > 6) {//cheek
                    cout << "Invalid enter number from 0_6" << endl;
                    cin >> r;
                }
                dominos.emplace_back(r, l); // Add the domino to the vector
            }
            if (n > 1) {
                if (FormsDominoChain(dominos)) {
                    for (int i = 0; i < num.size(); i += 2) {
                        cout << num[i] << "|" << num[i + 1] << (i + 2 < num.size() ? " - " : ""); //print chain
                    }
                    cout << endl;
                } else {
                    cout << "A domino chain cannot be formed." << endl;
                }
            } else {
                cout << "one domino can not form chain ! " << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            /*} else if (o[0] == '4') {
                locale::global(locale("")); // Set locale to UTF-8
                srand(time(0)); //to avoid given the same  random numbers at eveytime.
                string s;
                cout << "Enter file name: ";
                getline(cin, s);
                wifstream inputfile(s, ios::in); // Open input file read only
                if(inputfile.fail()) {
                    while (true) {
                        cerr << "File opening failed!" << endl;
                        cout << "Enter file name: ";
                        getline(cin, s);
                        wifstream inputfile(s, ios::in); // Open input file read only
                        if(inputfile.is_open()){
                            break;
                        }
                    }
                }
                cout << "File opened successfully." << endl;
                wofstream outputfile("updatedfile.txt"); // Create output file
                unordered_map<wstring, vector<wstring>> lookup = loadLookupTable();
                edit(inputfile, outputfile, lookup);
                cout << "done" <<endl;
                outputfile.close();
                inputfile.close();*/
        }else if (o[0] == '4') {
            locale::global(locale("")); // Set locale to UTF-8
            srand(time(0)); // Seed for random number generator
            string s;
            wifstream inputfile; // Declare input file stream
            while (true) {
                cout << "Enter file name: ";
                getline(cin, s);
                inputfile.open(s, ios::in); // Try to open the input file
                if (inputfile.is_open()) {
                    cout << "File opened successfully." << endl;
                    break; // Exit loop if file opened successfully
                } else {
                    cerr << "File opening failed! Please try again." << endl;
                }
            }

            // Create output file now that we have a valid input file
            wofstream outputfile("updatedfile.txt"); // Create output file
            unordered_map<wstring, vector<wstring>> lookup = loadLookupTable();
            edit(inputfile, outputfile, lookup);
            cout << "Done" << endl;

            outputfile.close();
            inputfile.close();

        } else if (o[0] == '5') {
            cout << "Exit....";
            exit(0);
        } else {
            cerr << "Invalid!" << endl;
        }
    }
}
