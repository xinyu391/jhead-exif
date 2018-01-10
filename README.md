## jhead-exif

port form [jhead](http://www.sentex.net/~mwandel/jhead/), but adding multiple thread supporting.

build:
<pre>
 $mkdir build && cd build
 $cmake .. && make
</pre>
sample:
<pre>
<code>
    ImageInfo_t  exifInfo;

    int ret = ReadJpegFile(path, READ_ANY, &exifInfo);
    
    printf("\tFile name    : %s\n", exifInfo.FileName);
    printf("\tFile size    : %d bytes\n", exifInfo.FileSize);
    printf("\tFile date    : %d\n", exifInfo.FileDateTime);
    printf("\tCamera make  : %s\n", exifInfo.CameraMake);
    printf("\tCamera model : %s\n", exifInfo.CameraModel);
    printf("\tDate/Time    : %s\n", exifInfo.DateTime);
    printf("\tResolution   : %d x %d\n", exifInfo.Width,exifInfo.Height);
    printf("\tFlash used   : %d\n", exifInfo.FlashUsed);
    printf("\tFocal length :  %.3fmm  (35mm equivalent: %.3fmm)\n", exifInfo.FocalLength, exifInfo.FocalLength35mmEquiv);
    printf("\tCCD Width    : %.3fmm\n", exifInfo.CCDWidth);
    printf("\tExposure time: %.3f s  (1/10)\n", exifInfo.ExposureTime);
    printf("\tAperture     : f/%.2f\n", exifInfo.ApertureFNumber);
    printf("\tFocus Dist.  : %.2fm\n", exifInfo.Distance);
    printf("\tMetering Mode: %d\n", exifInfo.MeteringMode);
    printf("\tJpeg process : %d\n", exifInfo.Process);
</code>
</pre>