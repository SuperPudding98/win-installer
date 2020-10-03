#include "fsutils_winapi.h"
#include "Win32Error.h"
#include <Windows.h>


namespace mywininstaller
{
	namespace fsutils
	{
		namespace winapi
		{
			bool createDirectoryThrows(LPCWSTR path, LPSECURITY_ATTRIBUTES securiryAttributes, bool existOK)
			{
				if (!CreateDirectoryW(path, securiryAttributes))
				{
					DWORD errorCode = GetLastError();
					if (!(errorCode == ERROR_ALREADY_EXISTS && existOK))
					{
						throw Win32Error(errorCode);
					}

					return false;
				}
				else
				{
					return true;
				}
			}

			void removeDirectoryThrows(LPCWSTR path)
			{
				if (!RemoveDirectoryW(path))
				{
					throw Win32Error::fromLastError();
				}
			}

			void copyFileThrows(LPCWSTR from, LPCWSTR to, bool overwrite)
			{
				if (!CopyFileW(from, to, !overwrite))
				{
					throw Win32Error::fromLastError();
				}
			}

			void deleteFileThrows(LPCWSTR path)
			{
				if (!DeleteFileW(path))
				{
					throw Win32Error::fromLastError();
				}
			}
		}
	}
}
