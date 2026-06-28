#ifndef __QUERY_H__
#define __QUERY_H__
#include "student.h"
#include "list.h"
int ShowAllSameName(Node* pHead, const char* n);
int ShowAllSameBirthYear(Node* pHead, int birthyear);
int ShowAllSameEnrollmentYear(Node* pHead, int enteryear);
int ShowAllInformation(Node* pHead);
#endif