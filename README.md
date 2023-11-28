# Pipex
Pipex is a project that reproduces the behaviour of the shell pipe | command in C, using the pipe() , fork() , dup2() and execve() functions. The program will launch as ./pipex infile cmd1 cmd2 outfile and behave exactly as this line in the shell &lt; infile cmd1 | cmd2 > outfile .
