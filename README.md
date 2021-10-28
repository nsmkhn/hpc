# Multithreading Demo
Given a file in [XML format](https://en.wikipedia.org/wiki/XML) whose name is passed as an argument to a program. Count the number of unique prime numbers within intervals specified in a file.

## Build
Dependencies: [boost property tree xml parser](https://www.boost.org/doc/libs/1_52_0/doc/html/boost_propertytree/parsers.html#boost_propertytree.parsers.xml_parser)

### macOS
```console
$ brew install boost
$ make -Bj
```

### Debian
```console
$ sudo apt-get install libboost-all-dev
$ make -Bj
```

## Usage
```console
$ ./mt <file>
```

## Sample Input File
```xml
<root>
  <intervals>
    <interval>
      <left_bound>-1000</left_bound>
      <right_bound>500000</right_bound>
    </interval>
    <interval>
      <left_bound>400000</left_bound>
      <right_bound>1000000</right_bound>
    </interval>
    <interval>
      <left_bound>800000</left_bound>
      <right_bound>1500000</right_bound>
    </interval>
    <interval>
      <left_bound>1200000</left_bound>
      <right_bound>2000000</right_bound>
    </interval>
    <interval>
      <left_bound>1900000</left_bound>
      <right_bound>3000000</right_bound>
    </interval>
    <interval>
      <left_bound>2900000</left_bound>
      <right_bound>3500000</right_bound>
    </interval>
    <interval>
      <left_bound>3400000</left_bound>
      <right_bound>4000000</right_bound>
    </interval>
    <interval>
      <left_bound>3900000</left_bound>
      <right_bound>4600000</right_bound>
    </interval>
  </intervals>
</root>
```
