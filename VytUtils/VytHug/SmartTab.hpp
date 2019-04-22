#ifndef VYTERM_SMART_TABCTRL_HPP_INCLUDED
#define VYTERM_SMART_TABCTRL_HPP_INCLUDED

#include "VytSmarters.hpp"
#include <afxdialogex.h>
#include <vector>

namespace vyt
{
	class SmartTab : public CTabCtrl
	{
		SMART_DECLARATION(SmartTab)
		afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);

	public:
		SmartTab();
		virtual ~SmartTab();

		template <typename TDlg>
		void SetDlg(UINT idTemplate, CString text)
		{
			CDialogEx *pDialog = new TDlg;
			pDialog->Create(idTemplate, this);
			InsertItem(int(m_pDlgs.size()), text);
			m_pDlgs.push_back(pDialog);
		}

		template <typename TDlg>
		TDlg* GetDlg()
		{
			for (auto &pDlg : m_pDlgs)
			{
				TDlg *dlg = dynamic_cast<TDlg*>(pDlg);
				if (nullptr != dlg)
					return dlg;
			}
			return nullptr;
		}

		void SeeDlg(size_t index);
	protected:
		std::vector<CDialogEx*> m_pDlgs;
	};
}

#endif
