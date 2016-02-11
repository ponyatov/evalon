" Language: Evalon
" Maintainer: (c) Dmitry Ponyatov <dponyatov@gmail.com>, all rights reserved
" GitHub: https://github.com/ponyatov/evalon

syntax region String	start="'" end="'"					" 'string'
syntax match  Type		"\v[()[\]<>:=]"						" brackets

