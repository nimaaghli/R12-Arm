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
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/features2d.hpp"

void captureImage();
cv::Mat saveImage(std::string path_do_images);
void sendCommand_TMOVETO(int hand,int wrist,int x,int y,int z);
void sendCommand_HOME();
std::vector<long> invKinem(double r ,double z);
void captureSave(std::string path);
int  wrist,hand;
int  image_seq;
void sendcommand_AJMA(int hand,int wrist,int elbow,int shoulder,int waist);
std::vector<cv::Point> processimage(cv::Mat img1,cv::Mat img2);
std::vector<float> inverse_kinemetics(int x,int y,int z,int l,int a);
void project1(std::string path_do_images,std::string password);
std::string password;
struct tmove;
double radian_to_degree(double  ENTER);
cv::Point findCenter(cv::Point p1,cv::Point p2);
void scanAndFind();
void scanAndFind();




#endif /* main_h */
