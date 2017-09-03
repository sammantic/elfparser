# Elfparser

its simple parser which analysis Executable and Linkable formate "ELF".

## Compile
```sh
$ gcc elfparser.c -o elfparser
```
## Usage
```sh
$./elfparser <excutable file>
```

## output
```sh
$./elfparser hello
Program Entry point: 0x400430 
Section header list:

.interp: 0x400238
.note.ABI-tag: 0x400254
.note.gnu.build-id: 0x400274
.gnu.hash: 0x400298
.dynsym: 0x4002b8
.dynstr: 0x400318
.gnu.version: 0x400356
.gnu.version_r: 0x400360
.rela.dyn: 0x400380
.rela.plt: 0x400398
.init: 0x4003c8
.plt: 0x4003f0
.plt.got: 0x400420
.text: 0x400430
.fini: 0x4005b4
.rodata: 0x4005c0
.eh_frame_hdr: 0x4005d0
.eh_frame: 0x400608
.init_array: 0x600e10
.fini_array: 0x600e18
.jcr: 0x600e20
.dynamic: 0x600e28
.got: 0x600ff8
.got.plt: 0x601000
.data: 0x601028
.bss: 0x601038
.comment: 0x0
.shstrtab: 0x0
.symtab: 0x0
.strtab: 0x0

Program header list

Phdr segment: 0x400040
Interpreter: /lib64/ld-linux-x86-64.so.2
Text segment: 0x400000
Data segment: 0x600e10
Dynamic segment: 0x600e28
Note segment: 0x400254
```
## Author
* **Mohammed Alsamman** - Sammantic4@gmail.com 

