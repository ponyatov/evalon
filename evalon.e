
# comment

file@.gitignore = [
*~
*.swp
*.exe
*.*log
ypp.tab.?pp
lex.yy.c
]

files = [
	e.e
	log.log
	ypp.ypp
	lpp.lpp
	hpp.hpp
	cpp.cpp
	Makefile
]

skeleton = [
	files
	bat.bat
	.gitignore
	filetype.vim
	syntax.vim
]

bat.bat = '@start.\n@gvim -p '+files/' '

next = dir@'next' + skeleton
#next = [ next bat.bat ]
