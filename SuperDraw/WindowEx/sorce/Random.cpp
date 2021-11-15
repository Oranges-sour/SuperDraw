//
//  Random.cpp
//
//  Created by Oranges.
//  E-mail 873516725@qq.com
//  Copyright 2021 Oranges. All rights reserved.
//

#include "Random.h"

using namespace std;

unsigned int Random::seed{0};
default_random_engine Random::e{};
random_device Random::rd{};