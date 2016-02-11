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
	for (auto pr=par.begin(),e=par.end();pr!=e;pr++)
		S += ","+ pr->first+":"+pr->second->tagval();
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		S += (*it)->dump(depth+1);
	return S; }
string Sym::tagval() { return tag+":"+val; }
string Sym::tagstr() { return tag+":'"+val+"'"; }
string Sym::pad(int n) { string S;
	if (n) S+='\\';
	for (int i=0;i<=n-1;i++) S+="___"; 
	return S; }

Sym* Sym::eval() {
	Sym*E = env[val]; if (E) return E;
	for (auto it=nest.begin(),e=nest.end();it!=e;it++)
		(*it)=(*it)->eval();
	return this; }

Sym* Sym::eq(Sym*o) { o->par["var"]=this; env[val]=o; return o; }
//	Sym*R = new opEq("=");
//	env[val]=this;
//	R->push(this); R->push(o); return R; }
Sym* Sym::at(Sym*o) { Sym*R = new opAt("@");
	R->push(this); R->push(o); return R; }

Str::Str(string V):Sym("str",V) {}
string Str::tagval() { return tagstr(); }

List::List():Sym("[","]") {}

Op::Op(string V):Sym("op",V) {}

opEq::opEq(string V):Op(V) {}
Sym* opEq::eval() { Sym::eval();
	assert(nest.size()==2); return nest[0]->eq(nest[1]); }

opAt::opAt(string V):Op(V) {}
Sym* opAt::eval() { Sym::eval();
	assert(nest.size()==2); return nest[0]->at(nest[1]); }

opColon::opColon(string V):Op(V) {}
Sym* opColon::eval() { Sym::eval();
	assert(nest.size()==2); return this;}//new Sym(nest[1],nest[0]); }

opAdd::opAdd(string V):Op(V) {}
Sym* opAdd::eval() { Sym::eval();
	assert(nest.size()==2); return this; }

opDiv::opDiv(string V):Op(V) {}
Sym* opDiv::eval() { Sym::eval();
	assert(nest.size()==2); return this; }

Fn::Fn(string V, FN F):Sym("fn",V) { fn=F; }
Sym* Fn::at(Sym*o) { return fn(o); }

Lambda::Lambda():Sym("^","^") {}

Dir::Dir(Sym*o):Sym("dir",o->val) {}
Sym* dir(Sym*o) { return new Dir(o); }

File::File(Sym*o):Sym("file",o->val) {}
Sym* file(Sym*o) { return new File(o); }

Sym* var(Sym*o) { return new Sym("var",o->val); }

map<string,Sym*> env;
void env_init() {
	env["dir"] = new Fn("dir",dir);
	env["file"] = new Fn("file",file);
	env["var"] = new Fn("var",var);
}
