//
//  ImagePool.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __IMAGE_POOL_H__
#define __IMAGE_POOL_H__

#include "WindowEx.h"

#include <map>
#include <string>

class ImagePool {
public:
    static ImagePool* instance;

    ImagePool() = default;
    ~ImagePool();

public:
    WindowEx::Image* loadImage(const std::wstring& fileName);
    void removeImage(const std::wstring& fileName);
    WindowEx::Image* getImage(const std::wstring& fileName);

private:
    std::map<std::wstring, WindowEx::Image*> pool;
};

#endif
