//-------------------------------------------------------
//@file: IXMLReader.h
//@brief: xml file reader
//@author: venus
//@date: 2018/12/07-18:00
//-------------------------------------------------------
#ifndef __I_XML_READER_H_INCLUDED__
#define __I_XML_READER_H_INCLUDED__

#include "IReferenceCounted.h"
#include "venusXML.h"

namespace venus
{
	namespace io
	{
		//! An xml reader for wide characters, derived from IReferenceCounted.
		/** This XML Parser can read any type of text files from any source
		Irrlicht can read. Just call IFileSystem::createXMLReader(). For more
		informations on how to use the parser, see IIrrXMLReader */
		typedef IVenusXMLReader<wchar_t, IReferenceCounted> IXMLReader;

		//! An xml reader for ASCII or UTF-8 characters, derived from IReferenceCounted.
		/** This XML Parser can read any type of text files from any source
		Irrlicht can read. Just call IFileSystem::createXMLReaderUTF8(). For
		more informations on how to use the parser, see IIrrXMLReader */
		typedef IVenusXMLReader<c8, IReferenceCounted> IXMLReaderUTF8;

	} // end namespace io
} // end namespace venus

#endif

