#include "pre_compile.h"


#include "Exception.h"
#include "Console.h"

using namespace Base;


TYPESYSTEM_SOURCE(Base::Exception,Base::BaseClass);


Exception::Exception(void)
{
  _sErrMsg = "FreeCAD Exception";
}

Exception::Exception(const Exception &inst)
 : BaseClass(),_sErrMsg(inst._sErrMsg)
{
}


Exception::Exception(const char * sMessage)
 : _sErrMsg(sMessage)
{
}

Exception::Exception(const std::string& sMessage)
 : _sErrMsg(sMessage)
{
}

Exception &Exception::operator=(const Exception &inst)
{
  _sErrMsg = inst._sErrMsg;
  return *this;
}

const char* Exception::what(void) const throw()
{
    return _sErrMsg.c_str();
}

void Exception::ReportException (void) const
{
    Console().Error("Exception (%s): %s \n",Console().Time(),what());
}

// ---------------------------------------------------------

AbortException::AbortException(const char * sMessage)
  : Exception( sMessage )
{
}

AbortException::AbortException()
{
    _sErrMsg = "Aborted operation";
}

AbortException::AbortException(const AbortException &inst)
 : Exception(inst)
{
}

const char* AbortException::what() const throw()
{
    return Exception::what();
}

// ---------------------------------------------------------

FileException::FileException(const char * sMessage, const char * sFileName)
  : Exception( sMessage ),file(sFileName)
{
    _sErrMsg += ": ";
    _sErrMsg += sFileName;
}

FileException::FileException(const char * sMessage, const FileInfo& File)
  : Exception( sMessage ),file(File)
{
    _sErrMsg += ": ";
    _sErrMsg += File.fileName();
}

FileException::FileException()
  : Exception( "Unknown file exeption happened" )
{
}

FileException::FileException(const FileException &inst)
  : Exception( inst._sErrMsg.c_str() ),file(inst.file)
{
}

const char* FileException::what() const throw()
{
    return Exception::what();
}

// ---------------------------------------------------------

MemoryException::MemoryException()
{
    _sErrMsg = "Not enough memory available";
}

MemoryException::MemoryException(const MemoryException &inst)
#if defined (__GNUC__)
 : std::bad_alloc(), Exception(inst) 
#else
 : Exception(inst)
#endif
{
}

#if defined (__GNUC__)
const char* MemoryException::what() const throw()
{
    // call what() of Exception, not of std::bad_alloc
    return Exception::what();
}
#endif

