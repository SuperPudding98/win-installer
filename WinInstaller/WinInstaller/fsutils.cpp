#include "fsutils.h"
#include "Win32Error.h"
#include <Windows.h>


namespace mywininstaller
{
	namespace fsutils
	{
		using std::wstring;

		void createDirectoryThrows(const wstring& path, bool existOK)
		{
			if (!CreateDirectoryW(path.c_str(), nullptr))
			{
				DWORD errorCode = GetLastError();
				if (!(errorCode == ERROR_ALREADY_EXISTS && existOK))
				{
					throw Win32Error(errorCode);
				}
			}
		}

		void removeDirectoryThrows(const std::wstring& path)
		{
			if (!RemoveDirectoryW(path.c_str()))
			{
				throw Win32Error::fromLastError();
			}
		}

		void copyFileThrows(const std::wstring& from, const std::wstring& to, bool overwrite)
		{
			if (!CopyFileW(from.c_str(), to.c_str(), !overwrite))
			{
				throw Win32Error::fromLastError();
			}
		}

		void deleteFileThrows(const std::wstring& path)
		{
			if (!DeleteFileW(path.c_str()))
			{
				throw Win32Error::fromLastError();
			}
		}
	}
}
