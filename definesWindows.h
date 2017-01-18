#pragma once

#include "definesCrossPlatform.h"

#ifdef _DEBUG
	#define ASSERT \
		if ( false ) {} \
		else \
		struct LocalAssert { \
				int32 mLine; \
				LocalAssert(int32 line=__LINE__) : mLine(line) {} \
				LocalAssert(bool isOK, const tstring & message = _TT("")) { \
				if ( !isOK ) { \
				tstringstream buffer; \
				buffer  << _TT("ERROR!! Assert failed on line ") \
						<< LocalAssert().mLine << _TT(" in file \""); \
				buffer  << __FILE__ << _TT("\", message: \"") \
						<< message << _TT("\"\n"); \
				tprintf(buffer.str().c_str()); \
				__asm { int 3 } \
				} \
			} \
		} myAsserter = LocalAssert
#else
	#define ASSERT \
		if ( true ) {} else \
		struct NoAssert { \
				NoAssert(bool isOK, const tstring & message = _TT("")) {} \
		} myAsserter = NoAssert
#endif
