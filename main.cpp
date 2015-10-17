#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

double doAction(double a, char sign, double b);

// input: written formula
//output: vector of tokens of input formula
vector<string> getTokensFromTheLine(string str);


// input: tokens from string
//output: vector of sorted tokens acording to Polish method
vector <string> makePolishReverse(vector <string> tokens);

// input: vector of sorted tokens acording to Polish method
//output: double result
double calculate(vector <string> tokens);

// input: string with some symbol
//output: if '(' ==> true, else ==> false
bool isOpenParenthesis(string ch);

// input: string with some symbol
//output: if ')' ==> true, else ==> false
bool isCloseParenthesis(string ch);

// input: string with some symbol
//output: if it is number ==> true, else ==> false
bool isNumber(string str);

// input: string we expect it's number
//output: type double number
double parseNumber(string str);

// input: some stack of numbers
//output: top elemnt of stack and delete this element from stack
double getTopElementFromStack(stack <double > *numbers);

int main()
{
    string str;
    cout << "enter string" << endl;
    cin >> str;
    double result = calculate( makePolishReverse( getTokensFromTheLine(str) ) );
    cout << "the result is " << result << endl;
    return 0;
}




vector <string> getTokensFromTheLine(string str){
    // have to make array of tokens from the formula
    // where each token is next number or symbol such as + - / * in formula

     string sign = "*/+-";
    vector <string> tokens;
        string::iterator begin = str.begin();
        string::iterator current = str.begin();


    while (current != str.end())
    {
        while ((find(sign.begin(), sign.end(), *current) == sign.end()) && (current != str.end()))
            ++current;

        tokens.push_back(string(begin, current));
        if (current != str.end())
        {
            tokens.push_back(string(1,*current));
            ++current;
            begin = current;
        }
    }
    return tokens;
}


bool isNumber(string str){
    if (str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' || str[0] == '8'
            || str[0] == '9' || str[0] == '0')
        return true;
    else
        return false;
}

bool isOpenParenthesis(string ch){
    if (ch[0] == '(')
        return true;
    return false;
}

bool isCloseParenthesis(string ch){
    if (ch[0] == ')')
        return true;
    return false;
}

vector <string> makePolishReverse(vector <string> tokens){
    vector <string> newTokenList;
    stack <string> signs;

    int tokensSize = tokens.size();
    for (int i; i<tokensSize; i++){
        if (isNumber(tokens[i])){
           newTokenList.push_back(tokens[i]);
        }
        else if ( isOpenParenthesis(tokens[i]) ) {
            signs.push(tokens[i]);
        }
        else if ( isCloseParenthesis(tokens[i]) ){
            //while is not open parenthesis -
            //take elementfrom from stack and put to newTokenList
            while( ! isOpenParenthesis( signs.top() ) ){
                newTokenList.push_back(tokens[i]);
                signs.pop();
            }
            //then remove open parenthesis from stack
            signs.pop();
            //this part works corrctly if only formula is correct, i.e has same number of  '('  and  ')'
        }
        else { //it's a some sign ( + or - or * or / ) for this version of program,
                //so here could be problems if formula has any incorrect symbols
                //this scope is had to be rewritten, because it is totally unflexable and "kostil'"
            if (tokens[i][0] == '*' || tokens[i][0] == '/'){
                while  (signs.top()[0] == '/' || signs.top()[0] == '*'){
                    newTokenList.push_back(signs.top());
                    signs.pop();
                }
            signs.push(tokens[i]);
            }

            if (tokens[i][0] == '+' || tokens[i][0] == '-'){
                while (signs.top()[0] == '+' || signs.top()[0] == '-' || signs.top()[0] == '/' || signs.top()[0] == '*'){
                    newTokenList.push_back(signs.top());
                    signs.pop();
                }
                signs.push(tokens[i]);
            }
        }

    }

    while(!signs.empty()){
        newTokenList.push_back(signs.top());
        signs.pop();
    }

    return newTokenList;
}


double calculate(vector <string> tokens){
    std::stack <double> numbers;

    int tokensSize = tokens.size();
    //forEach element of vector
    //if it's number - parse string to double and
    //write it to stack
    //
    //else (for now we do not proccess X,y, etc
    //(we imply in this case this token is actions: + - * /)
    //so else we take 2 numbers from stack
    //and process them

    //Do it again while it's not the end of vector

    for (int i = 0; i <= tokensSize; i++){
        if ( isNumber(tokens[i]) ){
            numbers.push(parseNumber(tokens[i]));
        }
        else{
            char operation = tokens[i][0];
            numbers.push(doAction(getTopElementFromStack(&numbers), operation, getTopElementFromStack(&numbers)));
        }
    }

    return numbers.top(); //last element in stack is the result
}



double doAction(double a, char sign, double b){
    if (sign == '+')
        return a + b;

    if (sign == '-')
        return a - b;

    if (sign == '*')
        return a * b;

    if (sign == '/')
        return a / b;
    else{
        cout<<"error in doAction";
        return -1;
    }

}


double getTopElementFromStack(stack <double > *numbers){
    double res;
    res = numbers->top();
    numbers->pop();
    return res;
}


double parseNumber(string str){
    return atof(str.c_str());
}
