//
//  Layer.h
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#ifndef __LAYER_H__
#define __LAYER_H__

#include "Node.h"

class Layer : public Node {
public:
    virtual bool init() { return true; }
    virtual void release();
};

#endif