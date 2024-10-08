
KPress
==========

[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat)](https://choosealicense.com/licenses/mit/)

KPress is an open-source, lossy image compression tool designed to give
the user control over the loss/compression tradeoff. Simple machine learning
tools such as this are often implemented as Python code calling C libraries,
but KPress is built in the underlying C for (1) the challenge and (2) to allow
optimization and portability for users who want to carefully input parameters
to fit their specific use cases. KPress uses a single-header library (made by
Sean T. Barrett) for image I/O, which increases portability, especially for
Windows machines, and decreases compile time via the preprocessor.

## Installation and Dependencies ##

KPress relies on `cstdio`, `cstring`, `cstdlib`, `ctime`, and `cmath`
standard C libraries to run. To-do: remove these dependencies by
replacing them with equivalent single-header libraries.

If you build from the Git repository you will also need to install make
and gcc to use the Makefile (e.g. `brew install make` on macOS,
`sudo apt install make` on Debian variants). Note that gcc and make
are most easily downloaded via Xcode on MacOS.

### Installation ###

The recommended way to obtain the source code is to clone the entire
[repository](https://github.com/Kasaar/KPress) from
[GitHub](https://github.com)

    git clone https://github.com/Kasaar/KPress.git

Building the main application is a simple as

    cd src
    make

If you are not using make or gcc, you will have to manually compile
the application. See Makefile for required files to be linked.

### Usage ###

After compiling, in the `src` directory, run the following command:

    ./kpress <image_path> <save_name> <clusters> <epochs>

`<image_path>`: The full path from the `src` directory to the image
file you want to compress.

`<save_name>`: The name you want the compressed image to have.
Do no include the full path or the file extension (i.e. .png).
The file will be saved to the src directory.

`<clusters>`: The number of centroids you want the algorithm to
consider. It is recommended to use powers of 2.

`<epochs>`: The number of times to iterate if the algorithm
does not converge.
