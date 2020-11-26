How to compile
Go to the path and run:
	gcc -Wall -g hwserver.c -lzmq -o hwserver

You need first the warning and optimizations or debugging flags (e.g. -Wall for all warnings, -g for debugging information), 
then the optional preprocessor flags (like -D or -I but you have none of them), 
then the source files, 
and at last the libraries -lzmq (order is relevant: from high level libraries to low level ones) 
and the output option -o hwserver (which could be elsewhere).