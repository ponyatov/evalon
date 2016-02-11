" Language: Evalon
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/evalon

syntax match  Comment	"\v#.*"
syntax match  Comment	"\v\\_+"

syntax region String	start="'" end="'"				" 'string'
syntax match  Type		"\v[()[\]]"						" brackets
syntax match  Keyword	"\v[@+\-*/\^]"					" operators
syntax match  Type		"\v[=:]"
