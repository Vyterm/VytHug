#include "stdafx.h"
#include "SmartList.hpp"
using namespace vyt;

SMART_BEGIN_IMPLEMENT(SmartList, CListCtrl)
SMART_END_IMPLEMENT()

SmartList::SmartList() : m_columnIndex(0)
{

}

SmartList::~SmartList()
{
}

void SmartList::InsertTexts(CString title, DWORD textCount, ...)
{
	auto index = GetItemCount();
	InsertItem(index, title);
	va_list texts;
	va_start(texts, textCount);
	for (DWORD i = 0; i < textCount; ++i)
		SetItemText(index, i + 1, va_arg(texts, CString));
	va_end(texts);
}

void SmartList::InsertColumn(CString title, int width)
{
	CListCtrl::InsertColumn(m_columnIndex++, title, 0, width);
}

void vyt::SmartList::InsertColumn(DWORD columnCount, ...)
{
	va_list args;
	va_start(args, columnCount);
	for (DWORD i = 0; i < columnCount; ++i)
	{
		auto title = va_arg(args, CString);
		auto width = va_arg(args, int);
		// 参数从右向左传递，如果直接写在调用语句的话，参数顺序会有误
		InsertColumn(title, width);
	}
	va_end(args);
}
