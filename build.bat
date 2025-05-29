IF NOT EXIST build\ (mkdir build\)

rc /fo build\winlofi.res src\res\winlofi.rc
cl /c src/main.c /Fo: build\winlofi.obj /std:clatest /WX
link build\winlofi.obj build\winlofi.res user32.lib shell32.lib /OUT:build\winlofi.exe
