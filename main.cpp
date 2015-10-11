#include <iostream>
#include <cmath>
#include <vector>
#include <stack>

using namespace std;


// input: written formula
//output: vector of tokens of input formula
vector getTokensFromTheLine(string str);


// input: tokens from string
//output: vector of sorted tokens acording to Polish method
vector makePolishReverse(vector tokens);

// input: vector of sorted tokens acording to Polish method
//output: double result
double calculate(vector tokens);

// input: string with come symbol
//output: if '(' ==> true, else ==> false
bool isOpenParenthesis(string ch);

// input: string with come symbol
//output: if ')' ==> true, else ==> false
bool isCloseParenthesis(string ch);

// input: string with come symbol
//output: if it is number ==> true, else ==> false
bool isNumber(string str);

int main()
{
    String str;
    cout << "enter string" << endl;
    cin >> str;
    double result = calculate( makePolishReverse( getTokensFromTheLine(str) ) );
    cout << "the result is " << result << endl;
    return 0;
}




vector getTokensFromTheLine(string str){
    vector <string> tokens;
    // have to make array of tokens from the formula
    // where each token is next number or symbol such as + - / * in formula
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
    if (ch == '(')
        return true;
    return false;
}

bool isCloseParenthesis(string ch){
    if (ch == ')')
        return true;
    return false;
}

vector makePolishReverse(vector tokens){
    vector <string> newTokenList;
    stack signs;

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
                signs.pop;
            }
            //then remove open parenthesis from stack
            signs.pop;
            //this part works corrctly if only formula is correct, i.e has same number of  '('  and  ')'
        }
        else { //it's a some sign ( + or - or * or / ) for this version of program,
                //so here could be problems if formula has any incorrect symbols
                //this scope is had to be rewritten, because it is totally unflexable and "kostil'"
            if (tokens[i] == '*' || tokens[i] == '/'){
                while  (signs.top() == '/' || signs.top() == '*'){
                    newTokenList.push_back(signs.top);
                    signs.pop();
                }
            signs.push(tokens[i]);
            }

            if (tokens[i] == '+' || tokens[i] == '-'){
                while (signs.top() == '+' || signs.top() == '-' || signs.top() == '/' || signs.top() == '*'){
                    newTokenList.push_back(signs.top);
                    signs.pop();
                }
                signs.push(tokens[i]);
            }
        }

    }

    while(!signs.empty()){
        newTokenList.push_back(signs.top);
        signs.pop();
    }

    return newTokenList;
}


double calculate(tokens){
    std::stack <double> numbers;
    char operation; // can be: + - / *
    //forEach element of vector
    //if (str[0] == 0..9)
    //then it's number, so parse this string to number and push it to stack
    numbers.push(parseNumber(token));

    //else
    //it's  + - / *
    //operation = tokens[i];
    //calculate this operation and push result to stack
    numbers.push(doAction(numbers.pop, operation, numbers.pop));

    //and do it again while there is more tokens
}



doAction(double a, char sign, double b){
    if (sign == '+')
        return a + b;

    if (sign == '-')
        return a - b;

    if (sign == '*')
        return a * b;

    if (sign == '/')
        return a / b;
}
