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
	string dump(int depth=0); string pad(int);
	virtual string tagval(); string tagstr();
	vector <Sym*> nest; void push(Sym*);
	map<string,Sym*> par;
	virtual Sym* eval();
	virtual Sym* eq(Sym*);
	virtual Sym* at(Sym*);
};

extern map<string,Sym*> env;
extern void env_init();

extern void W(Sym*);
extern void W(string);

struct Str: Sym { Str(string); string tagval(); };

struct List: Sym { List(); };

struct Op: Sym { Op(string); };
struct opEq: Op { opEq(string); Sym*eval(); } ;
struct opAt: Op { opAt(string); Sym*eval(); } ;
struct opColon: Op { opColon(string); Sym*eval(); } ;
struct opAdd: Op { opAdd(string); Sym*eval(); } ;
struct opDiv: Op { opDiv(string); Sym*eval(); } ;

typedef Sym*(*FN)(Sym*);
struct Fn: Sym { Fn(string,FN); FN fn; Sym*at(Sym*); };

struct Lambda: Sym { Lambda(); };

struct Dir: Sym { Dir(Sym*); };
struct File: Sym { File(Sym*); };

extern int yylex();
extern int yylineno;
extern char* yytext;
#define TOC(C,X) { yylval.o = new C(yytext); return X; }
extern int yyparse();
extern void yyerror(string);
#include "ypp.tab.hpp"

#endif // _H_EVALON
