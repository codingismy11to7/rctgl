#include <windows.h>
#include <stdio.h>
#include "ResourceIO.h"

ResourceFile::ResourceFile()
{
 isActive = false;
 rFile = NULL;
 FileName = NULL;
 Header.Count = 0;
 Header.Data = NULL;
 EchoError = false;
}

ResourceFile::ResourceFile(bool doErr, const char *fName, int NameSize)
{
 isActive = false;
 rFile = NULL;
 FileName = (char *)malloc(NameSize + 1);
 memcpy(FileName,fName,NameSize);
 FileName[NameSize] = 0;
 Header.Count = 0;
 Header.Data = NULL;
 EchoError = doErr;
}

ResourceFile::~ResourceFile()
{
 if(isActive) fclose(rFile);
 if(FileName != NULL) free(FileName);
 if(Header.Data != NULL) delete [] Header.Data;
}

int ResourceFile::Error(int ErrNo)
{
 char ErrStr[200];
 if(EchoError)
 {
  switch(ErrNo)
  {
   case RS_ERROR: strcpy(ErrStr,"Unknown Error!");break;
   case RS_ACTIVE: strcpy(ErrStr,"Resource File is already in use!");break;
   case RS_INACTIVE: strcpy(ErrStr,"Operation can not be executed on inActive File!");break;
   case RS_INVALID_FILENAME: strcpy(ErrStr,"Invalid File Name!");break;
   case RS_INVALID_RESOURCE_NAME: strcpy(ErrStr,"Invalid Resource Name!");break;
   case RS_INVALID_RESOURCE_ID: strcpy(ErrStr,"Invalid Resource ID!");break;
   case RS_INVALID_RESOURCE_DATA: strcpy(ErrStr,"Invalid Data Pointer!");break;
   case RS_RESOURCE_NOT_UNIQUE: strcpy(ErrStr,"Resource Names must be UNIQUE!");break;
  default: strcpy(ErrStr,"Operation Executed!");break;
  }
  MessageBox (HWND_DESKTOP, ErrStr, "Resource File Error", MB_OK | MB_ICONEXCLAMATION);
 }
 return ErrNo;
}

int ResourceFile::Create()
{
 if(isActive) return Error(RS_ACTIVE);
 if(FileName == NULL) return Error(RS_INVALID_FILENAME);
 if((rFile = fopen(FileName,"w+b")) == NULL) return Error(RS_INVALID_FILENAME);
 Header.Count = 0;
 fwrite(&(Header.Count),4,1,rFile);
 fclose(rFile);
 if((rFile = fopen(FileName,"r+b")) == NULL) return Error(RS_INVALID_FILENAME);
 isActive = true;
 return RS_OK;
}

void ResourceFile::Close()
{
 if(isActive) fclose(rFile);
 if(Header.Data != NULL) 
 {
  delete [] Header.Data;
  Header.Data = NULL;
 }
 Header.Count = 0;
 isActive = false;
}

int ResourceFile::Open()
{
 int HeaderLength;
 if(isActive) return Error(RS_ACTIVE);
 if(FileName == NULL) return Error(RS_INVALID_FILENAME);
 if((rFile = fopen(FileName,"r+b")) == NULL) return Create();
 fseek(rFile,-4,SEEK_END);
 fread(&(Header.Count),4,1,rFile);
 if(Header.Count > 0)
 {
  HeaderLength = Header.Count * sizeof(ResourceEntry);
  Header.Data = new ResourceEntry[Header.Count];
  fseek(rFile, -(4 + HeaderLength), SEEK_END);
  fread(Header.Data, HeaderLength,1,rFile);
 }
 isActive = true;
 return RS_OK;
}

int ResourceFile::AddResource(const char *ResName,unsigned int ResType, unsigned char *ResData, unsigned int ResSize)
{
 int HeaderLength;
 int rPos;
 int sLen;
 int nResID;
 ResourceEntry *nData;
 if(!isActive) return Error(RS_INACTIVE);
 if(ResName == NULL)  return Error(RS_INVALID_RESOURCE_NAME);
 if(LocateRes(ResName) > -1) return Error(RS_RESOURCE_NOT_UNIQUE);
 if(ResData == NULL)  return Error(RS_INVALID_RESOURCE_DATA);
 nData = new ResourceEntry[Header.Count + 1];
 if(Header.Count > 0) memcpy(nData,Header.Data,sizeof(ResourceEntry) * Header.Count);
 HeaderLength = Header.Count * sizeof(ResourceEntry);
 fseek(rFile,-(4 + HeaderLength),SEEK_END);
 delete [] Header.Data;
 Header.Data = nData;
 nResID = 1;
 if(Header.Count > 0) nResID += Header.Data[Header.Count - 1].ResID;
 rPos = Header.Count++;
 Header.Data[rPos].ResID = nResID;
 Header.Data[rPos].Type  = ResType;
 Header.Data[rPos].Size  = ResSize;
 Header.Data[rPos].Start = ftell(rFile);
 sLen = strlen(ResName);
 if(sLen > 19) sLen = 19;
 memset(Header.Data[rPos].ResName,0,20);
 memcpy(Header.Data[rPos].ResName,ResName,sLen);
 Header.Data[rPos].ResPrefix = Header.Data[rPos].ResName[0] * 0x01000000 + Header.Data[rPos].ResName[1] * 0x00010000 +
	                           Header.Data[rPos].ResName[2] * 0x00000100 + Header.Data[rPos].ResName[3];
 HeaderLength = Header.Count * sizeof(ResourceEntry);
 fwrite(ResData,ResSize,1,rFile);
 fwrite(Header.Data,HeaderLength,1,rFile);
 fwrite(&(Header.Count),4,1,rFile);
 return Header.Count;
}

int ResourceFile::GetResource(int ResID,unsigned char *ResData)
{
 int rPos, rSize;
 int rLocation;
 if(!isActive) return Error(RS_INACTIVE);
 if(ResID < 1) return Error(RS_INVALID_RESOURCE_ID);
 if((rLocation = LocateRes(ResID)) < 0) return Error(RS_INVALID_RESOURCE_ID);
 rPos  = Header.Data[rLocation].Start;
 rSize = Header.Data[rLocation].Size;
 fseek(rFile,rPos,SEEK_SET);
 fread(ResData,rSize,1,rFile);
 return RS_OK;
}

int ResourceFile::GetResource(const char *ResName,unsigned char *ResData)
{
 int rPos, rSize;
 int rLocation;
 if(!isActive) return Error(RS_INACTIVE);
 if(ResName == NULL) return Error(RS_INVALID_RESOURCE_NAME);
 if((rLocation = LocateRes(ResName)) < 0) return Error(RS_INVALID_RESOURCE_NAME);
 rPos  = Header.Data[rLocation].Start;
 rSize = Header.Data[rLocation].Size;
 fseek(rFile,rPos,SEEK_SET);
 fread(ResData,rSize,1,rFile);
 return RS_OK;
}

unsigned int ResourceFile::GetResSize(int ResID)
{
 int rLocation;
 if(!isActive) return Error(RS_INACTIVE);
 if(ResID < 1) return Error(RS_INVALID_RESOURCE_ID);
 if((rLocation = LocateRes(ResID)) < 0) return Error(RS_INVALID_RESOURCE_ID);
 return Header.Data[rLocation].Size;
}

int ResourceFile::DeleteResource(int ResID)
{
 int HeaderLength;
 int rLocation;
 if(!isActive) return Error(RS_INACTIVE);
 if((rLocation = LocateRes(ResID)) < 0) return Error(RS_INVALID_RESOURCE_ID);
 Header.Data[rLocation].ResID = -1;
 HeaderLength = Header.Count * sizeof(ResourceEntry);
 fseek(rFile, -(4+HeaderLength), SEEK_END);
 fwrite(Header.Data,HeaderLength,1,rFile);
 fwrite(&(Header.Count),4,1,rFile);
 return RS_OK;
}

int ResourceFile::LocateRes(int ResID)
{
 unsigned int rot;
 if(!isActive) return Error(RS_INACTIVE);
 for(rot = 0;rot < Header.Count;rot++)
 {
  if(Header.Data[rot].ResID == ResID) return rot;
 }
 return RS_INVALID_RESOURCE_ID;
}

int ResourceFile::LocateRes(const char *ResName)
{
 unsigned int rot;
 unsigned int rPrefix;
 char rName[20];
 if(!isActive) return Error(RS_INACTIVE);
 memset(rName,0,20);
 strcpy(rName,ResName);
 rPrefix = rName[0] * 0x01000000 + rName[1] * 0x00010000 + rName[2] * 0x00000100 + rName[3];
 for(rot = 0;rot < Header.Count;rot++)
 {
  if(Header.Data[rot].ResPrefix == rPrefix)
  {
   if(strcmp(Header.Data[rot].ResName, ResName) == 0) return rot;  
  }
 }
 return RS_INVALID_RESOURCE_ID;
}

int ResourceFile::Clean()
{
 return RS_OK;
}