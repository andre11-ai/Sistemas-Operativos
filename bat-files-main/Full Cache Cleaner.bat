@echo off
echo Hecho por Manuel
color 0A
echo Este archivo se encarga de eliminar todo el caché de Windowsm, archivos temporales, basura, historia, cookies, 
/s /f /q c:\windows\temp\*.*
rd /s /q c:\windows\temp
md c:\windows\temp
del /s /f /q C:\WINDOWS\Prefetch
del /s /f /q %temp%\*.*
rd /s /q %temp%
md %temp%
deltree /y c:\windows\tempor~1
deltree /y c:\windows\temp
deltree /y c:\windows\tmp
deltree /y c:\windows\ff*.tmp
deltree /y c:\windows\history
deltree /y c:\windows\cookies
deltree /y c:\windows\recent
deltree /y c:\windows\spool\printers
del c:\WIN386.SWP
cls

REM Estos siguientes comandos se encargar de llamar una función ejectuable que llama a la información de archivos y eventos de registro, para después utilizar la función de limpiar "do_clear" para eliminar estos archivos de registro, optimizando el almacenamiento.
FOR /F "tokens=1, 2 * " %%V IN ('bcdedit') DO SET adminTest=%%V
IF (%adminTest%)==(Access) goto noAdmin
for /F " tokens=*" %%G in ('wevtutil.exe el') DO (call :do_clear "%%G")
echo.
echo Se limpiaron todos los archivos temporales ^<press any key^>
goto theEnd
:do_clear
echo clearing %1
wevtutil.exe cl %1
goto :eof
:noAdmin
echo Es necesario ejecutar el archivo como administrador
echo ^<press any key^>
cls
pause
