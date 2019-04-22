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

void SmartList::InsertTexts(CString title, int textCount, ...)
{
	auto index = GetItemCount();
	InsertItem(index, title);
	va_list texts;
	va_start(texts, textCount);
	for (int i = 0; i < textCount; ++i)
		SetItemText(index, i + 1, va_arg(texts, CString));
	va_end(texts);
}

void SmartList::InsertColumn(CString title, int width)
{
	CListCtrl::InsertColumn(m_columnIndex++, title, 0, width);
}
