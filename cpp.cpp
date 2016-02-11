#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cerr<<YYERR; cout<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

Sym::Sym(string T,string V) { tag=T; val=V; }
Sym::Sym(string V):Sym("sym",V) {}

void W(Sym*o) { cout << o->dump(); }
void W(string s) { cout << s ; }

string Sym::dump(int depth) { string S = "\n" + pad(depth) + tagval(); 
	return S; }
string Sym::tagval() { return tag+":"+val; }
string Sym::pad(int n) { string S; for (int i=0;i<n;i++) S+='\t'; return S; }

map<string,Sym*> env;
void env_init() {}
