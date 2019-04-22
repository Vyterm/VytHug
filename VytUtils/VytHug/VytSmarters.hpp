#ifndef VYTERM_SMARTERS_UI_HPP_INCLUDED
#define VYTERM_SMARTERS_UI_HPP_INCLUDED

#include <afxwin.h>
#define SMART_DECLARATION(class_name) \
private:\
	DECLARE_DYNAMIC(class_name)\
protected:\
	DECLARE_MESSAGE_MAP()\
public:

#define SMART_BEGIN_IMPLEMENT(class_name, base_class_name) \
IMPLEMENT_DYNAMIC(class_name, base_class_name) \
BEGIN_MESSAGE_MAP(class_name, base_class_name)

#define SMART_END_IMPLEMENT() \
END_MESSAGE_MAP()

namespace vyt
{
	inline CString Str(UINT idString)
	{
		CString str;
		str.LoadString(idString);
		return str;
	}
}

#endif