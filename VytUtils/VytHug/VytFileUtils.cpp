#include "stdafx.h"
#include "resource.h"
#include "VytFileUtils.hpp"
#include "md5.h"
#include <strsafe.h>
using namespace vyt;

namespace vyt
{
	void EnumFiles(CString path, std::function<void(const CString&, WIN32_FIND_DATA&)> fileAction)
	{
		// 1. 使用通配符 *，构建子目录和文件夹路径的字符串
		TCHAR szFilePath[MAX_PATH];
		StringCbCopy(szFilePath, MAX_PATH, path);
		StringCbCat(szFilePath, MAX_PATH, _T("\\*"));
		// 2. 获取第一个文件/目录，并获得查找句柄
		WIN32_FIND_DATA filedata;
		HANDLE file = FindFirstFile(szFilePath, &filedata);
		if (INVALID_HANDLE_VALUE == file) return;
		// 3. 开始循环遍历获取文件名
		do
		{
			// 3.1. 判断是否是本级目录或上级目录的名称，是的话则结束本次循环
			if (!_tcscmp(filedata.cFileName, _T(".")) || !_tcscmp(filedata.cFileName, _T(".."))) continue;
			fileAction(path, filedata);
		} while (FindNextFile(file, &filedata));
	}

	CString FileTimeToTimeString(const FILETIME & time)
	{
		FILETIME ftLocal;
		FileTimeToLocalFileTime(&time, &ftLocal);
		SYSTEMTIME stTime;
		FileTimeToSystemTime(&ftLocal, &stTime);
		CString timeString;
		timeString.Format(_T("%04d%s%02d%s%02d%s %02d:%02d"),
			stTime.wYear, vyt::Str(IDS_YEAR),
			stTime.wMonth, vyt::Str(IDS_MONTH),
			stTime.wDay, vyt::Str(IDS_DAY),
			stTime.wHour, stTime.wMinute);
		return timeString;
	}

	CString FileSizeToString(QWORD nFileSizeHigh, DWORD nFileSizeLow)
	{
		QWORD fileSize = (nFileSizeHigh << 32) + nFileSizeLow;
		CString sizeUnitStrings[] = { _T("B"), _T("KB"), _T("MB"), _T("GB") };
		int sizeUnit = fileSize > 1024 ? 1 : 0;
		long double ldSize = fileSize > 1024 ? long double(fileSize / 1024.0l) : long double(fileSize);
		while (ldSize > 1024.0)
		{
			ldSize /= 1024.0;
			++sizeUnit;
			if (sizeUnit + 1 == _countof(sizeUnitStrings))
				break;
		}
		CString fileSizeString;
		fileSizeString.Format(_T("%.1lf %s"), ldSize, sizeUnitStrings[sizeUnit]);
		return fileSizeString;
	}

	void QueryFileAttributes(const CString & path, const WIN32_FIND_DATA & filedata, CString & name, CString & attr,
		CString & createTime, CString & visitTime, CString & modifyTime, CString & size, CString & md5)
	{
		name = filedata.cFileName;
		attr = (filedata.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY ? Str(IDS_DIRECTORY) : Str(IDS_FILE);
		createTime = _T("");
		visitTime = _T("");
		modifyTime = _T("");
		size = _T("");
		md5 = _T("");
		CString filename;
		filename.Format(_T("%s\\%s"), path, filedata.cFileName);
		WIN32_FILE_ATTRIBUTE_DATA wfad = {};
		if (GetFileAttributesEx(filename, GetFileExInfoStandard, &wfad))
		{
			// 1. 获取若干时间戳
			createTime = FileTimeToTimeString(wfad.ftCreationTime);
			visitTime = FileTimeToTimeString(wfad.ftLastAccessTime);
			modifyTime = FileTimeToTimeString(wfad.ftLastWriteTime);
			if ((wfad.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
			{
				// 2. 显示文件大小
				size = FileSizeToString(wfad.nFileSizeHigh, wfad.nFileSizeLow);
				// 3. 显示文件MD5值
				md5 = md5FileValue(filename);
			}
			// 4. 显示文件或文件夹属性
			if ((wfad.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN)
				attr = Str(IDS_HIDE) + attr;
		}
		else
		{
			attr += Str(IDS_ACCESS_FAILED);
		}
	}
}
