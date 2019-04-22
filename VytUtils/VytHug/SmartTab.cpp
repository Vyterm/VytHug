#include "stdafx.h"
#include "SmartTab.hpp"

using namespace vyt;

SMART_BEGIN_IMPLEMENT(SmartTab, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &SmartTab::OnTcnSelchange)
SMART_END_IMPLEMENT()

SmartTab::SmartTab()
{

}

SmartTab::~SmartTab()
{
}

void SmartTab::SeeDlg(size_t index)
{
	if (GetCurFocus() != index)
		SetCurFocus(int(index));
	for (size_t i = 0; i < m_pDlgs.size(); ++i)
	{
		if (i == index)
		{
			CRect rt;
			GetClientRect(rt);
			rt.DeflateRect(3, 23, -3, -3);
			m_pDlgs[i]->ShowWindow(SW_SHOW);
			m_pDlgs[i]->MoveWindow(rt);
		}
		else
			m_pDlgs[i]->ShowWindow(SW_HIDE);
	}
}

void SmartTab::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult)
{
	SeeDlg(GetCurSel());
	*pResult = 0;
}
