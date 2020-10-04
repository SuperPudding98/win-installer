#include "CreateDirectoryTransactedAction.h"
#include "winapi.h"


namespace mywininstaller
{
	namespace transactions
	{
		namespace filesystem
		{
			using std::filesystem::path;


			CreateDirectoryTransactedAction::CreateDirectoryTransactedAction(const path& dirPath, LPSECURITY_ATTRIBUTES securiryAttributes) :
				m_dirPath(dirPath),
				m_securiryAttributes(securiryAttributes),
				TransactedAction("Create dir " + dirPath.string())
			{}

			void CreateDirectoryTransactedAction::execute()
			{
				winapi::createDirectoryThrows(m_dirPath.c_str(), m_securiryAttributes);
			}


			void CreateDirectoryTransactedAction::rollback()
			{
				winapi::removeDirectoryThrows(m_dirPath.c_str());
			}

		}
	}
}