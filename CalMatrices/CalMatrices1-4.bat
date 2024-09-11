@echo off
setlocal enabledelayedexpansion

:start
cls
echo Calculadora de Matrices
echo.
echo 1.- Multiplicacion por escalar
echo 2.- Suma de matrices
echo 3.- Multiplicacion de matrices
echo 4.- Transpuesta de la matriz
echo 5.- Determinante de la matriz
echo.
set /p option="Elige el numero de la opcion que quieras: "

if "%option%" == "1" goto :escalar
if "%option%" == "2" goto :suma
if "%option%" == "3" goto :multiplicacion
if "%option%" == "4" goto :transpuesta
if "%option%" == "5" goto :determinante
echo. Opción no válida
pause
goto start

:seleccionar_matriz
echo Selecciona el tamaño de la matriz:
echo 1.- 2x2
echo 2.- 3x3
set /p size="Elige el numero de la opción que quieras: "
if "%size%" == "1" goto :leer_matriz_2x2
if "%size%" == "2" goto :leer_matriz_3x3
echo. Opción no válida
pause
goto seleccionar_matriz

:leer_matriz_2x2
echo Ingresa los valores de la matriz 2x2:
set /p m11="Valor 1: "
set /p m12="Valor 2: "
set /p m21="Valor 3: "
set /p m22="Valor 4: "
goto :eof

:leer_matriz_3x3
echo Ingresa los valores de la matriz 3x3:
set /p m11="Valor 1: "
set /p m12="Valor 2: "
set /p m13="Valor 3: "
set /p m21="Valor 4: "
set /p m22="Valor 5: "
set /p m23="Valor 6: "
set /p m31="Valor 7: "
set /p m32="Valor 8: "
set /p m33="Valor 9: "
goto :eof

:leer_segunda_matriz_2x2
echo Ingresa los valores de la segunda matriz 2x2:
set /p n11="Valor 1: "
set /p n12="Valor 2: "
set /p n21="Valor 3: "
set /p n22="Valor 4: "
goto :eof

:leer_segunda_matriz_3x3
echo Ingresa los valores de la segunda matriz 3x3:
set /p n11="Valor 1: "
set /p n12="Valor 2: "
set /p n13="Valor 3: "
set /p n21="Valor 4: "
set /p n22="Valor 5: "
set /p n23="Valor 6: "
set /p n31="Valor 7: "
set /p n32="Valor 8: "
set /p n33="Valor 9: "
goto :eof

:suma
cls
echo Suma de matrices
call :seleccionar_matriz

if "%size%" == "1" (
    call :leer_segunda_matriz_2x2
    set /a sum11=!m11! + !n11!
    set /a sum12=!m12! + !n12!
    set /a sum21=!m21! + !n21!
    set /a sum22=!m22! + !n22!
    echo El resultado de la suma es:
    echo [!sum11! !sum12!]
    echo [!sum21! !sum22!]
) else if "%size%" == "2" (
    call :leer_segunda_matriz_3x3
    set /a sum11=!m11! + !n11!
    set /a sum12=!m12! + !n12!
    set /a sum13=!m13! + !n13!
    set /a sum21=!m21! + !n21!
    set /a sum22=!m22! + !n22!
    set /a sum23=!m23! + !n23!
    set /a sum31=!m31! + !n31!
    set /a sum32=!m32! + !n32!
    set /a sum33=!m33! + !n33!
    echo El resultado de la suma es:
    echo [!sum11! !sum12! !sum13!]
    echo [!sum21! !sum22! !sum23!]
    echo [!sum31! !sum32! !sum33!]
)
pause
goto start

:transpuesta
cls
echo Transpuesta de la matriz
call :seleccionar_matriz

if "%size%" == "1" (
    echo El resultado de la transpuesta es:
    echo [!m11! !m21!]
    echo [!m12! !m22!]
) else if "%size%" == "2" (
    echo El resultado de la transpuesta es:
    echo [!m11! !m21! !m31!]
    echo [!m12! !m22! !m32!]
    echo [!m13! !m23! !m33!]
)
pause
goto start

:determinante
cls
echo Determinante de la matriz
call :seleccionar_matriz

if "%size%" == "1" (
    set /a det=!m11! * !m22! - !m12! * !m21!
    echo El determinante de la matriz 2x2 es: !det!
) else if "%size%" == "2" (
    set /a diagonal1=!m11! * !m22! * !m33!
    set /a diagonal2=!m12! * !n23! * !m31!
    set /a diagonal3=!m13! * !m21! * !m32!
    set /a diagonal4=!m13! * !m22! * !m31!
    set /a diagonal5=!m11! * !m23! * !m32!
    set /a diagonal6=!m12! * !m21! * !m33!
    
    set /a determinante=!diagonal1! + !diagonal2! + !diagonal3! - !diagonal4! - !diagonal5! - !diagonal6!
    echo El determinante de la matriz 3x3 es: !determinante!
)
pause
goto start

:escalar
cls
echo Multiplicacion de matriz por un escalar
call :seleccionar_matriz

set /p escalar="Ingresa el valor del escalar: "

if "%size%" == "1" (
    set /a esc11=!m11! * !escalar!
    set /a esc12=!m12! * !escalar!
    set /a esc21=!m21! * !escalar!
    set /a esc22=!m22! * !escalar!
    echo El resultado de la multiplicacion por el escalar es:
    echo [!esc11! !esc12!]
    echo [!esc21! !esc22!]
) else if "%size%" == "2" (
    set /a esc11=!m11! * !escalar!
    set /a esc12=!m12! * !escalar!
    set /a esc13=!m13! * !escalar!
    set /a esc21=!m21! * !escalar!
    set /a esc22=!m22! * !escalar!
    set /a esc23=!m23! * !escalar!
    set /a esc31=!m31! * !escalar!
    set /a esc32=!m32! * !escalar!
    set /a esc33=!m33! * !escalar!
    echo El resultado de la multiplicacion por el escalar es:
    echo [!esc11! !esc12! !esc13!]
    echo [!esc21! !esc22! !esc23!]
    echo [!esc31! !esc32! !esc33!]
)
pause
goto start

:multiplicacion
cls
echo Multiplicacion de matrices
call :seleccionar_matriz

if "%size%" == "1" (
    call :leer_segunda_matriz_2x2
    set /a prod11=!m11! * !n11! + !m12! * !n21!
    set /a prod12=!m11! * !n12! + !m12! * !n22!
    set /a prod21=!m21! * !n11! + !m22! * !n21!
    set /a prod22=!m21! * !n12! + !m22! * !n22!
    echo El resultado de la multiplicación es:
    echo [!prod11! !prod12!]
    echo [!prod21! !prod22!]
) else if "%size%" == "2" (
    call :leer_segunda_matriz_3x3
    set /a prod11=!m11! * !n11! + !m12! * !n21! + !m13! * !n31!
    set /a prod12=!m11! * !n12! + !m12! * !n22! + !m13! * !n32!
    set /a prod13=!m11! * !n13! + !m12! * !n23! + !m13! * !n33!
    set /a prod21=!m21! * !n11! + !m22! * !n21! + !m23! * !n31!
    set /a prod22=!m21! * !n12! + !m22! * !n22! + !m23! * !n32!
    set /a prod23=!m21! * !n13! + !m22! * !n23! + !m23! * !n33!
    set /a prod31=!m31! * !n11! + !m32! * !n21! + !m33! * !n31!
    set /a prod32=!m31! * !n12! + !m32! * !n22! + !m33! * !n32!
    set /a prod33=!m31! * !n13! + !m32! * !n23! + !m33! * !n33!
    echo El resultado de la multiplicación es:
    echo [!prod11! !prod12! !prod13!]
    echo [!prod21! !prod22! !prod23!]
    echo [!prod31! !prod32! !prod33!]
)
pause
goto start

:eof
goto :eof

