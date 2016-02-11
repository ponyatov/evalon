#include "hpp.hpp"
#define YYERR "\n\n"<<yylineno<<":"<<msg<<"["<<yytext<<"]\n\n"
void yyerror(string msg) { cerr<<YYERR; cout<<YYERR; exit(-1); }
int main() { env_init(); return yyparse(); }

void W(Sym*o) { cout << o->dump(); }
void W(string s) { cout << s ; }

Sym::Sym(string T,string V) { tag=T; val=V; }
Sym::Sym(string V):Sym("sym",V) {}
Sym::Sym(Sym*A,Sym*B):Sym(A->val,B->val) {}

void Sym::push(Sym*o) { nest.push_back(o); }

string Sym::dump(int depth) { string S = "\n" + pad(depth) + tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }
string Sym::tagval() { return tag+":"+val; }
string Sym::pad(int n) { string S;
	if (n) S+='\\';
	for (int i=0;i<=n-1;i++) S+="___"; 
	return S; }

Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		(*it)=(*it)->eval();
	return this; }

List::List():Sym("[","]") {}

Op::Op(string V):Sym("op",V) {}

opColon::opColon(string V):Op(V) {}
Sym* opColon::eval() { Sym::eval();
	return new Sym(nest[1],nest[0]); }

opEq::opEq(string V):Op(V) {}
Sym* opEq::eval() { Sym::eval();
	assert(nest.size()==2); env[nest[0]->val]=nest[0]; return this; }

Lambda::Lambda():Sym("^","^") {}

map<string,Sym*> env;
void env_init() {}
