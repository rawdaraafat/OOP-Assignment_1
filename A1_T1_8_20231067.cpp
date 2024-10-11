/*
 * // File: A1_T1_8_202301067.cpp
// Purpose: problem 3 , 6 , 9 , 12
// Author:Rawda Raafat Ramadan
// Section: S8
// ID:20230117
// TA: Dr.Ramly
// Date: 10 Oct 2024
//please make sure to have the file you want to count the total count of phishing words in your directory,
 there is a phishing example files you can run the program on
//________________________________________________________________________
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

vector<string> split(string target, string delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = target.find(delimiter);

    while (end != string::npos) {
        result.push_back(target.substr(start, end - start));
        start = end + delimiter.length();
        end = target.find(delimiter, start);
    }

    if (start < target.length()) {
        result.push_back(target.substr(start));
    }

    return result;
}
class BinaryPrinter {
public:
    static void binaryprint(unsigned int n) {
        if (n > 1) {
            binaryprint(n / 2);
        }
        cout << (n % 2);
    }
    static void numbers(const string& prefix, int k) {
        if (k == 0) {
            cout << prefix << endl;
            return;
        }
        numbers(prefix + "0", k - 1);
        numbers(prefix + "1", k - 1);
    }
};

bool bears(int n) {
    if (n == 42) return true;
    if (n < 42) return false;

    if (n % 2 == 0 && bears(n / 2)) return true;
    if ((n % 3 == 0 || n % 4 == 0)) {
        int lastDigit = n % 10;
        int secondLastDigit = (n % 100) / 10;
        int product = lastDigit * secondLastDigit;
        if (bears(n - product)) return true;
    }
    if (n % 5 == 0 && bears(n - 42)) return true;
    return false;
}

//I get the words using chatGPT
map<string, int> keywords = {
        {"account", 3}, {"verify", 3}, {"click here", 3}, {"password", 3}, {"social security number", 3}, {"credit card", 3},
        {"bank", 2}, {"update", 2}, {"confirm", 2}, {"urgent", 3}, {"limited time", 2}, {"suspicious activity", 3}, {"secure", 2},
        {"login", 2}, {"billing", 2}, {"prize", 2}, {"lottery", 3}, {"refund", 2}, {"account suspended", 3}, {"transaction", 2},
        {"invoice", 2}, {"statement", 2}, {"alert", 3}, {"notification", 2}, {"paypal", 3}, {"ebay", 3}, {"amazon", 2}, {"apple", 2},
        {"google", 2}, {"unusual activity", 3}
};

int scan_text(const string& file_name) {
    int total_points = 0;
    ifstream file(file_name);
    if (!file.is_open()) {
        cout << "Unable to open file: " << file_name << endl;
        return total_points;
    }

    string line;
    while (getline(file, line)) {
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        istringstream iss(line);
        string word;
        while (iss >> word) {
            for (const auto& kv : keywords) {
                if (word.find(kv.first) != string::npos) {
                    total_points += kv.second;
                }
            }
        }
    }
    file.close();
    return total_points;
}


int main() {
    int choice;
    string target, delimiter;
    while (true) {
        cout << "Welcome to the program please enter the number of your chosen problem:\n"
             << "3- Split function\n"
             << "6- Two printing binary methods\n"
             << "9- Teddy Bear Picnic\n"
             << "12- Phishing Scanner\n"
             << "0- Exit\n"
             << "-> ";
        cin >> choice;
        cin.ignore();
        if (choice == 3) {
            cout << "Please enter what you want to split -> ";
            getline(cin, target);
            cout << "Please enter what you are separating them by -> ";
            getline(cin, delimiter);
            vector<string> result = split(target, delimiter);
            for (const auto& str : result) {
                cout << str << " ";
            }
            cout << "\n";
        } else if (choice == 6) {
            cout << "1- Print one binary number\n"
                    "2- Printing many binary numbers\n";
            int choice2;
            cout << "-> ";
            cin >> choice2;
            while (true){
                if(choice2 == 1){
                    cout << "Enter a number as n -> ";
                    int n;
                    cin >> n;
                    BinaryPrinter::binaryprint(n);
                    cout << endl;
                    break;
                }else if(choice2 == 2){
                    cout << "Please enter the prefix you want -> ";
                    string prefix;
                    cin >> prefix;
                    cout << "Please enter the number k -> ";
                    int k;
                    cin >> k;
                    cout << "Here are the possible outcomes of k-bits of number of suffix\n";
                    BinaryPrinter::numbers(prefix,k);
                    cout << endl;
                    break;
                }else{
                    cout << "Please enter a correct choice";
                    continue;
                }
            }

        } else if (choice == 9) {
            int n;
            cout << "Please Enter the number of bears -> ";
            cin >> n;
            if(bears(n)){
                cout << "It's possible to win the bears game with " << n << " bears!" << endl;
            }else{
                cout << "I am sorry you can't win the bears game with " << n << " bears" << endl;
            }
        } else if (choice == 12) {
            string file_name;
            cout << "Enter the name of the file (in the current directory): ";
            cin >> file_name;

            int total_points = scan_text(file_name);
            cout << "Total points: " << total_points << endl;
        } else if (choice == 0) {
            cout << "Thanks my dear user, hope to see you soon!" << endl;
            break;
        } else {
            cout << "Entered a wrong choice, please try again ^-^" << endl;
            continue;
        }
    }
}
