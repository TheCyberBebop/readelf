#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define LS_PATH "/usr/bin/ls"
#define EI_NIDENT 16

typedef struct elf32_header
{
    uint8_t e_ident[EI_NIDENT];
    uint16_t e_type;
    uint16_t e_machine;
    uint32_t e_version;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} elf32_header;

int main()
{
    int ret = 0;
    void *elf_header = NULL;
    FILE *fd = NULL;

    fd = fopen(LS_PATH, "rb");
    if (NULL == fd)
    {
        return -1;
    }

    elf_header = (elf32_header *)malloc(sizeof(elf32_header));
    if (NULL == elf_header)
    {
        return -1;
    }
    memset(elf_header, 0, sizeof(elf32_header));

    // TODO: Error check ret
    fread(elf_header, 1, sizeof(elf32_header), fd);

    return 0;
}