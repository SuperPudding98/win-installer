#include "CopyFileToDirectoryTransactedAction.h"
#include "winapi.h"


namespace mywininstaller
{
	namespace transactions
	{
		namespace filesystem
		{
			using std::filesystem::path;


			CopyFileToDirectoryTransactedAction::CopyFileToDirectoryTransactedAction(const path& fromFilePath, const path& toDirPath, bool overwrite) :
				m_fromPath(fromFilePath),
				m_toPath(toDirPath / fromFilePath.filename()),
				m_overwrite(overwrite),
				TransactedAction("Copy file " + fromFilePath.string() + " to " + toDirPath.string())
			{}

			void CopyFileToDirectoryTransactedAction::execute()
			{
				winapi::copyFileThrows(m_fromPath.c_str(), m_toPath.c_str(), m_overwrite);
			}

			void CopyFileToDirectoryTransactedAction::rollback()
			{
				winapi::deleteFileThrows(m_toPath.c_str());
			}
		};
	}
}
