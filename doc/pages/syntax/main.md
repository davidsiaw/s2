title: Syntax
symbol: :file
---

In its most basic form, S2 structures look like this:

```csharp
struct Name
{
    Uint32 aField
    Uint32 anotherField
}
```

They have a `Name` that must always start with an uppercase. This name is the datatype that is being defined. 

They have fields that are defined as a datatype followed by the field name. They can have any number of fields.

Datatypes always start with an uppercase.

Field names always start with a lowercase.

There are more general rules to this but this is how they are for now.

---

S2 structures can have attributes, for example:

```csharp
[LittleEndian]
struct Name
{
    Uint32 aField
    Uint32 anotherField
}
```

The attribute is placed in square brackets above the struct keyword. Placing the attribute `[LittleEndian]` here means all the integers in this structure must be read out in little-endian order.

Fields can also have attributes:

```csharp
struct Name
{
    [LittleEndian]
    Uint32 aField

    [BigEndian]
    Uint32 anotherField
}
```

This obviously means that `aField` is encoded in little endian and `anotherField` is encoded as a big endian. 

`[LittleEndian]` and `[BigEndian]` are special attributes that tell the compiler how to read bytes from a stream. They do not impact the way they are stored in memory. By default, all numbers are `[LittleEndian]`

---

You can use a structure in another structure:

```csharp
struct Name
{
    Uint32 aField
    Uint32 anotherField
}

struct Structure
{
    Name thing
    Uint32 number
}
```

In this case you have created a new structure called `Structure` and it contains a field of type `Name`.

---

It is possible to refer to a structure inside itself:

```csharp
struct Name
{
    Name inside
}
```

This is known as a recursive structure. This basically means that a Name exists inside another name.

In a target language this means you can request inside an infinite number of times. We will see why this is useful later.

---