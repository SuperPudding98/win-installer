#include "config.h"
#include "Transaction.h"
#include "fsutils.h"
#include <filesystem>


namespace mywininstaller
{
	using std::filesystem::path;

	void install()
	{
		Transaction<path> transaction;

		fsutils::createDirectoryAndParentsTransacted(transaction, config::InstallDir);
		for (const path& file : config::InstalledFiles)
		{
			fsutils::copyFileToDirTransacted(transaction, file, config::InstallDir, config::OverwriteIfExists);
		}

		transaction.commit();
	}
}
