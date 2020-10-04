#include "CreateDirectoryAndParentsTransactedAction.h"
#include "CreateDirectoryTransactedAction.h"


namespace mywininstaller
{
	namespace transactions
	{
		namespace filesystem
		{
			using std::filesystem::path;


			CreateDirectoryAndParentsTransactedAction::CreateDirectoryAndParentsTransactedAction(const std::filesystem::path& dirPath) :
				m_dirPath(dirPath),
				m_innerTransaction(),
				TransactedAction("Create dir (including parents) " + dirPath.string())
			{}

			CreateDirectoryAndParentsTransactedAction::~CreateDirectoryAndParentsTransactedAction()
			{
				// When we are destructed either rollback has already been called (so we commit nothing) or we do not want to rollback (so we rightfully commit the actions)
				m_innerTransaction.commit();
			}

			void CreateDirectoryAndParentsTransactedAction::execute()
			{
				const path& root = m_dirPath.root_path();
				path subpath = "";
				path::const_iterator iterator;

				// Skip root part of path
				for (iterator = m_dirPath.begin(); subpath < root && iterator != m_dirPath.end(); iterator++)
				{
					subpath /= *iterator;
				}
				for (; iterator != m_dirPath.end(); iterator++)
				{
					subpath /= *iterator;
					m_innerTransaction.addAction(
						std::make_unique<CreateDirectoryTransactedAction>(subpath, nullptr, true)
					);
				}
			}

			void CreateDirectoryAndParentsTransactedAction::rollback()
			{
				m_innerTransaction.rollback();
			}
		}
	}
}
