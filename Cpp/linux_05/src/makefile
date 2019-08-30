### xxx.c---->xxx
SrcFile=$(wildcard *.cpp) $(wildcard *.c) 

TargetFile=$(patsubst %.cpp,%,$(SrcFile)) $(patsubst %.c,%,$(SrcFile))

all:$(TargetFile)

%:%.c
	g++ -o $@ $^ -g

clean:
	rm -f $(TargetFile)