# xstrtok
String tokeniser

A variant of [strtok(3)](https://man7.org/linux/man-pages/man3/strtok.3.html) which addresses weaknesses in the standard library function:

* Do not modify the first argument.
* Can be used on constant strings.
* Make identity of the delimiting byte available.
