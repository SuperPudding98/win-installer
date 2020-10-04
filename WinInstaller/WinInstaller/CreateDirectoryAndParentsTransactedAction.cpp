#include "CreateDirectoryAndParentsTransactedAction.h"
#include "CreateDirectoryTransactedAction.h"
#include "Win32Error.h"


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
					try
					{
						m_innerTransaction.addAction(
							std::make_unique<CreateDirectoryTransactedAction>(subpath)
						);
					}
					catch (const winapi::Win32Error& e)
					{
						// If a parent dir exists we can ignore error and move to next dir
						if (e.getErrorCode() != ERROR_ALREADY_EXISTS)
						{
							throw;
						}
					}
				}
			}

			void CreateDirectoryAndParentsTransactedAction::rollback()
			{
				m_innerTransaction.rollback();
			}
		}
	}
}
