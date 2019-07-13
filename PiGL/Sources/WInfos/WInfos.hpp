//
//  WInfos.h
//  PiGL
//
//  Created by Alex Sb on 11/07/2019.
//  Copyright © 2019 Alex Sb. All rights reserved.
//

#include <stdio.h>
#include <string>

#ifndef DEFAULT_WINDOW_TITLE
#define DEFAULT_WINDOW_TITLE "No Title!"
#endif

#ifndef DEFAULT_WINDOW_WIDTH
#define DEFAULT_WINDOW_WIDTH 800
#endif

#ifndef DEFAULT_WINDOW_HEIGHT
#define DEFAULT_WINDOW_HEIGHT 600
#endif

#ifndef WInfos_h
#define WInfos_h

struct WInfos {
    
    WInfos();
    WInfos(const int& width, const int& height, const std::string& title, const int& context_version_major, const int& context_version_minor);
    
    /* Window width */
    int width;
    /* Window height */
    int height;
    
    /* Window title */
    std::string title;
    
    /* OpenGL context major version */
    int context_version_major;
    /* OpenGL context minor version */
    int context_version_minor;
    
};

#endif /* WInfos_h */
