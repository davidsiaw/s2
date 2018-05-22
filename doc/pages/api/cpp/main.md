title: C++
symbol: API
---

## Introduction

The C++ API generated using S2 tries to be as idiomatic in C++ as possible. C++ is used in a wide variety of ways in many different projects, but S2 adheres as much as possible to standard C++ coding style guidelines and requires C++11 or later.

---

## Ownership

All pointers used by S2 are represented by the `std::shared_ptr<T>`. No explicit delete is required. When you assign the contents of a structure to another in S2, S2 will perform deep copies of both structures.

---

## Structures

Structures generated using S2 are exposed as classes. The API uses the `std::shared_ptr<T>` to send and receive pointers.

---

## Arrays

Arrays in C++ use the `std::vector<T>` data type.

---

## Streams

In C++ the `std::istream` and `std::ostream` are used for serialization and deserialization. These can be connected to files, memory and anything that can be written to.

