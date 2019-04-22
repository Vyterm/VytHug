#ifndef VYTERM_FILE_UTILS_HPP_INCLUDED
#define VYTERM_FILE_UTILS_HPP_INCLUDED

#include <afxwin.h>
#include <functional>

namespace vyt
{
	void EnumFiles(CString path, std::function<void(const CString&, WIN32_FIND_DATA&)> fileAction);
	CString FileTimeToTimeString(const FILETIME &time);
	CString FileSizeToString(QWORD nFileSizeHigh, DWORD nFileSizeLow);
	void QueryFileAttributes(const CString &path, const WIN32_FIND_DATA &filedata, CString &name, CString &attr,
		CString &createTime, CString &visitTime, CString &modifyTime, CString &size, CString &md5);
}

#endif