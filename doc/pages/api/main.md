title: API
symbol: :file
---

# S2

While S2 is a language, its compiler generates code that is meant to be used in other languages. These pages will describe the APIs generated in each language and describe how to use them.

# Languages

- C
- C++
- Ruby
- JavaScript

# What gets generated

In every language there will be at least 2 modules of APIs generated:

- Object API
- Serialization API

---

## Object API

Using the Object API, you can create, modify and delete (if necessary) objects in a way that is idiomatic to the language

---

## Serialization API

Using the Serialization API, you can read from streams (be it files, network streams, memory streams) and receive objects or write objects created using the object API to streams.

The general flow for reading is then:

1. Obtain a stream from which to read
2. Call the read function on the stream with the format
3. Receive the object

The general flow for writing is thus:

1. Create/obtain an object
2. Obtain a stream to write to
3. Perform some modification to the object
4. Call the write function on the stream
