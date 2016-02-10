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
void captureSave(std::string path);
int  wrist,hand;
int  image_seq;
void sendcommand_AJMA(int hand,int wrist,int elbow,int shoulder,int waist);
std::vector<float> inverse_kinemetics(int x,int y,int z,int l,int a);
std::string password;
struct tmove;
std::string path_do_images;


#endif /* main_h */
