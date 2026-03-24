#include "BStream.h"
#include "BOpcodeShell.h"

int main()
{
    TK_Status status;
    BStreamFileToolkit * tk = new BStreamFileToolkit;
 
	status = TK_Read_Stream_File("base_stream_all.hsf", tk);

	return 0;
}
 
