#include<stdint.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "utils.h"
////////////////////////////////////////////////////////////////////////////
#define dataStackDepth	8	//ЗДЕСЬ: ЗАДАЕТ ГЛУБИНУ СТЕКА В DWORD(UINT32_T)
////////////////////////////////////////////////////////////////////////////
uint8_t stackLevel=0;
uint32_t stackBuffer[dataStackDepth];
uint8_t GetFileName(char* inputPath, char *receivedName){
	uint8_t masRange=masrng(receivedName);
	char iname[256];
	char oname[masRange];
	memset(iname,0x00,sizeof(iname));
	memset(oname,0x00,sizeof(oname));
	uint8_t nameLenght = strlen(inputPath);
	strcpy(iname,inputPath);
	char *lastSymbolEntry = strrchr(iname, 92);
	uint8_t entryPos = lastSymbolEntry-iname+1;
	uint8_t stepsTransfer=0;
	memset(receivedName,0x00,masRange);
	if(lastSymbolEntry==NULL){
		while(stepsTransfer<=nameLenght){
			oname[stepsTransfer]=iname[stepsTransfer];
			if(stepsTransfer==nameLenght)
			{oname[stepsTransfer]=0x00;}
			++stepsTransfer;}
		strcpy(receivedName,oname);
		return stepsTransfer;}
	while(entryPos<nameLenght){
		oname[stepsTransfer]=iname[entryPos];
		++entryPos;
		++stepsTransfer;}
	strcpy(receivedName,oname);
	return stepsTransfer;}
inline uint32_t masrng(char* inputArr){
	for(uint32_t i=0;i<0xFFFFFFFF;++i)
	{if(inputArr[i]==0x00){return i;}}}
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore){
	char procBuf[224];
	memset(procBuf,0x00,sizeof(procBuf));
	uint8_t filenameWithoutExtension=sourceLenght;
	uint8_t generatedFileNameWithSuffix;
	for(int i=0;i<filenameWithoutExtension+suffixLength;++i){
		if(i<filenameWithoutExtension){
			procBuf[i]=sourceFileName[i];}
		if(i>=filenameWithoutExtension){
			procBuf[i]=suffixToAttach[i-filenameWithoutExtension];}}
	generatedFileNameWithSuffix = filenameWithoutExtension+suffixLength;
	for(int i=0;i<generatedFileNameWithSuffix;++i)
	{arrToStore[i]=procBuf[i];}}
void splitFileName(char* sourceFileName, char *fileName, char *fileExt){
	char fext[16];
	char sname[256];
	char oname[240];
	strcpy(sname,sourceFileName);
	uint8_t endOfName=0;
	uint8_t pointPtr=masrng(fileExt);
	uint8_t transferIndex=masrng(fileName);
	memset(fileExt,0x00,pointPtr);
	memset(fileName,0x00,transferIndex);
	transferIndex=0;
	pointPtr=0;
	uint8_t nameLength=strlen(sname);
	for(uint8_t i=0;i<64;++i){
		if(sname[i]==0x00){endOfName=i;
			break;}}
	for(uint8_t i=endOfName;i>0;--i){
		if(sname[i]==0x2E){pointPtr=i;
			break;}}
	for(uint8_t i=pointPtr+1;i<nameLength+1;++i){
		fext[transferIndex]=sname[i];
		if(i==nameLength){fext[transferIndex+1]=0x00;}
		++transferIndex;}transferIndex=0;
	for(uint8_t i=0;i<pointPtr;++i){oname[i]=sname[i];
		if(i==pointPtr-1){oname[i+1]=0x00;}}
	strcpy(fileExt,fext);
	strcpy(fileName,oname);}
bool intmas(uint64_t inputValue, uint8_t valueRangeBytes, char *arrToStore){
	switch(valueRangeBytes){
		case 0x01:{
			arrToStore[0]=inputValue;
			return 1;}
		case 0x02:{
			arrToStore[0]=inputValue>>8;
			arrToStore[1]=inputValue;
			return 1;}
		case 0x04:{
			arrToStore[0]=inputValue>>24;
			arrToStore[1]=inputValue>>16;
			arrToStore[2]=inputValue>>8;
			arrToStore[3]=inputValue;
			return 1;}
		case 0x08:{
			arrToStore[0]=inputValue>>56;
			arrToStore[1]=inputValue>>48;
			arrToStore[2]=inputValue>>32;
			arrToStore[3]=inputValue>>24;
			arrToStore[4]=inputValue>>16;
			arrToStore[5]=inputValue>>40;
			arrToStore[6]=inputValue>>8;
			arrToStore[7]=inputValue;
			return 1;}}}
void arrcop(char *sourceArr, uint16_t startIndex, char *destinationArr, uint16_t valueOfElements){
	for(uint16_t i=0;i<valueOfElements;++i){
		destinationArr[startIndex]=sourceArr[i];
		startIndex++;}}
void mascln(char *arrToClean, uint32_t cleanStartIndex, uint32_t cleanEndIndex){
	while(cleanStartIndex<=cleanEndIndex){
		arrToClean[cleanStartIndex]=0x00;
		++cleanStartIndex;}}
uint32_t dataStack(bool direction, uint32_t inputValue){
	uint32_t popRegister;
	if((direction==1)&&(stackLevel<sizeof(stackBuffer))){
		++stackLevel;
		stackBuffer[stackLevel]=inputValue;
		return stackLevel;}
	if((direction==0)&&(stackLevel>=0)){
		popRegister=stackBuffer[stackLevel];
		--stackLevel;
		return popRegister;}return 0;}
uint32_t strarcmp(char *Arr1, uint32_t startIndex, char *Arr2, uint32_t length){
	bool compareStatus=0;
	uint32_t ri=0;
	uint32_t li=startIndex+length;
	while(startIndex<li){if(Arr1[startIndex]==Arr2[ri]){compareStatus=1;}
		else{return 0;}ri++;
		startIndex++;}return startIndex;}
uint64_t masint(uint8_t *srcStr, uint32_t strIndex, uint8_t wordRange){
	uint64_t retVal;
	switch(wordRange){
		case 0x01:{
			retVal=srcStr[0];
			break;}
		case 0x02:{
			retVal=srcStr[1];
			retVal=retVal|srcStr[0]<<8;
			break;}
		case 0x04:{
			retVal=srcStr[3];
			retVal=retVal|srcStr[2]<<8;
			retVal=retVal|srcStr[1]<<16;
			retVal=retVal|srcStr[0]<<24;
			break;}
		/*case 0x08:{
			retVal=srcStr[7];
			retVal=retVal|srcStr[6]<<8;
			retVal=retVal|srcStr[5]<<16;
			retVal=retVal|srcStr[4]<<24;
			retVal=retVal|srcStr[3]<<32;
			retVal=retVal|srcStr[2]<<40;
			retVal=retVal|srcStr[1]<<48;
			retVal=retVal|srcStr[0]<<56;
			break;}*/}return retVal;}
