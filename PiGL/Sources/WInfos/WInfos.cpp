//
//  WInfos.cpp
//  PiGL
//
//  Created by Alex Sb on 12/07/2019.
//  Copyright © 2019 Alex Sb. All rights reserved.
//

#include "WInfos.hpp"

WInfos::WInfos() :
    width(DEFAULT_WINDOW_WIDTH),
    height(DEFAULT_WINDOW_HEIGHT),
    title(DEFAULT_WINDOW_TITLE),
    context_version_major(3),
    context_version_minor(1)
{ /* ... */ }

WInfos::WInfos(const int& width, const int& height, const std::string& title, const int& context_version_major, const int& context_version_minor) :
width(width <= 1 ? DEFAULT_WINDOW_WIDTH : width),
    height(height <= 1 ? DEFAULT_WINDOW_HEIGHT : height),
    title(title == "" || title == " " ? DEFAULT_WINDOW_TITLE : title),
    context_version_major(context_version_major),
    context_version_minor(context_version_minor)
{ /* ... */ }
