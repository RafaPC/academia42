NAME = libasm
SRCS =	ft_strlen.asm	\
		ft_write.asm	\
		ft_read.asm		\
		ft_strcmp.asm	\
		ft_strcpy.asm	\
		ft_strdup.asm

OBJS = ${SRCS:.asm=.o}

all:
	rm -rf *.o
	nasm -f elf64 ft_write.asm
	nasm -f elf64 ft_strlen.asm
	nasm -f elf64 ft_read.asm
	nasm -f elf64 ft_strcmp.asm
	nasm -f elf64 ft_strcpy.asm
	nasm -f elf64 ft_strdup.asm
	gcc main.c ${OBJS} -o ${NAME}

clean:
	rm -f ${NAME}
	rm -f *.o