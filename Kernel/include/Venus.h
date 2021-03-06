//-------------------------------------------------------
//@file: Venus.h
//@brief: core system include
//@author: venus
//@date: 2018/12/07-11:41
//-------------------------------------------------------

#ifndef __VENUS_H__
#define __VENUS_H__

#define VENUS_VERSION_MAJOR 1
#define VENUS_VERSION_MINOR 0
#define VENUS_VERSION_REVISION 0
#define VENUS_SDK_VERSION "1.0.0"

#include <stdio.h>

//system compile define
#include "compiler.h"

///core 
#include "venusTypes.h"
#include "TAllocator.h"
#include "venusMath.h"
#include "heapsort.h"
#include "fast_atof.h"
#include "venusString.h"
#include "venusArray.h"
#include "venusList.h"
#include "venusMap.h"

///3d
#include "vector2d.h"
#include "vector3d.h"
#include "line2d.h"
#include "line3d.h"
#include "matrix4.h"
#include "rect.h"
#include "triangle3d.h"
#include "quaternion.h"
#include "dimension2d.h"
#include "plane3d.h"
#include "position2d.h"

#include "IReferenceCounted.h"

#include "ITimer.h"
#include "IRandomizer.h"

//file attribute
#include "EAttributes.h"
#include "IAttributeExchangingObject.h"
#include "IAttributes.h"

#include "SColor.h"

///file
#include "path.h"
#include "IReadFile.h"
#include "IWriteFile.h"
#include "venusXML.h"
#include "IXMLReader.h"
#include "IXMLWriter.h"

#include "IFileList.h"
#include "IFileArchive.h"
#include "IFileSystem.h"

#include "ILogger.h"
#include "venusMutex.h"
#include "VenusThread.h"
#endif
