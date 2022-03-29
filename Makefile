icepick:
	x86_64-w64-mingw32-gcc -c PersistenceBOF.c -o persist-ice-monitor.o -DPRINTMONITOR 
	x86_64-w64-mingw32-strip -N PersistenceBOF.c persist-ice-monitor.o
	x86_64-w64-mingw32-gcc -c PersistenceBOF.c -o persist-ice-time.o -DTIME
	x86_64-w64-mingw32-strip -N PersistenceBOF.c persist-ice-time.o
	x86_64-w64-mingw32-gcc -c PersistenceBOF.c -o persist-ice-shortcut.o -DShortCutStartup
	x86_64-w64-mingw32-strip -N PersistenceBOF.c persist-ice-shortcut.o
	x86_64-w64-mingw32-gcc -c PersistenceBOF.c -o persist-ice-junction.o -DJUNCTION
	x86_64-w64-mingw32-strip -N PersistenceBOF.c persist-ice-junction.o 
