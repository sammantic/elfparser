#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <elf.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd, i;
	uint8_t *mem;
	struct stat st;
	char *StringTable, *interp;

	Elf64_Ehdr *ehdr;
	Elf64_Phdr *phdr;
	Elf64_Shdr *shdr;

	if (argc < 2) {
		printf("Usage: %s <executable>\n", argv[0]);
		exit(0);
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0 ) {
		perror("open");
		exit(-1);
	}

	if (fstat(fd, &st) < 0) {
		perror("fstat");
		exit(-1);
	}

	mem = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (mem == MAP_FAILED) {
		perror("mmap");
		exit(-1);
	}

	ehdr = (Elf64_Ehdr *) mem;

	phdr = (Elf64_Phdr *) &mem[ehdr->e_phoff];
	shdr = (Elf64_Shdr *) &mem[ehdr->e_shoff];

	if (mem[0] != 0x7f && strcmp(&mem[1], "ELF")) {
		fprintf(stderr, "%s is not an ELF file\n", argv[1]);
		exit(-1);
	}

	if (ehdr->e_type != ET_EXEC) {
		fprintf(stderr, "%s is not an executable\n", argv[1]);
		exit(-1);
	}

	printf("Program Entry point: 0x%x \n", ehdr->e_entry );

	StringTable = &mem[shdr[ehdr->e_shstrndx].sh_offset];

	printf("Section header list:\n\n");

	for (i = 1; i < ehdr->e_shnum; i++)
	{
		printf("%s: 0x%x\n", &StringTable[shdr[i].sh_name], shdr[i].sh_addr );

	}

	printf("\nProgram header list\n\n");

	for (i = 0; i < ehdr->e_phnum; ++i)
	{
		switch(phdr[i].p_type) {
			case PT_LOAD:
				if (phdr[i].p_offset == 0)
					printf("Text segment: 0x%x\n", phdr[i].p_vaddr);
				else
					printf("Data segment: 0x%x\n", phdr[i].p_vaddr);
				break;
			case PT_INTERP:
				interp = strdup((char *) &mem[phdr[i].p_offset]);
				printf("Interpreter: %s\n", interp);
				break;
			case PT_NOTE:
				printf("Note segment: 0x%x\n", phdr[i].p_vaddr);
				break;
			case PT_DYNAMIC:
				printf("Dynamic segment: 0x%x\n", phdr[i].p_vaddr);
				break;
			case PT_PHDR:
				printf("Phdr segment: 0x%x\n", phdr[i].p_vaddr);
				break;
		}
	}

	exit(0);
}