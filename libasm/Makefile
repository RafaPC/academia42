NAME = libasm
SRCS = ft_strlen.asm ft_write.asm ft_read.asm ft_strcmp.asm
OBJS = ${SRCS:.asm=.o}

all:
	rm -rf *.o
	nasm -f elf64 ft_write.asm
	nasm -f elf64 ft_strlen.asm
	nasm -f elf64 ft_read.asm
	nasm -f elf64 ft_strcmp.asm
	gcc main.c ${OBJS} -o ${NAME}

clean:
	rm -f ${NAME}
	rm -f *.o