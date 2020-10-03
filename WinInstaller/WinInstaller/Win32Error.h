#pragma once
#include <stdexcept>
#include <string>
#include <Windows.h>


namespace mywininstaller
{
	// We could inherit from std::system_error and hook this up to automatically show error message when you call what(),
	// but std::system_error can possibly overflow (it uses int for error codes instead of DWORD) and anyway the message is almost always "Unkown error".
	// So for consistency and correctness of messages it's better to just show error code.
	class Win32Error : public std::runtime_error
	{
	public:
		Win32Error(const DWORD errorCode);
		DWORD getErrorCode() const;
		static Win32Error fromLastError();

	private:
		const DWORD m_errorCode;
	};
}
