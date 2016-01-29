//
//  main.h
//  project1_AIClass
//
//  Created by Nima Aghli on 1/28/16.
//  Copyright © 2016 Nima Aghli. All rights reserved.
//

#ifndef main_h
#define main_h
#include <iostream>
void captureImage();
void saveImage(std::string path_do_images);
void sendCommand_TMOVETO(int hand,int wrist,int x,int y,int z);
void sendCommand_HOME();
int image_seq;
std::string password;


#endif /* main_h */
