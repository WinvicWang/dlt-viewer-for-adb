# Diagnostic Log and Trace Viewer

## Overview

The Diagnostic Log Tool For Android ADB Device.

## Documentation

+ DLT Release Notes: ReleaseNotes.txt
+ DLT Installation: INSTALL.md

### Command line usage;

+ Windows: `dlt-viewer-for-adb.exe [OPTIONS]`
+ Linux: `dlt-viewer-for-adb [OPTIONS]`
+ MacOS: `open -a $DLT_BUILD_DIR/bin/DLT\ Viewer.app --args [OPTIONS]`

Options: 
+ `-h` Print usage
+ `-p projectfile` Loading project file on startup (must end with .dlp)
+ `-l logfile`     Loading logfile on startup (must end with .dlta)
+ `-f filterfile`  Loading filterfile on startup (must end with .dlf)
+ `-s or --silent`  Enable silent mode without warning message boxes
+ `-v or --version` Only show version and buildtime information
+ `-c logfile textfile`  Convert logfile file to textfile (logfile must end with .dlta)
+ `-u` Conversion will be done in UTF8 instead of ASCII";
+ `-csv` Conversion will be done in CSV format";
+ `-d` Conversion will NOT be done, save in dlt file format again instead"
+ `-dd` Conversion will NOT be done, save as decoded messages in dlt format"
+ `-e "name of plugin|command in plugin|param1|..|param<n>"` Execute a plugin command with <n> parameters

## API Documentation

See INSTALL.txt regarding doxygen API documentation generation.

## Software/Hardware

Developed with QT 5 (http://qt-project.org/)
Tested with Windows 10 + Qt 5.12.12 + Microsoft Visual Studio Build Tools 2017
Tested with Ubuntu Linux 18.04 + Qt 5.9.5
Tested with macOS Sierra + Qt 5.7.0
Dynamically linked open source software

Qt 5.x.x (LGPLv3 - Qt)
GCC (GPL)
(Optional) Mingw (GPL + BSD Variante + Public Domain)
Open Icon Library (http://openiconlibrary.sourceforge.net,Multiple Licenses)
License

Full information on the license for this software is available in the "LICENSE.txt" file.

## Source Code for DLT Viewer For Adb (This repository)
https://github.com/WinvicWang/dlt-viewer-for-adb-for-adb
This repo is developed based on the repo https://github.com/COVESA/dlt-viewer-for-adb, the license should follow Mozilla Public License, v. 2.0




