//
//  main.cpp
//  project1_AIClass
//
//  Created by Nima Aghli on 1/28/16.
//  Copyright © 2016 Nima Aghli. All rights reserved.
//  This app uses curl lib to send http commands

#include <iostream>
#include <curl/curl.h>
#include <vector>
#include "main.h"
#include <cmath>

#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;


int main(int argc, const char * argv[]) {
    string path_do_images="/Users/nimaaghli/Documents/Couraea/AiRobotics/project1_AIClass/project1_AIClass/img/";
    password="NAhuygi6djgovuyv";
    //password="ESjdvkasfalkgd";//SHAKERI
    //password="SMkgbku6tc4hxwy";//Mahdi
    
    password="YMBkbo3yb3b3b3p";
    
    if(argc<3){
        printf("Not enough Parameters\n");
        printf("Template ./arm <password> <path to images to save>\n");
        //return 0;
        
    }
    else {
        password=argv[1];
        path_do_images=argv[2];
    }
    //sendCommand_TMOVETO(3000,-7950, -3900, 0, 2000);
    //captureImage();
    //saveImage(path_do_images);
    //project1(path_do_images, password);
    Mat model=imread(path_do_images+"model.png");
    Mat image=imread(path_do_images+"image8.BMP");
    processimage(model, image);
    return 0;
}


void captureImage(){
    CURL *curl;
    CURLcode res;
    string command="p="+password+"&c=1 CAPTURE";
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    printf("comamnd is = %s\n",command.c_str());
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        curl_easy_setopt(curl, CURLOPT_URL, "http://debatedecide.fit.edu/robot.php?o=369");
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, command.c_str());
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    
    
}
void saveImage(string path){
    CURL *image;
    CURLcode imgresult;
    FILE *fp;
    image_seq +=1;
    image = curl_easy_init();
    
    string image_name="image";
    image_name =path+image_name+to_string(image_seq)+".BMP";
    printf("%s",image_name.c_str());
    fp = fopen(image_name.c_str(), "wp");
    
    if( image ){
        
        if( fp == NULL ) cout << "File cannot be opened";
        
        curl_easy_setopt(image, CURLOPT_URL, "http://debatedecide.fit.edu/robot/last.bmp");
        curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(image, CURLOPT_WRITEDATA, fp);
        
        // Grab image
        imgresult = curl_easy_perform(image);
        if( imgresult ){
            cout << "Cannot grab the image!\n";
        }
    }
    
    // Clean up the resources
    curl_easy_cleanup(image);
    // Close the file
    fclose(fp);
    
    
}


void sendCommand_TMOVETO(int hand,int wrist,int x,int y,int z){
    CURL *curl;
    CURLcode res;
    string command;
    command ="p="+password+"&c="+to_string(hand)+" "+to_string(wrist)+" "+to_string(x)+" "+to_string(y)+" "+to_string(z)+" "+"TMOVETO";
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    printf("comamnd is = %s\n",command.c_str());    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        curl_easy_setopt(curl, CURLOPT_URL, "http://debatedecide.fit.edu/robot.php?o=369");
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, command.c_str());
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    
}


void sendCommand_HOME(){
    
    CURL *curl;
    CURLcode res;
    string command="p="+password+"&c=HOME";
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    printf("comamnd is = %s\n",command.c_str());
    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "http://debatedecide.fit.edu/robot.php?o=369");
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, command.c_str());
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void captureSave(string path){
    saveImage(path);
    captureImage();
    
}

void sendcommand_AJMA(int hand,int wrist,int elbow,int shoulder,int waist){
    CURL *curl;
    CURLcode res;
    string command;
    command ="p="+password+"&c="+to_string(hand)+" "+to_string(wrist)+" "+to_string(elbow)+" "+to_string(shoulder)+" "+to_string(waist)+" "+"AJMA";
    /* In windows, this will init the winsock stuff */
    curl_global_init(CURL_GLOBAL_ALL);
    printf("comamnd is = %s\n",command.c_str());    /* get a curl handle */
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. This URL can
         just as well be a https:// URL if that is what should receive the
         data. */
        curl_easy_setopt(curl, CURLOPT_URL, "http://debatedecide.fit.edu/robot.php?o=369");
        /* Now specify the POST data */
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, command.c_str());
        
        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

vector<float> inverse_kinemetics(int x,int y,int z,int l,int a){ // THIS FUNCTION WILL BE USED ON LATER PROJECT
    
    vector<float> res;
    double d;
    float p=3.14159265;
    d=sqrt(x^2+y^2+((a+z)^2));
    float q1,q2,q3=0;
    float q22=acos(float(z)/float(d))*180/p;
    printf("q22 =%f d=%f\n",q22,d);
    q2=acos(((float(d)/2)/float(l)))*180/p;
    printf("q2 =%f\n",q2);
    q1=180-(2*q2);
    printf("q1 =%f\n",q1);
    q3=atan(float(x)/float(y))*180/p;
    printf("q3 =%f\n",q3);
    
    res.push_back(q1);
    res.push_back(q2);
    res.push_back(q3);
    return res;
    
}

vector<cv::Point> processimage(cv::Mat img1,cv::Mat img2){
    vector<cv::Point> corners;
    Mat img_object;
    Mat img_scene;
    cv::cvtColor(img1, img_object, CV_BGR2GRAY);
    cv::cvtColor(img2, img_scene, CV_BGR2GRAY);

if( !img_object.data || !img_scene.data )
{ std::cout<< " --(!) Error reading images " << std::endl; }
    
    //-- Step 1: Detect the keypoints using SURF Detector
    int minHessian = 400;
    
    SurfFeatureDetector detector( minHessian );
    
    std::vector<KeyPoint> keypoints_object, keypoints_scene;
    
    detector.detect( img_object, keypoints_object );
    detector.detect( img_scene, keypoints_scene );
    
    //-- Step 2: Calculate descriptors (feature vectors)
    SurfDescriptorExtractor extractor;
    
    Mat descriptors_object, descriptors_scene;
    
    extractor.compute( img_object, keypoints_object, descriptors_object );
    extractor.compute( img_scene, keypoints_scene, descriptors_scene );
    
    //-- Step 3: Matching descriptor vectors using FLANN matcher
    FlannBasedMatcher matcher;
    std::vector< DMatch > matches;
    matcher.match( descriptors_object, descriptors_scene, matches );
    
    double max_dist = 0; double min_dist = 100;
    
    //-- Quick calculation of max and min distances between keypoints
    for( int i = 0; i < descriptors_object.rows; i++ )
    { double dist = matches[i].distance;
        if( dist < min_dist ) min_dist = dist;
        if( dist > max_dist ) max_dist = dist;
    }
    
    printf("-- Max dist : %f \n", max_dist );
    printf("-- Min dist : %f \n", min_dist );
    
    //-- Draw only "good" matches (i.e. whose distance is less than 3*min_dist )
    std::vector< DMatch > good_matches;
    
    for( int i = 0; i < descriptors_object.rows; i++ )
    { if( matches[i].distance < 3*min_dist )
    { good_matches.push_back( matches[i]); }
    }
    
    Mat img_matches;
    drawMatches( img_object, keypoints_object, img_scene, keypoints_scene,
                good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
                vector<char>(), DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );
    
    
    //-- Localize the object from img_1 in img_2
    std::vector<Point2f> obj;
    std::vector<Point2f> scene;
    
    for( size_t i = 0; i < good_matches.size(); i++ )
    {
        //-- Get the keypoints from the good matches
        obj.push_back( keypoints_object[ good_matches[i].queryIdx ].pt );
        scene.push_back( keypoints_scene[ good_matches[i].trainIdx ].pt );
    }
    
    Mat H = findHomography( obj, scene, CV_RANSAC );
    //-- Get the corners from the image_1 ( the object to be "detected" )
    std::vector<Point2f> obj_corners(4);
    obj_corners[0] = Point(0,0); obj_corners[1] = Point( img_object.cols, 0 );
    obj_corners[2] = Point( img_object.cols, img_object.rows ); obj_corners[3] = Point( 0, img_object.rows );
    std::vector<Point2f> scene_corners(4);
    
    perspectiveTransform( obj_corners, scene_corners, H);
    
    
    //-- Draw lines between the corners (the mapped object in the scene - image_2 )
    Point2f offset( (float)img_object.cols, 0);
    //int c1_x,c1_y,c2_x,c2_y,c3_x,c3_y,c4_x,c4_y;
    //corners[0]=scene_corners[0];
    //corners[1]=scene_corners[1];
    //corners[2]=scene_corners[2];
    //corners[3]=scene_corners[3];
    printf("valuse is = %f and %f\n",scene_corners[0].x ,scene_corners[0].y);
    printf("valuse is = %f and %f\n",scene_corners[1].x ,scene_corners[1].y);
    printf("valuse is = %f and %f\n",scene_corners[2].x ,scene_corners[2].y);
    printf("valuse is = %f and %f\n",scene_corners[3].x ,scene_corners[3].y);
    
    line( img_matches, scene_corners[0] + offset, scene_corners[1] + offset, Scalar(255, 255, 0), 4 );
    line( img_matches, scene_corners[1] + offset, scene_corners[2] + offset, Scalar( 0, 255, 0), 4 );
    line( img_matches, scene_corners[2] + offset, scene_corners[3] + offset, Scalar( 0, 255, 0), 4 );
    line( img_matches, scene_corners[3] + offset, scene_corners[0] + offset, Scalar( 0, 255, 0), 4 );
    
    //-- Show detected matches
    imshow( "Good Matches & Object detection", img_matches );
    
    imwrite( path_do_images+ "Gray_Image.jpg", img_matches );
    
    waitKey(0);
    return corners;
    
}


void project1(string path_do_images,string password){
    
    
    
    bool flag=true;
    int fix;
    vector<int> numbers={-4100,-4100,-4600};
    
    
    
    //vector<float> res=inverse_kinemetics(-2400,-1600,1000, 2500, 2230);
    //<HAND_ANGLE> <WRIST_ANGLE> <ELBOW_ANGLE> <SHOULDER_ANGLE> <WAIST_ANGLE>
    //printf("q1=%d,q2=%d,q3=%d",res.at(0)*100,res.at(1)*100,res.at(2)*100);
    //sendcommand_AJMA(-11500,-7000,res.at(0)*10,res.at(1)*10,res.at(2)*10);
    //saveImage(path_do_images);
    //captureImage();
    //captureSave(path_do_images);
    //sendCommand_HOME();
    sendCommand_TMOVETO(3000,-5950, -2000, -1600, 100);
    /*for(int i=-1831;i<=-1031;i+=200){
     printf("+++i=%d\n",i);
     if(flag){
     fix=-2520;
     for(int j=-180;j>=-1000;j-=100){
     //sendCommand_TMOVETO(3000,-1050, -2952, -280, -1831);
     printf("j=%d,fix=%d",j,fix);
     flag=false;
     sendCommand_TMOVETO(3000,-1850, fix, j, i);//-2620
     captureSave(path_do_images);
     fix+=18;
     }
     }
     
     else {
     fix=-2376;
     for(int j=-1000;j<=-180;j+=100){
     //sendCommand_TMOVETO(3000,-1050, -2952, -280, -1831);
     printf("j=%d",j);
     flag=true;
     sendCommand_TMOVETO(3000,-1850, fix, j, i);
     captureSave(path_do_images);
     fix-=18;
     }
     }
     
     printf("\n");
     }*/
    sendCommand_TMOVETO(3000,-5950, -2500, -1600, 100);//GO TO BASE
    flag=true;
    fix=0;
    for(vector<int>::iterator it=numbers.begin();it!=numbers.end();it++){
        printf("+++i=%d\n",*it);
        fix=*it;
        if(flag){
            for(int j=-200;j>=-1300;j-=100){
                flag=false;
                printf("j=%d,fix=%d\n",j,fix);
                sendCommand_TMOVETO(3000,-8600, fix, j, 0);
                captureSave(path_do_images);
                fix+=18;
            }
        }
        
        else {
            for(int j=-1300;j<=-200;j+=100){
                
                flag=true;
                sendCommand_TMOVETO(3000,-8600, fix, j, 0);
                captureSave(path_do_images);
                printf("j=%d,fix=%d\n",j,fix);
                fix-=18;
            }
        }
        
        printf("\n");
    }
    
    sendCommand_HOME();
    

    
    
}



