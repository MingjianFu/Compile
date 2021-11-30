#include<iostream>
#include<fstream>
using namespace std;
void error();
void print();
void program();
void block();
void stmt();
void stmts();
void _bool();
void expr();
void expr1();
void term();
void term1();
void factor();
void match(string str);
string getToken();
string word;
ifstream fin;

int flagerror = 0,flag_error = 0;
void main()
{
    fin.open("Finaltable.txt");
    if (!fin.is_open()) {
        cout << "文件打开失败!\n";
        exit(EXIT_FAILURE);
    }
   
   
        print();
        program();
        fin.close();
        fin.clear();
        if (flagerror == 0)
            cout << "语法分析完成!" << endl;
    
}

void error()
{
    flag_error = 1;
    cout << "出现错误，终止分析！" << endl;
}
void print()
{
    char ch;
    cout << "词法分析结果如下：" << endl;
    fin.get(ch);
    while (!fin.eof()) {
        cout << ch;
        fin.get(ch);
    }
    fin.clear();//file读结束后，eof()返回真值时，file的错误标志被设置为eofbit，于是，后续所有针对file1的操作都不能得到预期的结果，比如tellp、tellg、seekg、seekp等，
    //因此，再进行其他针对file的操作前，   需要清除该错误标志~~~!
    fin.seekg(0);
    

    cout << endl;
    cout << "语法分析过程如下：" << endl;
   
}
void program()
{
   
    word = getToken();
    cout << "program-->block" << endl;
    block();
    if (flagerror == 1)
    {


        error();
        return;
    }
}
void block()
{
    if (flagerror == 1)return;
    cout << "block-->{stmts}" << endl;
    match("{");
    stmts();
    match("}");
}
void stmts()
{
    if (flagerror == 1)return;
    if (word=="}")
    {
        cout << "stmts-->NULL" << endl;
        return;
    }
    cout << "stmts-->stmt stmts" << endl;
    stmt();
    stmts();
}
void stmt()
{
    if (flagerror == 1)return;
    if (word == "id") {
        cout << "stmt-->id=expr;" << endl;
        match("id");
        match("=");
        expr();
        match(";");
    }
    else if (word == "if") {
        match("if");
        match("(");
        _bool();
        match(")");
        stmt();      
        if (word== "else")
        {
            cout << "stmt-->if(_bool)stmt else stmt" << endl;
            match("else");
            stmt();
           
        }
        else
        {
            
            

            cout << "stmt-->if(_bool)stmt" << endl;
        }
    }
    else if(word == "while") {
        cout << "stmt-->while(bool)stmt" << endl;
        match("while");
        match("(");
        _bool();
        match(")");
        stmt();
    }
    else if (word == "do") {
        cout << "stmt-->do stmt while(bool)" << endl;
        match("do");
        stmt();
        match("while");
        match("(");
        _bool();
        match(")");
    }
    else if (word == "break") {
        cout << "stmt-->break" << endl;
        match("break");
    }
    else {
        cout << "stmt-->block" << endl;
        block();
    }
}
void _bool()
{
    if (flagerror == 1)
        return;
    expr();
    if (word == "<") {
        cout << "_bool-->expr<expr" << endl;
        match("<");
        expr();
    }
    else if (word == "<=") {
        cout << "_bool-->expr<=expr" << endl;
        match("<=");
        expr();
    }
    else if (word == ">") {
        cout << "_bool-->expr>expr" << endl;
        match(">");
        expr();
    }
    else if (word == ">=") {
        cout << "_bool-->expr>=expr" << endl;
        match(">=");
        expr();
    }
    else
         cout << "_bool-->expr" << endl;
}
void expr()
{
    if (flagerror == 1)return;
    cout << "expr-->term expr1" << endl;
    term();
    expr1();
}
void expr1()
{
    if (flagerror == 1)return;
    if (word == "+") {
        cout << "expr1-->+ term expr1" << endl;
        match("+");
        term();
        expr1();
    }
    if (word == "-") {
        cout << "expr1-->- term expr1" << endl;
        match("-");
        term();
        expr1();
    }
    else
        cout << "expr1-->NULL" << endl;
        return;
    
}
void term()
{
    if (flagerror == 1)return;
    cout << "term-->factor term1" << endl;
    factor();
    term1();
}
void term1()
{
    if (flagerror == 1)return;
   // switch (finaltableint[finalnum])
    //{
   // case 18:
    //string word = getToken();
    if (word == "*") {
        cout << "term1-->* factor term1" << endl;
        match("*");
        factor();
        term1();
    }
    else if (word == "/") {
    //case 2:
        cout << "term1-->/factor term1" << endl;
        match("/");
        factor();
        term1();
    }
       
    else
        cout << "term1-->NULL" << endl;
        return;
    
}
void factor()
{
    if (flagerror == 1)
        return;
    
    //string word = getToken();
   
    if (word == "(") {
        cout << "factor-->(expr)" << endl;
        match("(");
        expr();
        match(")");
    }
     
   
    else if (word == "id") {
        cout << "factor-->id" << endl;
        match("id");
    }
      
    else if (word == "num") {
        cout << "factor-->num" << endl;
        match("num");
    }
     
    else
        flagerror=1;
       
   
}
void match(string str)
{
   
    if(word!=str)

    {
        flagerror = 1;
        return;
    }
    word = getToken();
   
}
string getToken() {
    
    string str="";
    char ch;
    fin.get(ch);
    

    if (ch == '\n') { fin.get(ch); }//跳过换行符
    while (ch != ' '&&!fin.eof()) {      
        str += ch;
        fin.get(ch);
        
    }
   
    return str;
}
