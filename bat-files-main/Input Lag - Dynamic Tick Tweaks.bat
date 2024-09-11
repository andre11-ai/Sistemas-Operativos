@echo off
echo Hecho por Manuel
REM Este script se encarga de desactiva el dynamic tick de Windows que hace que cuando no está sucediendo nada se detiene el timer del sistema para ahorrar energía, y este archivo lo desactivo mejorando el input lag.
echo Este archivo mejora el tiempo de respuesta de los componentes como el mouse
bcdedit -set disabledynamictick yes
bcdedit -set useplatformtick yes
pause