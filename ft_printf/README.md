# ft_printf
The first project in 42's algorithms branch, in spite of not using any sort of algorithm.

The goal of this project is to recode some of the system's printf's functionality.  The conversions this version must replicate are:

`sSpdDioOuUxXcC`

This project must also handle most flags, such as:

`#0-+` and space

and 
```
h
hh
l
ll
j
z
```

Precision and width are handled, as is `%%`.  Wildcard input `*` is implemented for precision and width as well.

## Usage
Run make and the `libftprintf.a` library will be created.  Include the library in whatever program is being compiled.  The function can be called with `ft_printf()` and used as the regular printf command.
#### Note
I am updating this repository with new functions to be used in my library, found in the directory `libft`.
