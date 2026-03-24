#ifndef BASE_EXCEPTION_HHHHHHHHH
#define BASE_EXCEPTION_HHHHHHHHH

#include <exception>
#include <string>
#include "FileInfo.h"
#include "BaseClass.h"

namespace Base
{

class BASE_EXPORT Exception : public BaseClass
{
  TYPESYSTEM_HEADER();

public:
  Exception(const char * sMessage);
  Exception(const std::string& sMessage);
  Exception(void);
  Exception(const Exception &inst);
  virtual ~Exception() throw() {}

  Exception &operator=(const Exception &inst);
  virtual const char* what(void) const throw();
  void ReportException (void) const;
  inline void setMessage(const char * sMessage);
  inline void setMessage(const std::string& sMessage);
  
protected:
  std::string _sErrMsg;
};


/**
 * The AbortException is thrown if a pending operation was aborted.
 * @author Werner Mayer
 */
class BASE_EXPORT AbortException : public Exception
{
public:
  /// Construction
  AbortException(const char * sMessage);
  /// Construction
  AbortException();
  /// Construction
  AbortException(const AbortException &inst);
  /// Destruction
  virtual ~AbortException() throw() {}
  /// Description of the exception
  virtual const char* what() const throw();
};

/** File exception handling class
 * This class is specialized to go with exception thrown in case of File IO Problems.
 * @author Juergen Riegel
 */
class BASE_EXPORT FileException : public Exception
{
public:
  /// With massage and file name
  FileException(const char * sMessage, const char * sFileName=0);
  /// With massage and file name
  FileException(const char * sMessage, const FileInfo& File);
  /// standard construction
  FileException();
  /// Construction
  FileException(const FileException &inst);
  /// Destruction
  virtual ~FileException() throw() {}
  /// Description of the exception
  virtual const char* what() const throw();
protected:
  FileInfo file;
};

/**
 * The MemoryException is thrown if not enough memory can be allocated.
 * @author Werner Mayer
 */
#if defined (__GNUC__)
// It seems that the calling instance of our new handler expects a bad_alloc exception
class BaseExport MemoryException : public Exception, virtual public std::bad_alloc
#else
class BASE_EXPORT MemoryException : public Exception
#endif
{
public:
  /// Construction
  MemoryException();
  /// Construction
  MemoryException(const MemoryException &inst);
  /// Destruction
  virtual ~MemoryException() throw() {}
#if defined (__GNUC__)
  /// Description of the exception
  virtual const char* what() const throw();
#endif
};


inline void Exception::setMessage(const char * sMessage)
{
  _sErrMsg = sMessage;
}

inline void Exception::setMessage(const std::string& sMessage)
{
  _sErrMsg = sMessage;
}


} //namespace Base

#endif // BASE_EXCEPTION_HHHHHHHHH

