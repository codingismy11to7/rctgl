#ifndef RESOURCE_MODULE
#define RESOURCE_MODULE
#include <stdio.h>

#define RS_OK                     0 
#define RS_ERROR                 -1 
#define RS_ACTIVE                -2
#define RS_INACTIVE              -3
#define RS_INVALID_FILENAME      -4
#define RS_INVALID_RESOURCE_NAME -5
#define RS_INVALID_RESOURCE_ID   -6
#define RS_INVALID_RESOURCE_DATA -7
#define RS_RESOURCE_NOT_UNIQUE   -8

typedef struct {
	int            ResID;
	char           ResName[20];
	unsigned int   ResPrefix;
	unsigned short Type;        
	int            Start;
	unsigned int   Size;
} ResourceEntry;

typedef struct {
    unsigned int   Count;
	ResourceEntry *Data;
} ResourceHeader;

class ResourceFile
{
 public:
	 ResourceFile();
     ResourceFile(bool doErr,const char *fName, int NameSize);
     ~ResourceFile();
	 int Error(int ErrNo);
	 int Create();
	 int Open();
	 void Close();
	 int Clean();
	 unsigned int GetResSize(int ResID);
	 int GetResource(int ResID,unsigned char *ResData);
	 int GetResource(const char *ResName,unsigned char *ResData);
	 int AddResource(const char *ResName,unsigned int ResType,unsigned char *ResData, unsigned int ResSize);
	 int DeleteResource(int ResID);
 private:
	 FILE *rFile;
	 char *FileName;
	 bool  isActive;
	 bool  EchoError;
	 ResourceHeader Header;
	 int LocateRes(int ResID);
	 int LocateRes(const char *ResName);
};

#endif