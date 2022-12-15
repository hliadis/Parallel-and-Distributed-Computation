# Makefile. If you change it, remember than in makefiles multiple spaces
# ARE NOT EQUIVALENT to tabs. The line after a rule starts with a tab!

#Add any executable you want to be created here.
EXECUTABLES	= ex6 ex7
#This is the compiler to use
CC = gcc

#These are the flags passed to the compiler. Change accordingly
CFLAGS = -Wall

#These are the flags passed to the linker. Nothing in our case
LDFLAGS = -lm


# make all will create all executables
all: $(EXECUTABLES)

# This is the rule to create any executable from the corresponding .c 
# file with the same name.
%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

# make clean will remove all executables, jpg files and the 
# output of previous executions.
clean:
	rm -f $(EXECUTABLES)

# make image will create the output_sobel.jpg from the output_sobel.grey. 
# Remember to change this rule if you change the name of the output file.


