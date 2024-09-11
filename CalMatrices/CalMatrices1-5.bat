@echo off
:: S.O. AGREVAl
:: Fecha: 06/09/2024
:: Este programa realiza operaciones con matrices, incluyendo:
:: multiplicación por escalar, suma de matrices, multiplicación de matrices,
:: transposición de matrices y cálculo de determinantes.
::AYALA SANCHEZ ANDRE EDUARDO
::HERRERA PELCASTRE HUGO ALEJANDRO 
::LOPEZ REYES LUIS DANIEL
::RODRÍGUEZ MIRANDA PAULINA
::TORRES PINEDA JESUS


@echo off
setlocal enabledelayedexpansion

:start
cls
echo ===============================================================================
echo               Calculadora de Matrices - S O AGREVAl
echo ===============================================================================
echo 1.- Multiplicación por escalar
echo 2.- Suma de matrices
echo 3.- Multiplicación de matrices
echo 4.- Transpuesta de la matriz
echo 5.- Determinante de la matriz
echo 6.- Salir
echo ===============================================================================
set /p option="Elige el número de la opción que quieras: "

if "%option%" == "1" goto :escalar
if "%option%" == "2" goto :suma
if "%option%" == "3" goto :multiplicacion
if "%option%" == "4" goto :transpuesta
if "%option%" == "5" goto :determinante
if "%option%" == "6" goto :fin
echo. Opción no válida
pause
goto start

:seleccionar_matriz
echo ===============================================================================
echo                             Selección de Tamaño de Matriz
echo ===============================================================================
echo 1.- Matriz 2x2
echo 2.- Matriz 3x3
echo ===============================================================================
set /p size="Elige el tamaño de la matriz (1 o 2): "

if "%size%" == "1" goto :leer_matriz_2x2
if "%size%" == "2" goto :leer_matriz_3x3
echo. Opción no válida
pause
goto seleccionar_matriz

:leer_matriz_2x2
cls
echo ===============================================================================
echo                             Estructura de la Matriz 2x2
echo ===============================================================================
echo [ 1  2 ]
echo [ 3  4 ]
echo ------------------------------------------------------------------------------
echo Ingresa los valores de la matriz 2x2:
set /p m11="Valor 1 [1,1]: "
set /p m12="Valor 2 [1,2]: "
set /p m21="Valor 3 [2,1]: "
set /p m22="Valor 4 [2,2]: "
goto :eof

:leer_matriz_3x3
cls
echo ===============================================================================
echo                             Estructura de la Matriz 3x3
echo ===============================================================================
echo [ 1  2  3 ]
echo [ 4  5  6 ]
echo [ 7  8  9 ]
echo ------------------------------------------------------------------------------
echo Ingresa los valores de la matriz 3x3:
set /p m11="Valor 1 [1,1]: "
set /p m12="Valor 2 [1,2]: "
set /p m13="Valor 3 [1,3]: "
set /p m21="Valor 4 [2,1]: "
set /p m22="Valor 5 [2,2]: "
set /p m23="Valor 6 [2,3]: "
set /p m31="Valor 7 [3,1]: "
set /p m32="Valor 8 [3,2]: "
set /p m33="Valor 9 [3,3]: "
goto :eof

:leer_segunda_matriz_2x2
cls
echo ===============================================================================
echo                             Ingreso de Segunda Matriz 2x2
echo ===============================================================================
echo [ 1  2 ]
echo [ 3  4 ]
echo ------------------------------------------------------------------------------
set /p n11="Valor 1 [1,1]: "
set /p n12="Valor 2 [1,2]: "
set /p n21="Valor 3 [2,1]: "
set /p n22="Valor 4 [2,2]: "
goto :eof

:leer_segunda_matriz_3x3
cls
echo ===============================================================================
echo                             Ingreso de Segunda Matriz 3x3
echo ===============================================================================
echo [ 1  2  3 ]
echo [ 4  5  6 ]
echo [ 7  8  9 ]
echo ------------------------------------------------------------------------------
set /p n11="Valor 1 [1,1]: "
set /p n12="Valor 2 [1,2]: "
set /p n13="Valor 3 [1,3]: "
set /p n21="Valor 4 [2,1]: "
set /p n22="Valor 5 [2,2]: "
set /p n23="Valor 6 [2,3]: "
set /p n31="Valor 7 [3,1]: "
set /p n32="Valor 8 [3,2]: "
set /p n33="Valor 9 [3,3]: "
goto :eof

:suma
cls
echo ===============================================================================
echo                             Suma de Matrices
echo ===============================================================================
call :seleccionar_matriz

if "%size%" == "1" (
    call :leer_segunda_matriz_2x2
    set /a sum11=!m11! + !n11!
    set /a sum12=!m12! + !n12!
    set /a sum21=!m21! + !n21!
    set /a sum22=!m22! + !n22!
    echo ------------------------------------------------------------------------------
    echo El resultado de la suma es:
    echo [ !sum11!  !sum12! ]
    echo [ !sum21!  !sum22! ]
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto suma
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
    echo ------------------------------------------------------------------------------
    echo El resultado de la suma es:
    echo [ !sum11!  !sum12!  !sum13! ]
    echo [ !sum21!  !sum22!  !sum23! ]
    echo [ !sum31!  !sum32!  !sum33! ]
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto suma
)
pause
goto start

:transpuesta
cls
echo ===============================================================================
echo                             Transpuesta de la Matriz
echo ===============================================================================
call :seleccionar_matriz

if "%size%" == "1" (
    echo ------------------------------------------------------------------------------
    echo La transpuesta de la matriz es:
    echo [ !m11!  !m21! ]
    echo [ !m12!  !m22! ]
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto transpuesta
) else if "%size%" == "2" (
    echo ------------------------------------------------------------------------------
    echo La transpuesta de la matriz es:
    echo [ !m11!  !m21!  !m31! ]
    echo [ !m12!  !m22!  !m32! ]
    echo [ !m13!  !m23!  !m33! ]
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto transpuesta
)
pause
goto start

:determinante
cls
echo ===============================================================================
echo                             Determinante de la Matriz
echo ===============================================================================
call :seleccionar_matriz

if "%size%" == "1" (
    set /a det=!m11! * !m22! - !m12! * !m21!
    echo ------------------------------------------------------------------------------
    echo El determinante de la matriz 2x2 es: !det!
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto determinante
) else if "%size%" == "2" (
    set /a diagonal1=!m11! * !m22! * !m33!
    set /a diagonal2=!m12! * !m23! * !m31!
    set /a diagonal3=!m13! * !m21! * !m32!
    set /a diagonal4=!m13! * !m22! * !m31!
    set /a diagonal5=!m11! * !m23! * !m32!
    set /a diagonal6=!m12! * !m21! * !m33!
    set /a determinante=!diagonal1! + !diagonal2! + !diagonal3! - !diagonal4! - !diagonal5! - !diagonal6!
    echo ------------------------------------------------------------------------------
    echo El determinante de la matriz 3x3 es: !determinante!
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto determinante
)
pause
goto start

:multiplicacion
cls
echo ===============================================================================
echo                          Multiplicación de Matrices
echo ===============================================================================
call :seleccionar_matriz

if "%size%" == "1" (
    call :leer_segunda_matriz_2x2
    set /a prod11=!m11! * !n11! + !m12! * !n21!
    set /a prod12=!m11! * !n12! + !m12! * !n22!
    set /a prod21=!m21! * !n11! + !m22! * !n21!
    set /a prod22=!m21! * !n12! + !m22! * !n22!
    echo ------------------------------------------------------------------------------
    echo El resultado de la multiplicación es:
    echo [ !prod11!  !prod12! ]
    echo [ !prod21!  !prod22! ]
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto multiplicacion
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
    echo ------------------------------------------------------------------------------
    echo El resultado de la multiplicación es:
    echo [ !prod11!  !prod12!  !prod13! ]
    echo [ !prod21!  !prod22!  !prod23! ]
    echo [ !prod31!  !prod32!  !prod33! ]
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto multiplicacion
)
pause
goto start

:escalar
cls
echo ===============================================================================
echo                         Multiplicación por Escalar
echo ===============================================================================
call :seleccionar_matriz

set /p escalar="Ingrese el valor del escalar: "

if "%size%" == "1" (
    set /a prod11=!m11! * !escalar!
    set /a prod12=!m12! * !escalar!
    set /a prod21=!m21! * !escalar!
    set /a prod22=!m22! * !escalar!
    echo ------------------------------------------------------------------------------
    echo El resultado de la multiplicación es:
    echo [ !prod11!  !prod12! ]
    echo [ !prod21!  !prod22! ]
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto escalar
) else if "%size%" == "2" (
    set /a prod11=!m11! * !escalar!
    set /a prod12=!m12! * !escalar!
    set /a prod13=!m13! * !escalar!
    set /a prod21=!m21! * !escalar!
    set /a prod22=!m22! * !escalar!
    set /a prod23=!m23! * !escalar!
    set /a prod31=!m31! * !escalar!
    set /a prod32=!m32! * !escalar!
    set /a prod33=!m33! * !escalar!
    echo ------------------------------------------------------------------------------
    echo El resultado de la multiplicación es:
    echo [ !prod11!  !prod12!  !prod13! ]
    echo [ !prod21!  !prod22!  !prod23! ]
    echo [ !prod31!  !prod32!  !prod33! ]
    echo ===============================================================================
    echo 3. [3] Regresar al Menú Principal
    echo ===============================================================================
    set /p return="Elige el número de la opción que quieras: "
    if "%return%" == "3" goto start
    goto escalar
)
pause
goto start

:fin
exit
