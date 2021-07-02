#include <iostream>
#include <windows.h>
#include <winreg.h>

using namespace std;

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

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (string(argv[1]) == "-h" || string(argv[1]) == "-H" || string(argv[1]) == "/h" || string(argv[1]) == "/H")
		{
			cout << "Usage:\n-U : Unlimited\t(Constantly attempting to abort the shutdown.)\n-L : Limited\t(Closes after the first successful attempt to abort the shutdown.)";
		}
		else if (string(argv[1]) == "-U" || string(argv[1]) == "-u")
		{
			cout << "Running..." <<endl;
			while (1)
			{
				PreventSystemShutdown();
			}
		}
		else if (string(argv[1]) == "-L" || string(argv[1]) == "-l")
		{
			cout << "Running..." <<endl;
			while (1)
			{
				bool result = PreventSystemShutdown();
				if (result == false){}
				if (result == true)
				{
					cout << "Done.";
					break;
				}
			}
		}
		else
		{
			cout << "Usage:\n-U : Unlimited\t(Constantly attempting to abort the shutdown.)\n-L : Limited\t(Closes after the first successful attempt to abort the shutdown.)";
		}
	}
	else
	{
		cout << "Usage:\n-U : Unlimited\t(Constantly attempting to abort the shutdown.)\n-L : Limited\t(Closes after the first successful attempt to abort the shutdown.)";
	}
	return 0;
}
/* How to compile!
windres Shutdown-Guard.rc -o Shutdown-Guard.o
g++ -o Shutdown-Guard.exe Shutdown-Guard.cpp Shutdown-Guard.o
*/