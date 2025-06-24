## File managements in core

core has a simple file api.


## Opening a file
To open a file, simply:

```cpp
IoFile* file = OpenFile("file.txt", "w");
```

The `"w"` is the open-mode, You can learn more about modes since they are just C File operation modes.

## Moving cursor
To move the file cursor

```cpp
FileSeek(file, SEEK_END); // you can replace SEEK_END with wherever you wanna go
// With offset
FileSeekEx(file, 0, SEEK_END);
```


To get the cursor pos

```cpp
long pos = GetFileCursorPos(file);
// Will return -1 if it failed
```

To rewind the cursor back to the start

```cpp
FileRewind(file);
```

## File length
To get the file length,

```cpp
long len = GetFileSize(file);
// will return -1 when failed
```

## Freeing
To free a file, simply call `CloseFile(IoFile*)`

## Reading
To read a file, There are two ways
1. Manual
Open a file, then
```cpp
// will return null on fail
const char* text = FileRead(file);
// Make sure to free after use
free((void*)text);
```


2. Quick
No file opening needed.

```cpp
// will return null on fail
const char* text = QuickFileRead("file.txt");
// make sure to free after use
free((void*)text);
```


## Writing file
There are also two ways of doing this


1. Line by line
Open a file and
```cpp
FileAppend(file, "Some text\n");
```

And when you close the file, it will write the changes

2. Quick
No file opening needed

```cpp
// will return 1 on fail, file must exist beforehand
int result = QuickFileWrite("file.txt", "Some text\n");
```

