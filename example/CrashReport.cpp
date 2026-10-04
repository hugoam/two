//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

// with TWO_NO_CRASH_DIALOG set, assertions, aborts and crashes print their message and a stack trace to stderr and exit,
// instead of popping a dialog: so that a run without a human in front of it can tell what went wrong

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <dbghelp.h>
#include <crtdbg.h>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <atomic>

#pragma comment(lib, "dbghelp.lib")

namespace
{
	std::atomic<bool> g_reporting{ false };

	void print_address(HANDLE process, DWORD64 address)
	{
		alignas(SYMBOL_INFO) char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME];
		SYMBOL_INFO* symbol = reinterpret_cast<SYMBOL_INFO*>(buffer);
		symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
		symbol->MaxNameLen = MAX_SYM_NAME;

		DWORD64 displacement = 0;
		const char* name = SymFromAddr(process, address, &displacement, symbol) ? symbol->Name : "?";

		IMAGEHLP_LINE64 line = {};
		line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
		DWORD offset = 0;
		if(SymGetLineFromAddr64(process, address, &offset, &line))
			fprintf(stderr, "    %s  %s(%lu)\n", name, line.FileName, line.LineNumber);
		else
			fprintf(stderr, "    %s  0x%llx\n", name, address);
	}

	void print_stack(CONTEXT context)
	{
		HANDLE process = GetCurrentProcess();
		HANDLE thread = GetCurrentThread();
		SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES);
		SymInitialize(process, nullptr, TRUE);

		STACKFRAME64 frame = {};
		frame.AddrPC.Offset = context.Rip;
		frame.AddrPC.Mode = AddrModeFlat;
		frame.AddrFrame.Offset = context.Rbp;
		frame.AddrFrame.Mode = AddrModeFlat;
		frame.AddrStack.Offset = context.Rsp;
		frame.AddrStack.Mode = AddrModeFlat;

		fprintf(stderr, "[crash] stack:\n");
		for(int i = 0; i < 64; ++i)
		{
			if(!StackWalk64(IMAGE_FILE_MACHINE_AMD64, process, thread, &frame, &context, nullptr, SymFunctionTableAccess64, SymGetModuleBase64, nullptr))
				break;
			if(frame.AddrPC.Offset == 0)
				break;
			print_address(process, frame.AddrPC.Offset);
		}
	}

	void print_current_stack()
	{
		CONTEXT context = {};
		RtlCaptureContext(&context);
		print_stack(context);
	}

	[[noreturn]] void report_and_exit(const char* what, const char* message)
	{
		if(g_reporting.exchange(true))
			_exit(3);
		fflush(stdout);
		fprintf(stderr, "[crash] %s%s%s\n", what, message ? ": " : "", message ? message : "");
		print_current_stack();
		fflush(stderr);
		_exit(3);
	}

	int crt_report(int type, char* message, int* result)
	{
		if(type == _CRT_WARN)
		{
			fputs(message, stderr);
			*result = 0;
			return TRUE;
		}
		report_and_exit(type == _CRT_ASSERT ? "assertion failed" : "crt error", message);
	}

	LONG WINAPI unhandled_exception(EXCEPTION_POINTERS* exception)
	{
		if(g_reporting.exchange(true))
			return EXCEPTION_EXECUTE_HANDLER;
		fflush(stdout);
		const EXCEPTION_RECORD& record = *exception->ExceptionRecord;
		fprintf(stderr, "[crash] unhandled exception 0x%08lx at 0x%p\n", record.ExceptionCode, record.ExceptionAddress);
		if(record.ExceptionCode == EXCEPTION_ACCESS_VIOLATION && record.NumberParameters >= 2)
			fprintf(stderr, "[crash] %s address 0x%llx\n", record.ExceptionInformation[0] ? "writing" : "reading", (unsigned long long)record.ExceptionInformation[1]);
		print_stack(*exception->ContextRecord);
		fflush(stderr);
		_exit(3);
	}

	void invalid_parameter(const wchar_t*, const wchar_t*, const wchar_t*, unsigned int, uintptr_t)
	{
		report_and_exit("invalid parameter passed to a crt function", nullptr);
	}
}

void install_crash_report()
{
	if(!getenv("TWO_NO_CRASH_DIALOG"))
		return;

	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
	SetUnhandledExceptionFilter(unhandled_exception);

	_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL, crt_report);
	_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
	signal(SIGABRT, [](int) { report_and_exit("abort", nullptr); });
	_set_invalid_parameter_handler(invalid_parameter);
	_set_purecall_handler([]() { report_and_exit("pure virtual function call", nullptr); });
}

#else

void install_crash_report() {}

#endif
