
# Nassi-Shneiderman-Diagrams

Nassi-Shneiderman diagrams (NSDs) are a graphical representation used in software development to describe the design or flow of a program.


##  Purpose

The purpose of this project is to provide a tool for generating NSDs based on pseudocode input. By visualizing the program flow in this way, developers can better understand the structure of their code and identify potential issues early in the development process.
## Description
The project was developed in the CodeBlocks text editor. The purpose of the project is to obtain a Nassi-Shneiderman diagram based on a text file that contains pseudocode. A Nassi-Shneiderman diagram is an easier way to represent a particular source code and is also available in CodeBlocks, see the following link:  https://wiki.codeblocks.org/index.php/NassiShneiderman_plugin.
## Installation

To use this application, follow these steps:
1. Clone this repository to your local machine.
```bash
  git clone https://github.com/ionutsavin/Nassi-Shneiderman-Diagrams.git
```
2. If your operating system is Windows(which is what i am using) you can follow this steps:
    - Download and install CodeBlocks on your computer from this website: https://www.codeblocks.org/downloads/.
        - Go to "Download the binary release"
        - Choose the "codeblocks-20.03mingw-setup.exe" option
    - Download 32bit Compiler from the following link: https://jmeubank.github.io/tdm-gcc/
        - Choose the "MinGW.org based" option
    - Download the WinBGIm graphics library for Windows from the following link: https://drive.google.com/file/d/16xZBvFXf7yFjxwTpuyevK1KPuLgUeZFh/view
        - Extract the downloaded zip file.
        - Copy graphics.h and winbgim.h to the include folder of the compiler you just downloaded
        - Copy libbgi.a to the lib folder of the compiler you just downloaded
        - Open CodeBlocks -> Settings -> Compiler -> Toolchain Executables and select the directory of your 32bit Compiler
        - Then go to Linker settings -> Other linker options and copy and paste this: 
            ```bash
            -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
            -lwinmm 
            -lgdiplus 
            -fmax-include-depth=268435456
            ```
        - Now you can run the project
3. If you are using Linux or MacOs follow these steps:
- Install the necessary tools
    ```bash
        sudo apt get update
        sudo apt install build-essential
    ```
- Go to this website https://libxbgi.sourceforge.net/ and download the "xbgi-365.tar.gz" version and type this commands
    ```bash
        tar zxvf xbgi-365.tar.gz # or later version
        cd xbgi-365/src
        make
        sudo make install
    ```
- To compile a program using libXbgi, make sure that it includes the 'graphics.h' header file and then:
    ```bash
        gcc -o program program.c /usr/lib/libXbgi.a -lX11 -lm
    ```
- Note that you might have to make some changes at the project providing the fact that the project was made using a library for Windows and graphics.h is an old library
## Documentation
The project uses BGI (Borland Graphics Interface) and here is a documentation of it: [BGI](https://home.cs.colorado.edu/~main/bgi/doc/)




## Demo

If you want to see how this project works you can go and watch the video at project -> docs -> short presentation

