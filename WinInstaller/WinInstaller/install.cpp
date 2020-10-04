#include "config.h"
#include "Transaction.h"
#include "CreateDirectoryAndParentsTransactedAction.h"
#include "CopyFileToDirectoryTransactedAction.h"
#include <filesystem>


namespace mywininstaller
{
	using std::filesystem::path;
	using namespace transactions;
	using namespace transactions::filesystem;


	void install()
	{
		Transaction transaction;
		
		transaction.addAction(
			std::make_unique<CreateDirectoryAndParentsTransactedAction>(config::InstallDir)
		);

		for (const path& file : config::InstalledFiles)
		{
			transaction.addAction(
				std::make_unique<CopyFileToDirectoryTransactedAction>(file, config::InstallDir, config::OverwriteIfExists)
			);
		}

		transaction.commit();
	}
}
