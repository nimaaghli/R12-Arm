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
using namespace std;

int main(int argc, const char * argv[]) {
    //password="NAhuygi6djgovuyv";
    password="ESjdvkasfalkgd";//SHAKERI
    //password="SMkgbku6tc4hxwy";
    string path_do_images="/Users/nimaaghli/Documents/Couraea/AI and Robotics/project1_AIClass/project1_AIClass/img/";
    bool flag=true;
    vector<double> numbers={-4400,-4400,-4800};
    //saveImage(path_do_images);
    //captureImage();
    captureSave(path_do_images);
    sendCommand_HOME();
    sendCommand_TMOVETO(3000,-5950, -2752, -1600, 100);
    for(int i=-1831;i<=-1031;i+=200){
        printf("+++i=%d\n",i);
        if(flag){
                for(int j=-280;j>=-1100;j-=100){
                    //sendCommand_TMOVETO(3000,-1050, -2952, -280, -1831);
                    printf("j=%d",j);
                    flag=false;
                    sendCommand_TMOVETO(3000,-950, -2820, j, i);
                    captureSave(path_do_images);
            }
        }
        
        else {
            for(int j=-1100;j<=-280;j+=100){
                //sendCommand_TMOVETO(3000,-1050, -2952, -280, -1831);
                printf("j=%d",j);
                flag=true;
                sendCommand_TMOVETO(3000,-950, -2820, j, i);
                captureSave(path_do_images);
                }
        }
        
        printf("\n");
    }

    
    
    sendCommand_TMOVETO(3000,-5950, -2752, -1600, 100);
    flag=true;
    int fix;
    for(vector<double>::iterator it=numbers.begin();it!=numbers.end();it++){
        printf("+++i=%f\n",*it);
        fix=*it;
        if(flag){
            for(int j=-300;j>=-1400;j-=100){
                //sendCommand_TMOVETO(3000,-1050, -2952, -280, -1831);
                flag=false;
                printf("j=%d,fix=%d\n",j,fix);
                sendCommand_TMOVETO(3000,-8600, fix, j, 0);
                captureSave(path_do_images);
                fix+=18;
            }
        }
        
        else {
            for(int j=-1400;j<=-300;j+=100){
                //sendCommand_TMOVETO(3000,-1050, -2952, -280, -1831);
                
                flag=true;
                sendCommand_TMOVETO(3000,-8600, fix, j, 0);
                captureSave(path_do_images);
                printf("j=%d,fix=%d\n",j,fix);
                fix-=18;
            }
        }
        
        printf("\n");
    }
   /* sendCommand_TMOVETO(3000,-1050, -2852, -1100, -1631);
    sendCommand_TMOVETO(3000,-1050, -2922, -280, -1631);
    sendCommand_TMOVETO(3000,-1050, -2922, -280, -1441);
    sendCommand_TMOVETO(3000,-1050, -2852, -1100, -1431);
    sendCommand_TMOVETO(3000,-1050, -2852, -1100, -1231);
    sendCommand_TMOVETO(3000,-1050, -2922, -280, -1241);
    sendCommand_TMOVETO(3000,-1050, -2922, -280, -1041);
    sendCommand_TMOVETO(3000,-1050, -2852, -1100, -1031);
    
    
    
    sendCommand_TMOVETO(3000,-5950, -2752, -1600, 100);
    */
 
    
    /*sendCommand_TMOVETO(3000,-8500, -4400, -300, 0);
    sendCommand_TMOVETO(3000,-8500, -4200, -1400, 0);
    sendCommand_TMOVETO(3000,-8500, -4400, -1400, 0);
    sendCommand_TMOVETO(3000,-8500, -4600, -300, 0);
    sendCommand_TMOVETO(3000,-8500, -4800, -300, 0);
    sendCommand_TMOVETO(3000,-8500, -4700, -1400, 0);
    */
    
    
    sendCommand_TMOVETO(3000,-5950, -2752, -1600, 100);
    sendCommand_HOME();
   
    
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



