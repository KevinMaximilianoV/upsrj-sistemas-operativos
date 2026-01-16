#!/bin/bash

#chmod +x scheduler_discovery.sh

#El Kernel de Linux viene compilado ya en el OS, por lo
#tanto, debemos descargar la version del Kernel descompilado
#para ver los archivos de C

sudo apt install linux-source
echo El codigo fuente del Kernel de Linux ha sido descargado

#Una vez descargado el codigo fuente, debemos navegar a donde
#se descargo
cd /usr/src/

#Ahora, cono el archivo esta comprimido, hay que descomprimirlo
echo Archivo a descomprimir: linux-source-5.15.0.tar.bz2
sudo tar -xjf linux-source-5.15.tar.bz2
echo Archivo Descomprimido

#Una vez descomprimido, podemos acceder al folder
cd linux-source-5.15.0/

#En todo caso que haya otro archvio tar.bz2 que extraer dentro
#usamos el mismo comando

sudo tar -xjf linux-source-5.15.0.tar.bz2

#Ahora si, entramos a la carpeta

cd linux-source-5.15.0

#Lo que nos interesa es entrar al Kernel, asi que buscaremos una
#carpeta con el nombre Kernel y entramos

ls 
cd kernel/

#Dentro del Kernel, hay muchos archivos, pero lo que nos interesa
#Es la carpeta de sched

ls 
cd sched/

#Dentro de esta carpeta, podemos ver multiples archivos, pero los
#mas importantes son el core.c y fair.c

cat core.c
echo Este es el archivo donde se implementa las bases para el scheduler
#Esto nos muestra el nucleo del proceso de scheduling que usa linux
#que es el CFS, pero aqui como tal no esta implementado el CFS, si no
#que es la base del scheduler en general, este es el framework que 
#permitiria implementar otro tipo de scheduler correctamente a las
#funciones ya existentes de linux

#Ahora, el archivo que explicitamente implementa el CFS es el archivo
#fair.c

cat fair.c
echo Este es el archivo donde se implementa el CFS en linux

#En este archivo se implementa como tal el CFS, el como se reparte 
#los procesos dependiendo de su prioridad, es decir, entre mas critico
#sea un proceso en el sistema, mayor prioridad se le asigna

#Esto permite implementar otro tipo de schedulers de manera mas sencilla
#sin tener que adaptar el resto de archivos de linux al scheduler que
#quisieramos implementar, basicamente, el core.c actua como el 
#process.c de nuestro repositorio, y el fair.c como los archivos de 
#implementacion de schedulers (fcfs.c, rr.c. sjf.c)

#Pregunta Obligatoria
#¿Por qué Linux no implementa directamente FCFS, SJF o RR como se ven en los libros?

#Por que estos tipos de scheduling no son efectivos en un sistema operativo tan complejo
#como lo es Linux, al tener que estar ejecutando +5000 procesos constantemente, los
#otros algoritmos de scheduling presentan problemas criticos en una ejecuccion eficiente
#mientras que el CFS prioritiza procesos con mas peso primero en vez de tiempo de llegada
#o tiempo para realizar, linux prioritiza la estabilidad de su sistema operativo