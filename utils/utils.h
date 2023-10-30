#ifndef _UTILS_H_
#define _UTILS_H_
bool intmas(uint64_t inputValue, uint8_t valueRangeBytes, char *arrToStore);
uint8_t GetFileName(char* inputPath, char *receivedName);
uint32_t masrng(char* inputArr);
uint32_t dataStack(bool direction, uint32_t inputValue);
uint32_t strarcmp(char *Arr1, uint32_t startIndex, char *Arr2, uint32_t length);
uint64_t masint(uint8_t *srcStr, uint32_t strIndex, uint8_t wordRange);
void transformFileName(char *sourceFileName, uint8_t sourceLenght, char *suffixToAttach, uint8_t suffixLength, char *arrToStore);
void splitFileName(char* sourceFileName, char *fileName, char *fileExt);
void arrcop(char *sourceArr, uint16_t startIndex, char *destinationArr, uint16_t valueOfElements);
void mascln(char *arrToClean, uint32_t cleanStartIndex, uint32_t cleanEndIndex);
#endif
