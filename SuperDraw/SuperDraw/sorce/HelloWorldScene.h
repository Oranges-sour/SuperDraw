#ifndef __HELLO_WORLD_SCENE_H__
#define __HELLO_WORLD_SCENE_H__

#include <string>

#include "SuperDraw.h"

class HelloWorldScene : public Scene {
public:
    static HelloWorldScene* create();
    virtual bool init() override;
    virtual void release() override;
};

class Layer0 : public Layer {
public:
    static Layer0* create();
    virtual bool init() override;

};
#endif
