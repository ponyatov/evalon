#ifndef _H_EVALON
#define _H_EVALON

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <vector>
#include <map>
using namespace std;

struct Sym {
	string tag,val;
	Sym(string,string); Sym(string);
	string dump(int depth=0); string pad(int); string tagval();
};

extern map<string,Sym*> env;
extern void env_init();

extern void W(Sym*);
extern void W(string);

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(X) { yylval.o = new Sym(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_EVALON
