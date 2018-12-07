//-------------------------------------------------------
//@file: path.h
//@brief: file system path 
//@author: venus
//@date: 2018/12/07-17:59
//-------------------------------------------------------
#ifndef __PATH_H_INCLUDED__
#define __PATH_H_INCLUDED__

#include "venusString.h"

namespace venus
{
	namespace io
	{

		//! Type used for all file system related strings.
		/** This type will transparently handle different file system encodings. */
		typedef core::string<fschar_t> path;

		//! Used in places where we identify objects by a filename, but don't actually work with the real filename
		/** Venus is internally not case-sensitive when it comes to names.
			Also this class is a first step towards support for correctly serializing renamed objects.
		*/
		struct SNamedPath
		{
			//! Constructor
			SNamedPath() {}

			//! Constructor
			SNamedPath(const path& p) : Path(p), InternalName(PathToName(p))
			{
			}

			//! Is smaller comparator
			bool operator <(const SNamedPath& other) const
			{
				return InternalName < other.InternalName;
			}

			//! Set the path.
			void setPath(const path& p)
			{
				Path = p;
				InternalName = PathToName(p);
			}

			//! Get the path.
			const path& getPath() const
			{
				return Path;
			};

			//! Get the name which is used to identify the file.
			//! This string is similar to the names and filenames used before Venus 1.7
			const path& getInternalName() const
			{
				return InternalName;
			}

			//! Implicit cast to io::path
			operator core::stringc() const
			{
				return core::stringc(getPath());
			}
			//! Implicit cast to io::path
			operator core::stringw() const
			{
				return core::stringw(getPath());
			}

		protected:
			// convert the given path string to a name string.
			path PathToName(const path& p) const
			{
				path name(p);
				name.replace('\\', '/');
				name.make_lower();
				return name;
			}

		private:
			path Path;
			path InternalName;
		};

	} // namespace io
} // namespace venus

#endif // __PATH_H_INCLUDED__
