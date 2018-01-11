//--------------------------------------------------------------------------
// Include file for jhead program.
//
// This include file only defines stuff that goes across modules.  
// I like to keep the definitions for macros and structures as close to 
// where they get used as possible, so include files only get stuff that 
// gets used in more than one file.
//--------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <ctype.h>

//--------------------------------------------------------------------------

#ifdef _WIN32
    #include <sys/utime.h>

    // Make the Microsoft Visual c 10 deprecate warnings go away.
    // The _CRT_SECURE_NO_DEPRECATE doesn't do the trick like it should.
    #define unlink _unlink
    #define chmod _chmod
    #define access _access
    #define mktemp _mktemp
#else
    #include <utime.h>
    #include <sys/types.h>
    #include <unistd.h>
    #include <errno.h>
    #include <limits.h>
#endif


typedef unsigned char uchar;

#ifndef TRUE
    #define TRUE 1
    #define FALSE 0
#endif

#define MAX_COMMENT_SIZE 16000

#ifdef _WIN32
    #define PATH_MAX _MAX_PATH
    #define SLASH '\\'
#else
    #ifndef PATH_MAX
        #define PATH_MAX 1024
    #endif
    #define SLASH '/'
#endif


//--------------------------------------------------------------------------
// This structure is used to store jpeg file sections in memory.
typedef struct {
    uchar *  Data;
    int      Type;
    unsigned Size;
}Section_t;

extern int ExifSectionIndex;

extern int DumpExifMap;

#define MAX_DATE_COPIES 10

typedef struct{
    Section_t * Sections;
    int SectionsAllocated;
    int SectionsRead;
    int HaveAll; 
    int MotorolaOrder;
    int ExifImageWidth;
    double FocalplaneUnits;
    double FocalplaneXRes;
    unsigned char * DirWithThumbnailPtrs;
    int NumOrientations ;
    void * OrientationPtr[2];
    int    OrientationNumFormat[2];
}SectionsBuf;
typedef struct _Stream {
  FILE* fp;
  unsigned char* buf;
  int size;
  int offset;
} _Stream;

int stream_getc(_Stream* stream);
int stream_read(void* ptr, size_t size, size_t nmemb, _Stream* stream);
int stream_tell(_Stream* stream);
int stream_seek(_Stream* stream, long offset, int whence);
void stream_close(_Stream* stream);
//--------------------------------------------------------------------------
// This structure stores Exif header image elements in a simple manner
// Used to store camera data as extracted from the various ways that it can be
// stored in an exif header
typedef struct {
    char  FileName     [PATH_MAX+1];
    time_t FileDateTime;

    struct {
        // Info in the jfif header.
        // This info is not used much - jhead used to just replace it with default
        // values, and over 10 years, only two people pointed this out.
        char  Present;
        char  ResolutionUnits;
        short XDensity;
        short YDensity;
    }JfifHeader;

    unsigned FileSize;
    char  CameraMake   [32];  // 设备厂商
    char  CameraModel  [40];  // 设备型号
    char  DateTime     [20];  //拍摄时间
    unsigned Height, Width;   //图像大小
    int   Orientation; //图像方向
    int   IsColor;     //
    int   Process;  
    int   FlashUsed; //闪光 0：无，1：开启
    float FocalLength; //焦距
    float ExposureTime;  //曝光时间
    float ApertureFNumber;//光圈大小
    float Distance;  //  聚焦深度
    float CCDWidth;  // 
    float ExposureBias;
    float DigitalZoomRatio; //数码变焦
    int   FocalLength35mmEquiv; // 对应35mm胶片的焦距
    int   Whitebalance;  //白平衡
    int   MeteringMode;  //测光模式
    int   ExposureProgram; 
    int   ExposureMode;  // 曝光模式
    int   ISOequivalent;
    int   LightSource;   // 光源
    int   DistanceRange; 

    float xResolution;
    float yResolution;
    int   ResolutionUnit;

    char  Comments[MAX_COMMENT_SIZE];
    int   CommentWidthchars; // If nonzero, widechar comment, indicates number of chars.

    unsigned ThumbnailOffset;          // Exif offset to thumbnail
    unsigned ThumbnailSize;            // Size of thumbnail.
    unsigned LargestExifOffset;        // Last exif data referenced (to check if thumbnail is at end)

    char  ThumbnailAtEnd;              // Exif header ends with the thumbnail
                                       // (we can only modify the thumbnail if its at the end)
    int   ThumbnailSizeOffset;

    int  DateTimeOffsets[MAX_DATE_COPIES];
    int  numDateTimeTags;

    int GpsInfoPresent;
    char GpsLat[31]; //纬度
    char GpsLong[31]; //经度
    char GpsAlt[20];  //

    int  QualityGuess;
    SectionsBuf ptr;
}ImageInfo_t;



#define EXIT_FAILURE  1
#define EXIT_SUCCESS  0

// jpgfile.c functions
typedef enum {
    READ_METADATA = 1,
    READ_IMAGE = 2,
    READ_ALL = 3,
    READ_ANY = 5        // Don't abort on non-jpeg files.
}ReadMode_t;


// prototypes for jhead.c functions
void ErrFatal(const char * msg);
void ErrNonfatal(const char * msg, int a1, int a2);
void FileTimeAsString(char * TimeStr, ImageInfo_t* exifInfo);

// Prototypes for exif.c functions.
int Exif2tm(struct tm * timeptr, char * ExifTime);
void process_EXIF (unsigned char * CharBuf, unsigned int length, ImageInfo_t* exifInfo);
void ShowImageInfo(int ShowFileInfo, ImageInfo_t* exifInfo);
void ShowConciseImageInfo(ImageInfo_t* exifInfo);
const char * ClearOrientation(ImageInfo_t* exifInfo);
void PrintFormatNumber(void * ValuePtr, int Format, int ByteCount, int MotorolaOrder);
double ConvertAnyFormat(void * ValuePtr, int Format, int MotorolaOrder);
int Get16u(void * Short, int MotorolaOrder);
unsigned Get32u(void * Long, int MotorolaOrder);
int Get32s(void * Long, int MotorolaOrder);
void Put32u(void * Value, unsigned PutValue, int MotorolaOrder);
void create_EXIF(ImageInfo_t* exifInfo);

//--------------------------------------------------------------------------
// Exif format descriptor stuff
extern const int BytesPerFormat[];
#define NUM_FORMATS 12

#define FMT_BYTE       1 
#define FMT_STRING     2
#define FMT_USHORT     3
#define FMT_ULONG      4
#define FMT_URATIONAL  5
#define FMT_SBYTE      6
#define FMT_UNDEFINED  7
#define FMT_SSHORT     8
#define FMT_SLONG      9
#define FMT_SRATIONAL 10
#define FMT_SINGLE    11
#define FMT_DOUBLE    12


// makernote.c prototypes
extern void ProcessMakerNote(unsigned char * DirStart, int ByteCount,
                 unsigned char * OffsetBase, unsigned ExifLength, ImageInfo_t* exifInfo);

// gpsinfo.c prototypes
void ProcessGpsInfo(unsigned char * ValuePtr,  
                unsigned char * OffsetBase, unsigned ExifLength, ImageInfo_t* exifInfo);

// iptc.c prototpyes
void show_IPTC (unsigned char * CharBuf, unsigned int length);
void ShowXmp(Section_t XmpSection);

// Prototypes for myglob.c module
#ifdef _WIN32
void MyGlob(const char * Pattern , void (*FileFuncParm)(const char * FileName));
void SlashToNative(char * Path);
#endif

// Prototypes for paths.c module
int EnsurePathExists(const char * FileName);
void CatPath(char * BasePath, const char * FilePath);

// Prototypes from jpgfile.c
int ReadJpegSections (_Stream *stream, ReadMode_t ReadMode, ImageInfo_t*exifInfo);
void DiscardData(ImageInfo_t* exifInfo);
void DiscardAllButExif(ImageInfo_t* exifInfo);
int ReadJpegFile(const char * FileName, ReadMode_t ReadMode, ImageInfo_t* exifInfo);
int ReplaceThumbnail(const char * ThumbFileName, ImageInfo_t* exifInfo);
int SaveThumbnail(char * ThumbFileName, ImageInfo_t* exifInfo);
int RemoveSectionType(int SectionType, ImageInfo_t* exifInfo);
int RemoveUnknownSections(ImageInfo_t* exifInfo);
void WriteJpegFile(const char * FileName, ImageInfo_t* exifInfo);
Section_t * FindSection(int SectionType, ImageInfo_t* exifInfo);
Section_t * CreateSection(int SectionType, unsigned char * Data, int size, ImageInfo_t* exifInfo);
void ResetJpgfile(ImageInfo_t* exifInfo);

// Prototypes from jpgqguess.c
void process_DQT (const uchar * Data, int length, ImageInfo_t* exifInfo);
void process_DHT (const uchar * Data, int length);

// Variables from jhead.c used by exif.c
// extern ImageInfo_t ImageInfo;
extern int ShowTags;



int ReadJpegBuffer(unsigned char * buf, int size, ReadMode_t ReadMode, ImageInfo_t* exifInfo);
//--------------------------------------------------------------------------
// JPEG markers consist of one or more 0xFF bytes, followed by a marker
// code byte (which is not an FF).  Here are the marker codes of interest
// in this program.  (See jdmarker.c for a more complete list.)
//--------------------------------------------------------------------------

#define M_SOF0  0xC0          // Start Of Frame N
#define M_SOF1  0xC1          // N indicates which compression process
#define M_SOF2  0xC2          // Only SOF0-SOF2 are now in common use
#define M_SOF3  0xC3
#define M_SOF5  0xC5          // NB: codes C4 and CC are NOT SOF markers
#define M_SOF6  0xC6
#define M_SOF7  0xC7
#define M_SOF9  0xC9
#define M_SOF10 0xCA
#define M_SOF11 0xCB
#define M_SOF13 0xCD
#define M_SOF14 0xCE
#define M_SOF15 0xCF
#define M_SOI   0xD8          // Start Of Image (beginning of datastream)
#define M_EOI   0xD9          // End Of Image (end of datastream)
#define M_SOS   0xDA          // Start Of Scan (begins compressed data)
#define M_JFIF  0xE0          // Jfif marker
#define M_EXIF  0xE1          // Exif marker.  Also used for XMP data!
#define M_XMP   0x10E1        // Not a real tag (same value in file as Exif!)
#define M_COM   0xFE          // COMment 
#define M_DQT   0xDB          // Define Quantization Table
#define M_DHT   0xC4          // Define Huffmann Table
#define M_DRI   0xDD
#define M_IPTC  0xED          // IPTC marker
