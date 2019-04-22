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
		// 1. ʹ��ͨ��� *��������Ŀ¼���ļ���·�����ַ���
		TCHAR szFilePath[MAX_PATH];
		StringCbCopy(szFilePath, MAX_PATH, path);
		StringCbCat(szFilePath, MAX_PATH, _T("\\*"));
		// 2. ��ȡ��һ���ļ�/Ŀ¼������ò��Ҿ��
		WIN32_FIND_DATA filedata;
		HANDLE file = FindFirstFile(szFilePath, &filedata);
		if (INVALID_HANDLE_VALUE == file) return;
		// 3. ��ʼѭ��������ȡ�ļ���
		do
		{
			// 3.1. �ж��Ƿ��Ǳ���Ŀ¼���ϼ�Ŀ¼�����ƣ��ǵĻ����������ѭ��
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
			// 1. ��ȡ����ʱ���
			createTime = FileTimeToTimeString(wfad.ftCreationTime);
			visitTime = FileTimeToTimeString(wfad.ftLastAccessTime);
			modifyTime = FileTimeToTimeString(wfad.ftLastWriteTime);
			if ((wfad.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
			{
				// 2. ��ʾ�ļ���С
				size = FileSizeToString(wfad.nFileSizeHigh, wfad.nFileSizeLow);
				// 3. ��ʾ�ļ�MD5ֵ
				md5 = md5FileValue(filename);
			}
			// 4. ��ʾ�ļ����ļ�������
			if ((wfad.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN) == FILE_ATTRIBUTE_HIDDEN)
				attr = Str(IDS_HIDE) + attr;
		}
		else
		{
			attr += Str(IDS_ACCESS_FAILED);
		}
	}
}
