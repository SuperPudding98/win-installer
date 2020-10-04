#include "CreateDirectoryTransactedAction.h"
#include "winapi.h"


namespace mywininstaller
{
	namespace transactions
	{
		namespace filesystem
		{
			using std::filesystem::path;


			CreateDirectoryTransactedAction::CreateDirectoryTransactedAction(const path& dirPath, LPSECURITY_ATTRIBUTES securiryAttributes, bool existOK) :
				m_dirPath(dirPath),
				m_securiryAttributes(securiryAttributes),
				m_existOK(existOK),
				m_created(false),
				TransactedAction("Create dir " + dirPath.string())
			{}

			void CreateDirectoryTransactedAction::execute()
			{
				m_created = winapi::createDirectoryThrows(m_dirPath.c_str(), m_securiryAttributes, m_existOK);
			}


			void CreateDirectoryTransactedAction::rollback()
			{
				if (m_created)
				{
					winapi::removeDirectoryThrows(m_dirPath.c_str());
				}
			}

		}
	}
}