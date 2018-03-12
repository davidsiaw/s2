title: Using S2
symbol: :file
---

# Installing
S2 is mostly a command line tool but it is distributed as a Ruby gem. To install, simply go

```bash
gem install "s2"
```

---

# Using
S2 is a code generator, so depending on the code you want to generate, you provide a parameter for generation in the form of `s2c <filename> <flag> [options]`.

```bash
s2c mystruct.s2 c > mystruct.c
```

Available flags are:

| Result          | flag   |
| --------------- | ------ |
| c header        |  h     |
| c source        |  c     |
| c++ header      |  hpp   |
| c++ source      |  cpp   |
| ruby            |  ruby  |
| javascript      |  js    |

The output is sent to stdout, so you want to pipe it into a file of your choosing.

The options are optional and differ according to the flag.
