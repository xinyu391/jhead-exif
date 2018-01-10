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
void test(char* path){
    ImageInfo_t  exifInfo;

    int ret = ReadJpegFile(path, READ_ANY, &exifInfo);
    if(ret==FALSE){
        printf("unsupported file %d\n",ret);
        return;
    }
    printf("\tFile name    : %s\n", exifInfo.FileName);
    printf("\tFile size    : %d bytes\n", exifInfo.FileSize);
    printf("\tFile date    : %d\n", exifInfo.FileDateTime);
    printf("\tCamera make  : %s\n", exifInfo.CameraMake);
    printf("\tCamera model : %s\n", exifInfo.CameraModel);
    printf("\tDate/Time    : %s\n", exifInfo.DateTime);
    printf("\tResolution   : %d x %d\n", exifInfo.Width,exifInfo.Height);
    printf("\tFlash used   : %d\n", exifInfo.FlashUsed);
    printf("\tFocal length :  %.3fmm  (35mm equivalent: %dmm)\n", exifInfo.FocalLength, exifInfo.FocalLength35mmEquiv);
    printf("\tCCD Width    : %.3fmm\n", exifInfo.CCDWidth);
    printf("\tExposure time: %.3f s  (1/10)\n", exifInfo.ExposureTime);
    printf("\tAperture     : f/%.2f\n", exifInfo.ApertureFNumber);
    printf("\tFocus Dist.  : %.2fm\n", exifInfo.Distance);
    printf("\tMetering Mode: %d\n", exifInfo.MeteringMode);
    printf("\tJpeg process : %d\n", exifInfo.Process);
}