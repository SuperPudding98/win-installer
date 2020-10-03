#include "Win32Error.h"
#include <string>


namespace mywininstaller
{
	Win32Error::Win32Error(const DWORD errorCode, const std::string& message) :
		m_errorCode(errorCode),
		runtime_error(std::string("Win32 Error ") + std::to_string(errorCode) + std::string(": ") + message)
	{}

	DWORD Win32Error::getErrorCode() const
	{
		return m_errorCode;
	}
}
