title: Home
symbol: :home
---

# S2

S2 is a language that describes binary data structures. It compiles to a variety of languages into code that allows a person to create, read, modify and write any given data structure to a binary file in those languages.

The following is a simple example of an S2 file

```csharp
import "base"

struct NumberList
{
    Uint32 magic = 'NUML'
    Uint32 numberCount
    Uint32[numberCount] numbers
}
```


This translates to an API that can be used to read and write the NumberList to a file, or even create a new one

---

### In C:

```c
/* read a file */
NumberList* numList; 

FILE* source = fopen("numberlist", "rb");
S2ERROR err = ReadNumberList(source, &numList);
if (err != S2_NO_ERROR) { printf("error!\n"); return; }
fclose(source);

/* read its contents */
ArrayOfUint32* arr;
err = GetNumberList_numbers(numList, &arr);
if (err != S2_NO_ERROR) { printf("error!\n"); return; }

/* modify its contents */
err = ArrayOfUint32_push(arr, 5);
if (err != S2_NO_ERROR) { printf("error!\n"); return; }

/* write a file */
FILE* dest = fopen("numberlist2", "wb");
err = WriteNumberList(dest, numList);
if (err != S2_NO_ERROR) { printf("error!\n"); return; }
fclose(dest);

/* free it */
DeleteNumberList(numList);
```

---

### In C++:

```cpp
// read a file
std::ifstream source ("numberlist", ios::binary);
std::shared_ptr<NumberList> numList = std::make_shared<NumberList>(source);

// modify its contents
numList->numbers()->push_back(5);

// write a file
std::ofstring dest("numberlist2", ios::binary);
numList->write(dest);
```

---

### In Ruby:

```ruby
# read a file
numList = NumberList::from_file("numberlist")

# modify its contents
numList.numbers << 5

# write a file
numList.to_file("numberlist2")
```

---


### In JavaScript:

```javascript
// read a file
var numList = NumberList.from_file("numberList")

// modify its contents
numList.get_numbers().push(5)

// write a file
numList.to_file("numberlist2")
```

---
# Inspiration

S2 was inspired by the fact that you can create a struct in C and read it using fread:

```clike
#pragma pack(push,1)

typedef struct {
    uint32_t number1;
    int32_t reserved;
} SomeStruct;

#pragma pack(pop)

void read(FILE* fp)
{
    SomeStruct s;
    fread(fp, &s, sizeof(SomeStruct));
    printf("%d\n", s.number1);
}
```

However this is only usable if the structure was a fixed size. Members could not have varying sizes and arrays had to have a fixed size. This was not true of real-world binary file formats. So I set out to create a way to read files as if it was an `fread` while preserving the declarative nature of a struct declaration.

---

# Addendum

### Naming universality

You may notice that there are some very specific syntax that is imposed on you in S2. This is because this language needs to compile to other languages and be usable there, so the names and tokens that need to be recognizable in the target languages need to also be compatible with the target languages and be easily readable in them.

### No null

* NULL here refers to `NULL`/`null`/`nil`/`undefined` or whatever a meaningless or uninitialized value is represented as in a target language.

S2 has no support for NULL. While useful in many cases, NULL in the context of different languages often have different meanings in different contexts and introduce many difficulties in implementing a sane and correct API in different target languages.

Instead of NULL, S2 has a policy of using default values. The most basic default values are 0 for the numeric types. Uninitialized structures will simply default to these values internally.

Please see the various languages' APIs to find out details on how uninitialized fields are handled in S2.
