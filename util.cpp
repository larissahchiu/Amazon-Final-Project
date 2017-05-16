#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
//word must be at least 2 characters long
//cannot have punctuation
//if it does have punctuation, see which of the words is more than 2 strings and return that

//isbn numbers and movie genres don't need to be parsed. 

// what needs to be parsed: any product name(book title, clothing item, 
// movie title), author's name(s), brand. 
std::set<std::string> parseStringToWords(string rawWords)
{   
    string lower = convToLower(rawWords);

    set<string> words;
    stringstream ss(lower);
    string s;
    while(ss >> s){
            unsigned int i = 0;
            while(i != s.size() && s.size() > 1){
                if(ispunct(s[i])){
                    string substr = s.substr(0, i);
                    s = s.substr(i + 1, s.size() - i);
                    if(substr.size() > 1){
                        words.insert(substr);
                        i = 0;
                    }
                }

                i++;
            }

        if(s.size() > 1){
            words.insert(s);
            }

        }



    return words;
}


/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
