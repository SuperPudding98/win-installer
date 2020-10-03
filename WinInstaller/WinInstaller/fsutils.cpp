#include "fsutils.h"
#include "winapi.h"


namespace mywininstaller
{
	namespace fsutils
	{
		using std::filesystem::path;


		void createDirectoryAndParentsTransacted(Transaction<path>& transaction, const path& dirPath)
		{
			const path& root = dirPath.root_path();
			path subpath = "";
			bool biggerThanRoot = false;
			for (const path& part : dirPath)
			{
				subpath /= part;
				if (biggerThanRoot || subpath > root)
				{
					// Caching this so we don't have to do lexicographic comparison each time.
					biggerThanRoot = true;

					if (winapi::createDirectoryThrows(subpath.c_str(), nullptr, true))
					{
						transaction.addAction(
							subpath,
							[](const path& p) { winapi::removeDirectoryThrows(p.c_str()); },
							"Create dir " + subpath.string()
						);
					}
				}
			}
		}


		void copyFileToDirTransacted(Transaction<path>& transaction, const path& fromFilePath, const path& toDirPath, bool overwrite)
		{
			path toFilePath = toDirPath / fromFilePath.filename();
			winapi::copyFileThrows(fromFilePath.c_str(), toFilePath.c_str(), overwrite);
			transaction.addAction(
				toFilePath,
				[](const path& p) { winapi::deleteFileThrows(p.c_str()); },
				"Copy file " + toFilePath.string()
			);
		}
	}
}
