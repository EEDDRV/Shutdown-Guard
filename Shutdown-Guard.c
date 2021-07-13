#include <stdio.h>
#include <stdbool.h>
#include <windows.h>


BOOL PreventSystemShutdown()
{
   HANDLE hToken;              // handle to process token 
   TOKEN_PRIVILEGES tkp;       // pointer to token structure 
 
   // Get the current process token handle  so we can get shutdown 
   // privilege. 
 
   if (!OpenProcessToken(GetCurrentProcess(), 
         TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
      return FALSE; 
 
   // Get the LUID for shutdown privilege. 
 
   LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, 
         &tkp.Privileges[0].Luid); 
 
   tkp.PrivilegeCount = 1;  // one privilege to set    
   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
 
   // Get shutdown privilege for this process. 
 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
        (PTOKEN_PRIVILEGES)NULL, 0); 
 
   if (GetLastError() != ERROR_SUCCESS) 
      return FALSE; 
 
   // Prevent the system from shutting down. 
 
   if ( !AbortSystemShutdown(NULL) ) 
      return FALSE; 
 
   // Disable shutdown privilege. 
 
   tkp.Privileges[0].Attributes = 0; 
   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
       (PTOKEN_PRIVILEGES) NULL, 0); 
 
   return TRUE;
}

int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		if (argv[1][1] == 'h' || argv[1][1] == 'H')// || argv[1] == "/h" || argv[1] == "-H" || argv[1] == "/H")
		{
			printf("Usage:\n-U : Unlimited\t(Constantly attempting to abort the shutdown.)\n-L : Limited\t(Closes after the first successful attempt to abort the shutdown.)");
		}
		else if (argv[1][1] == 'U' || argv[1][1] == 'u')
		{
			printf("Running...\n");
			while (1)
			{
				PreventSystemShutdown();
			}
		}
		else if (argv[1][1] == 'L' || argv[1][1] == 'l')
		{
			printf("Running...\n");
			while (1)
			{
				bool result = PreventSystemShutdown();
				if (result == false){}
				if (result == true)
				{
					printf("Done.");
					break;
				}
			}
		}
		// Now add an 'Efficiency' option.
		else if (argv[1][1] == 'E' || argv[1][1] == 'e')
		{
			printf("Running (in efficiency mode)...\n");
			while (1)
			{
				PreventSystemShutdown();
				// Now pause for one thousandth of a second.
				Sleep(1);
			}
		}
		else
		{
			printf("Usage:\n-U : Unlimited\t(Constantly attempting to abort the shutdown.)\n-L : Limited\t(Closes after the first successful attempt to abort the shutdown.)\n-E : Efficiency\t(Constantly attempting to abort the shutdown every 0.001 of a second.)");
		}
	}
	else
	{
		printf("Usage:\n-U : Unlimited\t(Constantly attempting to abort the shutdown.)\n-L : Limited\t(Closes after the first successful attempt to abort the shutdown.)");
	}
	return 0;
}
/* How to compile!
windres Shutdown-Guard.rc -o Shutdown-Guard.o
gcc -o Shutdown-Guard.exe Shutdown-Guard.c Shutdown-Guard.o
*/