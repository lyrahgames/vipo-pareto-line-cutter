<h1 align="center">
    VIPO: Pareto Line Cutter for <br>Two-Objective Pareto Frontiers
</h1>

<p align="center">
    Executable to Estimate Continuously Connected Areas of Two-Objective Pareto Frontiers
</p>

<table align="center" border="0">
    <tr>
        <td align="center">
            <figure>
                <img src="docs/images/pareto2-kursawe-wrong-cropped.png" width="350">
                <figcaption>Without Line Cut</figcaption>
            </figure>
        </td>
        <td align="center">
            <figure>
                <img src="docs/images/pareto2-kursawe-frontier-cropped.png" width="350">
                <figcaption>With Line Cut</figcaption>
            </figure>
        </td>
    </tr>
</table>

## Development Status

<p align="center">
    <img src="https://img.shields.io/github/languages/top/lyrahgames/vipo-pareto-line-cutter.svg?style=for-the-badge">
    <img src="https://img.shields.io/github/languages/code-size/lyrahgames/vipo-pareto-line-cutter.svg?style=for-the-badge">
    <img src="https://img.shields.io/github/repo-size/lyrahgames/vipo-pareto-line-cutter.svg?style=for-the-badge">
    <a href="COPYING.md">
        <img src="https://img.shields.io/github/license/lyrahgames/vipo-pareto-line-cutter.svg?style=for-the-badge&color=blue">
    </a>
</p>

<b>
<table align="center">
    <tr>
        <td>
            master
        </td>
        <td>
            <a href="https://github.com/lyrahgames/pxart">
                <img src="https://img.shields.io/github/last-commit/lyrahgames/vipo-pareto-line-cutter/master.svg?logo=github&logoColor=white">
            </a>
        </td>
    </tr>
    <tr>
        <td>
        </td>
    </tr>
    <tr>
        <td>
            Current
        </td>
        <td>
            <a href="https://github.com/lyrahgames/vipo-pareto-line-cutter">
                <img src="https://img.shields.io/github/commit-activity/y/lyrahgames/vipo-pareto-line-cutter.svg?logo=github&logoColor=white">
            </a>
        </td>
        <!-- <td>
            <img src="https://img.shields.io/github/release/lyrahgames/vipo-pareto-line-cutter.svg?logo=github&logoColor=white">
        </td>
        <td>
            <img src="https://img.shields.io/github/release-pre/lyrahgames/vipo-pareto-line-cutter.svg?label=pre-release&logo=github&logoColor=white">
        </td> -->
        <td>
            <img src="https://img.shields.io/github/tag/lyrahgames/vipo-pareto-line-cutter.svg?logo=github&logoColor=white">
        </td>
        <td>
            <img src="https://img.shields.io/github/tag-date/lyrahgames/vipo-pareto-line-cutter.svg?label=latest%20tag&logo=github&logoColor=white">
        </td>
    </tr>
</table>
</b>


## Requirements
<b>
<table align="center">
    <tr>
        <td>Language Standard:</td>
        <td>C++20</td>
    </tr>
    <tr>
        <td>Operating System:</td>
        <td>Linux</td>
    </tr>
    <tr>
        <td>Compiler:</td>
        <td>GCC 10 | GCC 11</td>
    </tr>
    <tr>
        <td>Build System:</td>
        <td>
            <a href="https://build2.org/">build2</a>
        </td>
    </tr>
    <tr>
        <td>Dependencies:</td>
        <td>
            <a href="https://github.com/lyrahgames/pareto">
                lyrahgames-pareto
            </a>
            <br>
            <a href="https://github.com/lyrahgames/gnuplot">
                lyrahgames-gnuplot
            </a>
        </td>
    </tr>
</table>
</b>

## Build
First, clone the repository and change into its directory.

    git clone https://github.com/lyrahgames/vipo-pareto-line-cutter.git
    cd vipo-pareto-line-cutter

### Linux
Add a new build2 configuration for GCC.

    bdep init -C ../.build-gcc @gcc cc config.cxx=g++ config.cxx.coptions="-O3 -march=native"

Build the executables for the created configuration.

    bdep update @gcc

The executables can then be found by looking inside the configuration folder.

### Cross-Compile on Linux for Windows
Make sure to install [Mingw-w64](https://www.mingw-w64.net) on your system and initialize a configuration with the appropriate parameters.

    bdep init -C ../.build-mingw @mingw cc \
        config.cxx=x86_64-w64-mingw32-g++ \
        config.cxx.poptions="-DNDEBUG -D_USE_MATH_DEFINES" \
        config.cxx.coptions="-O3" \
        config.cxx.loptions="-fPIC -static -static-libgcc -static-libstdc++"

Update the created configuration and put the executables that can be found inside the configuration folder on a Windows computer.

    bdep update @mingw

## Usage
The pareto-line-cutter can be called the following way.

    ./pareto-line-cutter <input file> <first column> <second column> <output file> [-plot]

The input file is expected to be written in ASCII-based CSV format with white space as separators and should contain the objective values of an estimated Pareto frontier of a chosen two-objective optimization problem.
Then the first and second column parameters describe in which columns those values can be located.

The output file will then again be written to in ASCII-based CSV format with white space as separators.
The first column stores the index of the Pareto solution with respect to the input file.
Following column describe for the sake of verbosity again the objective values.
Connected areas are separated by an additional newline character

For simplicity, the optional argument `-plot` can be provided to automatically plot the resulting connected areas with Gnuplot if it is available on the command line.

## Additional Information
- [Authors](AUTHORS.md)
- [License](COPYING.md)

## References
