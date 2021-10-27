#ifndef TEXTURE_DAT_H
#define TEXTURE_DAT_H

struct TextureData
{
    TextureData(int x, int y, int w, int h) {x = x; y = y; width = w; height = h;};
    int x;
    int y;
    int width;
    int height;
};

#endif