#pragma once
#include "MinecraftUIRenderContext.h"

struct FontEntry
{
public:
    class BitmapFont *font;
};

struct FontList
{
public:
    FontEntry fontEntries[7];
};

struct FontRepository
{
private:
    uintptr_t *font_repository_vtable; //8
    __int64 pad;                       //16
    void *ptrToSelf;                   //24
    void *ptrToSelfSharedPtr;          //32
    __int64 pad2;                      //40

public:
    FontList *fontList;
};

struct MinecraftGame
{
private:
    char padding_256[256];

public:
    FontRepository *fontRepository;

private:
    long padding_272;

public:
    class BitmapFont *Font;

    // private:
    //     char padding_344[64];

    // public:
    //     class BitmapFont *Font2;

    // private:
    //     char padding_416[64];

    // public:
    //     class BitmapFont *Font3;

    // private:
    //     char padding_560[136];

    // public:
    //     class BitmapFont *Font4;

    // private:
    //     char padding_576[464];
private:
    char padding_280[480];

public:
    bool canUseKeys; //0x2F0
};