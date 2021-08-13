#include "ImagePool.h"

#include "Director.h"
#include "WindowEx.h"
using namespace SuperDraw;
using namespace std;

ImagePool* ImagePool::instance = new ImagePool{};

Image* ImagePool::loadImage(const std::wstring& fileName)
{
    auto iter = pool.find(fileName);
    if (iter != pool.end()) return iter->second;
    Image* image = new Image();
    auto drawFactory = Director::instance->getDrawFactory();
    loadIMAGE(image, drawFactory, fileName);
    pool.insert({fileName, image});
    return image;
}

void ImagePool::removeImage(const wstring& fileName)
{
    auto iter = pool.find(fileName);
    if (iter != pool.end()) {
        iter->second->release();
        delete iter->second;
    }
    pool.erase(fileName);
}

Image* ImagePool::getImage(const wstring& fileName)
{
    auto iter = pool.find(fileName);
    if (iter != pool.end()) return iter->second;
    return nullptr;
}
