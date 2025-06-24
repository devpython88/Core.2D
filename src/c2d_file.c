#include "core2d.h"


IoFile *OpenFile(const char *path, const char *mode)
{
    IoFile* file = (IoFile*)malloc(sizeof(IoFile));
    if (file == NULL){
        Err("Could not allocate file: %s", path);
        return NULL;
    }

    FILE* cfile = fopen(path, mode);
    if (cfile == NULL){
        Err("Could not open file: %s", path);
        return NULL;
    }

    file->cfile = cfile;
    file->path = (char*)path;
    return file;
}

void FileAppend(IoFile *file, const char *text)
{
    if (file == NULL) return;
    
    fputs(text, file->cfile);
}

long GetFileSize(IoFile *file)
{   
    if (file == NULL) return -1;
    
    FileSeek(file, SEEK_END);
    long size = GetFileCursorPos(file);
    FileRewind(file);
    return size;
}

long GetFileCursorPos(IoFile *file)
{
    if (file == NULL) return -1;
    return ftell(file->cfile);
}

void CloseFile(IoFile *file)
{
    fclose(file->cfile);
    free(file);
}

void FileSeek(IoFile *file, int origin)
{
    if (file == NULL) return;
    fseek(file->cfile, 0, origin);
}

void FileSeekEx(IoFile *file, int offset, int origin)
{
    if (file == NULL) return;
    fseek(file->cfile, offset, origin);
}

void FileRewind(IoFile *file)
{
    if (file == NULL) return;
    rewind(file->cfile);
}

char *FileRead(IoFile *file)
{
    long size = GetFileSize(file);
    if (size < 0) return NULL;

    char* buffer = (char*)malloc(size + 1);
    if (buffer == NULL){
        Err("Buffer allocation failed for file: %s", file->path);
        return NULL;
    }

    size_t bytesRead = fread(buffer, 1, size, file->cfile);
    buffer[bytesRead] = '\0';

    return buffer;
}

int QuickFileWrite(const char *path, const char *text)
{
    IoFile* file = OpenFile(path, "w");
    if (file == NULL) return 1;

    FileAppend(file, text);
    CloseFile(file);

    return 0;
}

char *QuickFileRead(const char *path)
{
    IoFile* file = OpenFile(path, "r");

    if (file == NULL) return NULL;

    char* text = FileRead(file);

    CloseFile(file);
    return text; // will return null if the text is null
}
