#include "Win32Error.h"
#include <string>
#include <system_error>
#include <Windows.h>


namespace mywininstaller
{
	Win32Error::Win32Error(const DWORD errorCode) :
		m_errorCode(errorCode),
		runtime_error("Win32 error " + std::to_string(errorCode))
	{}

	DWORD Win32Error::getErrorCode() const
	{
		return m_errorCode;
	}

	Win32Error Win32Error::fromLastError()
	{
		return Win32Error(GetLastError());
	}
}
