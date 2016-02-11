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
	Sym(string,string); Sym(string); Sym(Sym*,Sym*);
	string dump(int depth=0); string pad(int); string tagval();
	vector <Sym*> nest; void push(Sym*);
	virtual Sym* eval();
};

extern map<string,Sym*> env;
extern void env_init();

extern void W(Sym*);
extern void W(string);

struct List: Sym { List(); };

struct Op: Sym { Op(string); };
struct opColon: Op { opColon(string); Sym*eval(); } ;
struct opEq: Op { opEq(string); Sym*eval(); } ;

struct Lambda: Sym { Lambda(); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_EVALON
