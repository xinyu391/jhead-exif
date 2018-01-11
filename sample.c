#include "jhead.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]){
    char* path = argv[1];
    int ret;
    if(argc<2){
        printf("usage: %s [jpeg-file]\n",argv[0]);
        return 0;
    }
    test(path);




    return 0;
}
  int readFile(const char* path, uchar** data){
      FILE* fp = fopen(path,"rb");
      if(fp!=NULL){

        fseek(fp,0,SEEK_END);
        int size = ftell(fp);
        fseek(fp,0, SEEK_SET);
        uchar * buf = (uchar*)malloc(size);
        int l = fread(buf,1,size, fp);
        fclose(fp);
        
        *data =buf;
        return size;
      }
      return 0;
  }
void test(char* path){
    ImageInfo_t  exifInfo;
    unsigned char* buf ;
    int size =  readFile(path, &buf);
    int ret;
    ret  = ReadJpegBuffer(buf, size, READ_METADATA, &exifInfo);
    // ret = ReadJpegFile(path, READ_METADATA, &exifInfo);
    if(ret==FALSE){
        printf("unsupported file %d\n",ret);
        return;
    }
    printf("\tFile name    : %s\n", exifInfo.FileName);
    printf("\tFile size    : %d bytes\n", exifInfo.FileSize);
    printf("\tFile date    : %d\n", exifInfo.FileDateTime);
    printf("\tXYResolution : %.0f x %.0f\n", exifInfo.xResolution, exifInfo.yResolution);
    printf("\tOrientation  : %d\n", exifInfo.Orientation);
    printf("\tCamera make  : %s\n", exifInfo.CameraMake);
    printf("\tCamera model : %s\n", exifInfo.CameraModel);
    printf("\tDate/Time    : %s\n", exifInfo.DateTime);
    printf("\tResolution   : %d x %d\n", exifInfo.Width,exifInfo.Height);
    printf("\tFlash used   : %d\n", exifInfo.FlashUsed);
    printf("\tFocal length :  %.1fmm  (35mm equivalent: %dmm)\n", exifInfo.FocalLength, exifInfo.FocalLength35mmEquiv);
    printf("\tCCD Width    : %.2fmm\n", exifInfo.CCDWidth);
    printf("\tExposure time: %.4f s  (1/%d)\n", exifInfo.ExposureTime, (int)(0.5+1/exifInfo.ExposureTime));
    printf("\tISO          : %d\n", exifInfo.ISOequivalent);
    printf("\tAperture     : f/%.2f\n", exifInfo.ApertureFNumber);
    printf("\tFocus Dist.  : %.2fm\n", exifInfo.Distance);
    printf("\tMetering Mode: %d\n", exifInfo.MeteringMode);
    printf("\tJpeg process : %d\n", exifInfo.Process);
    printf("\tLightSource  : %d\n", exifInfo.LightSource);
    
    printf("\tGPS location : %s,%s %s\n", exifInfo.GpsLat, exifInfo.GpsLong, exifInfo.GpsAlt);
}