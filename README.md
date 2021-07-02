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
## Note:
### This application is created in both C and C++. Instructions on how to compile the code are in the comments in the bottom of each of the files.
![GitHub code size in bytes](https://img.shields.io/github/languages/code-size/EEDDRV/Shutdown-Guard)
![GitHub](https://img.shields.io/github/license/EEDDRV/Shutdown-Guard)