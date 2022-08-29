# PersistBOF
A tool to help automate common persistence mechanisms.  Currently supports Print Monitor (SYSTEM), Time Provider (Network Service), Start folder shortcut hijacking (User), and Junction Folder (User)

## Usage
Clone, run make, add .cna to Cobalt Strike client.

run: help persist-ice in CS console

Syntax:
- persist-ice [PrintMon, TimeProv, Shortcut, Junction] [persist or clean] [key/folder name] [dll / lnk exe name];


## Technique Overview
All of these techniques rely on a Dll file to be seperately placed on disk.  It is intentially not part of the BOF.

### Print Monitor
The Dll MUST be on disk and in a location in PATH (Dll search order) **BEFORE you run the BOF**.  It will fail otherwise.  The Dll will *immediately* be loaded by spoolsv.exe as SYSTEM.  This can be used to elevate from admin to SYSTEM as well as for persistence.  Will execute on system startup. **Must be elevated to run.**

- Demo Print Monitor Dll in project

Example:
1. upload NotMalware.dll to C:\Windows\NotMalware.dll
2. persist-ice PrintMon persist TotesLegitMonitor NotMalware.dll
3. Immediately executes as SYSTEM 
4. Will execute on startup until removed
5. persist-ice PrintMon clean TotesLegitMonitor C:\Windows\NotMalware.dll  > Will delete the registery keys and unload the Dll, then attempt to delete the dll if provided the correct path.  Should succeed.

### Time Provider
Loaded by svchost.exe as NETWORK SERVICE (get your potatoes ready!) on startup after running the BOF.  **Must be elevated to run.**

- Demo Time Provider Dll in project

Example:
- persist-ice TimeProv persist TotesLegitTimeProvider C:\anywhere\NotMalware.dll
- persist-ice TimeProv clean TotesLegitTimeProvider C:\anywhere\NotMalware.dll  > Will delete the registry keys and attempt to delete the dll if provided the correct path. Will probably fail because the dll is not unloaded by the process.

### Junction Folder
Same technique as demonstrated in Vault 7 leaks. Executed on user login.  Non-elevated.  Dll will be loaded into explorer.exe 

Example:

- persist-ice Juction persist TotesLegitFolder C:\user-writable-folder\NotMalware.dll **Save CLSID**
- persist-ice Juction clean TotesLegitFolder C:\user-writable-folder\NotMalware.dll 6be5e092-90cc-452d-be83-208029e259e0 > Will delete the registry keys, junction folder, and attempt to delete the dll. 


### Start Folder Hijack
Create a new, user writeable folder, copy a hijackable windows binary to the folder, then create a shortcut in the startup folder. Executed on user login. Non-elevated.

Example:

- persist-ice Shortcut persist C:\TotesLegitFolder C:\Windows\System32\Dism.exe > upload your Dll as a proxy dll to dismcore.dll into C:\TotesLegitFolder
- persist-ice Shortcut persist C:\TotesLegitFolder C:\Windows\System32\Dism.exe > Will attempt delete all files in new folder then delete the folder itself.  If the Dll is still loaded in the process then this will fail.



## References
https://stmxcsr.com/persistence/print-monitor.html

https://stmxcsr.com/persistence/time-provider.html

https://pentestlab.blog/2019/10/28/persistence-port-monitors/

https://blog.f-secure.com/hunting-for-junction-folder-persistence/

https://attack.mitre.org/techniques/T1547/010/

https://attack.mitre.org/techniques/T1547/003/

https://attack.mitre.org/techniques/T1547/009/
