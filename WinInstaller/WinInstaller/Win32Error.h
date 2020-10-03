#pragma once
#include <stdexcept>
#include <string>
#include <Windows.h>


namespace mywininstaller
{
	class Win32Error : public std::runtime_error
	{
	public:
		Win32Error(const DWORD errorCode, const std::string& message = "");
		Win32Error(const Win32Error& other) = default;
		Win32Error(Win32Error&& other) = default;
		virtual ~Win32Error() = default;
		Win32Error& operator=(const Win32Error& other) = default;
		Win32Error& operator=(Win32Error&& other) = default;
		DWORD getErrorCode() const;

	private:
		const DWORD m_errorCode;
	};
}
