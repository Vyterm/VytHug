#ifndef VYTERM_SMART_LISTCTRL_HPP_INCLUDED
#define VYTERM_SMART_LISTCTRL_HPP_INCLUDED

#include "VytSmarters.hpp"

#include "stdafx.h"
#include "resource.h"

namespace vyt
{
	class SmartList : public CListCtrl
	{
		SMART_DECLARATION(SmartList)

	public:
		SmartList();
		virtual ~SmartList();

		void InsertTexts(CString title, DWORD textCount = 0, ...);
		void InsertColumn(CString title, int width);
		void InsertColumn(DWORD columnCount, ...);
	protected:
		int m_columnIndex;
	};
}

#endif
