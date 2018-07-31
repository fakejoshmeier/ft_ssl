# ft_ssl
A program that imitates commands from OpenSSL

The first project in 42's Cryptography branch.

The first part of this project is to imitate message digest functions, such as md5 and sha256.

To run the program, first run `make`, and then `./ft_ssl` with the appropriate command.

Hash algorithms implemented are:
```
md5
sha224
sha256
sha384
sha512
```
Strings can be echoed into the program, or given strings and filenames can be entered as arguments.
Examples:
```
echo "echo" | ./ft_ssl md5
53f31a089339194f333d2e3995dbb05e
```
```
./ft_ssl sha224 -s "quiet" -q
a9fa24b33397f04e631863159b833eaa6a3715dfec1aedc88ceeaa64
```

```
echo "test" | ./ft_ssl sha256 -p
test
f2ca1bb6c7e907d06dafe4687e579fce76b37e4e93b7605022da52d2ccc26fd2
```
```
echo "file" > file
./ft_ssl sha384 -r file
286524f6c6f70271aa31fb3444f33cc9891fb5487c255139d2214a77f8e80430fce9c949815cb621c996a6d56b3a39e7 file
```
```
./ft_ssl sha512 -s "string"
SHA512 ("string") = 2757cb3cafc39af451abb2697be79b4ab61d63d74d85b0418629de8c26811b529f3f3780d0150063ff55a2beee74c4ec102a2a2731a1f1f7f10d473ad18a6a87
```

The program can also take flags as arguments.  Flags for message digest commands are:

`-p` - Echoes STDIN to STDOUT and appends the checksum to the end of the output.

`-q` - Quiet mode: only prints out the Hash.

`-r` - Reverses the printing order, hash first with the original input/filename appended.

`-s` - Signifies a string input.
