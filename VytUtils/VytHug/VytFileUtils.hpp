#ifndef VYTERM_FILE_UTILS_HPP_INCLUDED
#define VYTERM_FILE_UTILS_HPP_INCLUDED

#include <afxwin.h>
#include <functional>

namespace vyt
{
	class FileUtils
	{
	public:
		static void EnumFiles(CString path, std::function<void(const CString&, WIN32_FIND_DATA&)> fileAction, bool isDeeply = false);
		static bool IsDirectory(const WIN32_FIND_DATA &filedata);
		static CString FileTimeToTimeString(const FILETIME &time);
		static CString FileSizeToString(QWORD nFileSizeHigh, QWORD nFileSizeLow);
		static void QueryFileAttributes(const CString &path, const WIN32_FIND_DATA &filedata, CString &name, CString &attr,
			CString &createTime, CString &visitTime, CString &modifyTime, CString &size, CString &md5);
		static void CleanupDirectory(CString path);
		static CString SelectFilePath(CString title = nullptr, CWnd *owner = nullptr);
		static CString SelectDirectoryPath(CString title = nullptr, CWnd *owner = nullptr);
		static CString FileSizeByPath(CString path);
		static CString FileNameByPath(CString path);
		static CString FileNameByName(CString name);
		static bool CopyToClipboard(CString str, CWnd *owner = nullptr);
	};
}

#endif