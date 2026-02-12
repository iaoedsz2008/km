
/**
 * 富强、民主、文明、和谐
 * 自由、平等、公正、法治
 * 爱国、敬业、诚信、友善
 **/

#if !defined(__eaa2bc062311653849e52543596ba34c__)
#define __eaa2bc062311653849e52543596ba34c__

static constexpr int DESCRIPTION_MAX_LENGTH = 0x100;
static constexpr int DESCRIPTION_MAX_COUNT = 0x1000;

void anylogPrintfA(const char* pszFormat, ...);

NTSTATUS anylogInit();

NTSTATUS anylogCleanup();

void anylogUpdate(HANDLE Pid, ULONG64 CR3);

#endif // !__eaa2bc062311653849e52543596ba34c__
