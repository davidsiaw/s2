title: C
symbol: API
---

## Introduction

The C API generated using S2 tries to be as idiomatic in C as possible. While C is used in a very wide variety of ways, the generated code attempts to be as friendly as possible while not losing the advantages of writing code in C, namely not paying for what you do not use. For that reason, it may not conform to the way you use C in your project.

All C functions in S2 return an error code named S2_ERROR and take inputs by value and return outputs by reference.

---

## Ownership

Memory management in C is extremely manual in C. S2's convention is root objects. Whenever you create an object using `Create<Structure Name>`, you own it. All the other pointers you can extract from this structure is owned by the structure itself. Attempting to free any pointers from structures you do not own will result in undefined behavior. Calling `Delete<Structure Name>` on the structure frees any pointers that may have been created during its use.

Hence you should match every call to `Create<Structure Name>` to `Delete<Structure Name>` and copy any data you wish to use beyond the structure's life cycle to structures you have created. To facilitate this, `Copy<Structure Name>` functions are provided to allow you to perform deep copies.

---

## Structures

Structures generated using S2 are exposed as opaque pointers with the name given in the s2 file. Internally, structures are created the way the compiler chooses to, that is to say there is no `#pragma push pack,1` or equivalent. If the compiler defaults to aligning struct members on machine word boundaries then that is the way it is represented in memory.

---

## Arrays

Arrays in C are implemented as a structure containing a buffer, count variable and capacity variable. This means that an empty array structure takes up 12 bytes on a machine where `size_t` is 4.

---

## Streams

The C API operates solely on the `FILE*` pointer. While the most common use case of this is to write to files, it is possible to use it to write to memory as well as network sockets. Please see the POSIX documentation to see how to do this.
