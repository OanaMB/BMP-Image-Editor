# BMP Image Editor
## Overview
This program features a parser that interacts with BMP image files based on commands read from an input file. The core functionalities include editing, saving, quitting, and inserting images over an existing BMP file. This document provides an overview of the program's architecture, including its main functions and the workflow.

## Features
* **Edit**: Load and initialize a BMP image into a structure for manipulation.
* **Save**: Write the modified image data to a new BMP file.
* **Quit**: Release all dynamically allocated memory associated with the image.
* **Insert**: Overlay another image at specified coordinates on the currently loaded image.

## Implementation Details

### Edit Function
* Opens the BMP image file using '**fopen**'.
* Initializes a '**Bitmap**' structure, '**imageinfo**', containing the file header, information header, and pixel matrix.
* Reads the file and information headers.
* Utilizes '**fseek**' to skip header bytes and dynamically allocates memory for reading the pixel matrix, taking into account the padding which is skipped after each row.
* The result is stored in the '**Bitmap**' variable '**image**' for subsequent operations.
### Save Function
* Opens the output file in write mode.
* Employs '**fwrite**' to write the '**image**' data, including pixel data and padding, to the new file.
### Quit Function
* Frees the memory allocated for the pixel matrix.
* Insert Function
* Extracts the x and y coordinates from the input vector.
* Iterates over the matrices, inserting the overlay image's pixels into the base image starting at the specified coordinates. This process stops either after the entire overlay image is inserted or the edges of the base image are reached.
### Drawing Functions
* A new Pencil structure is introduced within the '**Bitmap**' structure to store the drawing color and thickness.
* For drawing lines and shapes ('**line**', '**rectangle**', '**triangle**'), the program first checks if the specified coordinates are within bounds. It then determines the orientation of the shape (horizontal, vertical, oblique) and utilizes the punct function to apply the pencil color around each relevant point according to the pencil's thickness.
### Fill Function
* Stores the current color in '**RedNow**', '**GreenNow**', '**BlueNow**' variables.
* Calls '**fillonepixel**', which checks if the pixel's color matches the target color. If so, it changes the pixel's color to the new specified values.
'**fillonepixel**' is called recursively for adjacent pixels, stopping when it reaches the matrix bounds or there are no matching adjacent pixels left.

## Usage
To use the BMP Image Editor, ensure the input file with commands ('**edit**', '**save**', '**insert**', '**quit**', etc.) is correctly formatted. Each line should contain a command followed by any necessary parameters, such as file names or coordinates. The program reads these commands until EOF (End Of File) and performs the specified operations on BMP images.

Commands must be structured as follows in the input file:

For **editing** and **saving**, specify the file name.
For **inserting**, provide the starting coordinates and the overlay image file name.
**Drawing** commands should include coordinates and, if applicable, the size and color.
Ensure all BMP files are accessible to the program and the output directory is writable.

## Conclusion
This BMP Image Editor offers a range of functionalities for manipulating BMP files through a simple command interface. By following the guidelines above, users can edit, save, insert, and draw on BMP images effectively.
