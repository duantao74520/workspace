SrcFile = ${wildcard *.cpp} ${wildcard *.c}
TargetFile = ${patsubst %.cpp,%,${SrcFile}} ${patsubst %.c,%,${SrcFile}}

all:${TargetFile}

%:%.c 
	gcc -o $@ $< -lpthread -g 
clean:
	rm -f $(TargetFile)