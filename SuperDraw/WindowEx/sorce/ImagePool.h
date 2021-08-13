//
//  ImagePool.h
//
//  Created by Oranges.
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __IMAGE_POOL_H__
#define __IMAGE_POOL_H__

#include "WindowEx.h"
using namespace SuperDraw;

#include <map>
#include <string>

class ImagePool {
public:
    static ImagePool* instance;

public:
    Image* loadImage(const std::wstring& fileName);
    void removeImage(const std::wstring& fileName);
    Image* getImage(const std::wstring& fileName);

private:
    std::map<std::wstring, Image*> pool;
};

#endif
