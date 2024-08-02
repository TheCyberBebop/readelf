#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define LS_PATH "/usr/bin/ls"
#define EI_NIDENT 16

#define EI_CLASS 0x04
#define EI_DATA 0x05
#define EI_VERSION 0x06
#define EI_OSABI 0x07
#define EI_ABIVERSION 0x08
#define EI_PAD 0x09

#define EI_CLASS32 1
#define EI_CLASS64 2

#define EI_DATALSB 1
#define EI_DATAMSB 2

#define EI_OSABI0 0x00
#define EI_OSABI1 0x01
#define EI_OSABI2 0x02
#define EI_OSABI3 0x03
#define EI_OSABI4 0x04
#define EI_OSABI5 0x05
#define EI_OSABI6 0x06
#define EI_OSABI7 0x07
#define EI_OSABI8 0x08
#define EI_OSABI9 0x09
#define EI_OSABIA 0x0A
#define EI_OSABIB 0x0B
#define EI_OSABIC 0x0C
#define EI_OSABID 0x0D
#define EI_OSABIE 0x0E
#define EI_OSABIF 0x0F
#define EI_OSABI10 0x10
#define EI_OSABI11 0x11
#define EI_OSABI12 0x12
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

void printMagic(void *elf_header)
{
    printf("\n  Magic:%3s", " ");

    for (int32_t i = 0; i < EI_NIDENT; i++)
    {
        printf("%02x ", ((uint8_t *)elf_header)[i]);
    }
}

void printClass(uint8_t ei_class)
{
    switch (ei_class)
    {
    case EI_CLASS32:
        // TODO
    case EI_CLASS64:
        printf("\n  Class:%34s", "ELF64");
        break;
    default:
        printf("ERROR!");
    }
}

void printData(uint8_t ei_data)
{
    switch (ei_data)
    {
    case EI_DATALSB:
        printf("\n  Data:%30c2's complement, little endian", ' ');
        break;
    case EI_DATAMSB:
        // TODO
    default:
        printf("ERROR!");
    }
}

void printVersion(uint8_t ei_version)
{
    1 == ei_version ? printf("\n  Version:%38s", "1 (current)") : printf("\nERROR");
}

const char* getOsabi(uint8_t ei_osabi)
{
    switch (ei_osabi)
    {
        case EI_OSABI0:
            return "System V";
        // TODO the rest
        default:
            return "ERROR";
    }
}

void printOsabi(uint8_t ei_osabi)
{
    printf("\n  OS/ABI:%28sUNIX - %s", " ", getOsabi(ei_osabi));
}

void printElfHeader(void *elf_header)
{
    printf("ELF Header:");
    printMagic(elf_header);
    printClass(((uint8_t *)elf_header)[EI_CLASS]);
    printData(((uint8_t *)elf_header)[EI_DATA]);
    printVersion(((uint8_t *)elf_header)[EI_VERSION]);
    printOsabi(((uint8_t *)elf_header)[EI_OSABI]);
}

int main()
{
    int32_t ret = 0;
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
        fclose(fd);
        return -1;
    }
    memset(elf_header, 0, sizeof(elf32_header));

    ret = fread(elf_header, 1, sizeof(elf32_header), fd);
    if (sizeof(elf32_header) != ret)
    {
        fclose(fd);
        return -1;
    }
    fclose(fd);

    printElfHeader(elf_header);

    free(elf_header);

    return 0;
}