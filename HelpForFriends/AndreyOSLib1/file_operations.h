#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>
#include <vector>
#include <iomanip>
#include "utils.h"

void CopyFile(const std::wstring& srcFile, const std::wstring& destFile);
void MoveFile(const std::wstring& srcFile, const std::wstring& destFile);
void PrintFileAttributes(const std::wstring& fileName, bool flag = false);
void GetFileInfo(const std::wstring& fileName);
void ShowFileTime(const std::wstring& fileName);
void SetFileTime(const std::wstring& fileName, const std::wstring& time, const std::wstring& select);
void SetFileAttribute(std::wstring fileName, DWORD attributes = 0);

