# Shutdown Guard
## About:
### An application that prevent Windows from shutting down.
---
## Usage:
#### -U : Unlimited&nbsp;&nbsp;(Constantly attempting to abort the shutdown).
```bat
Shutdown-Guard.exe -U
```
---
#### -L : Limited&nbsp;&nbsp;(Closes after the first successful attempt to abort the shutdown).
```bat
Shutdown-Guard.exe -L
```
---
#### -E : Efficiency&nbsp;&nbsp;(Constantly attempting to abort the shutdown every 0.001 of a second.).
```bat
Shutdown-Guard.exe -E
```
---
### Note: This application is created in both C and C++.
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/EEDDRV/Shutdown-Guard)
![GitHub](https://img.shields.io/github/license/EEDDRV/Shutdown-Guard)
---
## How to compile in C:

```bat
windres Shutdown-Guard.rc -o Shutdown-Guard.o
gcc -o Shutdown-Guard.exe Shutdown-Guard.c Shutdown-Guard.o 
```
## How to compile in C++:
```bat
windres Shutdown-Guard.rc -o Shutdown-Guard.o
g++ -o Shutdown-Guard.exe Shutdown-Guard.cpp Shutdown-Guard.o
```
