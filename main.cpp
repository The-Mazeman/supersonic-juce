#include <iostream>
#if 0
#define JUCE_STRING_UTF_TYPE 8
#include <juce_core/system/juce_StandardHeader.h>
#include <juce_core/memory/juce_Atomic.h>
#include <juce_core/memory/juce_Memory.h>
#include <juce_core/maths/juce_MathsFunctions.h>
#include <juce_core/text/juce_CharacterFunctions.h>
#include <juce_core/text/juce_CharPointer_UTF8.h>
#include <juce_core/text/juce_CharPointer_UTF16.h>
#include <juce_core/text/juce_CharPointer_UTF32.h>
#include <juce_core/text/juce_CharPointer_ASCII.h>
namespace juce
{
    class StringRef;
    class OutputStream;
}
#include <juce_core/text/juce_String.h>
#include <juce_core/memory/juce_HeapBlock.h>
#include <juce_core/memory/juce_LeakedObjectDetector.h>
#include <juce_core/memory/juce_MemoryBlock.h>
#include <juce_core/text/juce_StringRef.h>
#include <juce_core/streams/juce_InputStream.h>
#include <juce_core/time/juce_RelativeTime.h>
#include <juce_core/time/juce_Time.h>
#include <juce_core/misc/juce_Result.h>
#include <juce_core/threads/juce_ScopedLock.h>
#include <juce_core/threads/juce_CriticalSection.h>
#include <juce_core/containers/juce_ArrayBase.h>
#include <juce_core/containers/juce_ElementComparator.h>
#include <juce_core/containers/juce_Array.h>
#include <juce_core/text/juce_StringArray.h>
namespace juce
{
    class FileInputStream;
    class FileOutputStream;
}
#include <juce_core/files/juce_File.h>
#include <juce_core/detail/juce_NativeFileHandle.h>
#include <juce_core/text/juce_NewLine.h>
#include <juce_core/files/juce_FileInputStream.h>
#include <juce_core/streams/juce_OutputStream.h>
#include <juce_core/files/juce_FileOutputStream.h>
#endif

#include <juce_gui_basics/juce_gui_basics.h>
#include "application.hpp"

START_JUCE_APPLICATION(Application)
