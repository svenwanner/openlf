#include "cameraarray.h"

#include <stdio.h>
#include <stdarg.h>

/*Function///////////////////////////////////////////////////////////////

Name:       cvShowManyImages

Purpose:    This is a function illustrating how to display more than one 
               image in a single window using Intel OpenCV

Parameters: char *title: Title of the window to be displayed
            int nArgs:   Number of images to be displayed
            ...:         IplImage*, which contains the images

Language:   C++

The method used is to set the ROIs of a Single Big image and then resizing 
and copying the input images on to the Single Big Image.

This function does not stretch the image... 
It resizes the image without modifying the width/height ratio..

This function can be called like this:

cvShowManyImages("Images", 2, img1, img2);
or
cvShowManyImages("Images", 5, img2, img2, img3, img4, img5);

This function can display upto 12 images in a single window.
It does not check whether the arguments are of type IplImage* or not.
The maximum window size is 700 by 660 pixels.
Does not display anything if the number of arguments is less than
    one or greater than 12.

If you pass a pointer that is not IplImage*, Error will occur.
Take care of the number of arguments you pass, and the type of arguments, 
which should be of type IplImage* ONLY.

Idea was from BettySanchi of OpenCV Yahoo! Groups.

If you have trouble compiling and/or executing
this code, I would like to hear about it.

You could try posting on the OpenCV Yahoo! Groups
[url]http://groups.yahoo.com/group/OpenCV/messages/ [/url]


Parameswaran, 
Chennai, India.

cegparamesh[at]gmail[dot]com            

...
///////////////////////////////////////////////////////////////////////*/

void cvShowManyImages(char* title, int nArgs, ...) {

    // img - Used for getting the arguments 
    Mat img;

    // DispImage - the image in which input images are to be copied
	//Mat DispImage;

    int size;
    int i;
    int m, n;
    int x, y;

    // w - Maximum number of images in a row 
    // h - Maximum number of images in a column 
    int w, h;

    // scale - How much we have to resize the image
    float scale;
    int max;

    // If the number of arguments is lesser than 0 or greater than 18
    // return without displaying 
    if(nArgs <= 0) {
        printf("Number of arguments too small....\n");
        return;
    }
    else if(nArgs > 18) {
        printf("Number of arguments too large....\n");
        return;
    }
    // Determine the size of the image, 
    // and the number of rows/cols 
    // from number of arguments 
    else if (nArgs == 1) {
        w = h = 1;
        size = 400;
    }
    else if (nArgs == 2) {
        w = 2; h = 1;
        size = 400;
    }
    else if (nArgs == 3 || nArgs == 4) {
        w = 2; h = 2;
        size = 400;
    }
    else if (nArgs == 5 || nArgs == 6) {
        w = 3; h = 2;
        size = 400;
    }
    else if (nArgs == 7 || nArgs == 8) {
        w = 4; h = 2;
        size = 400;
    }
	else if (nArgs == 16) {
        w = 4; h = 4;
        size = 400;
    }
    else {
        w = 4; h = 3;
        size = 400;
    }

    // Create a new 1 channel image
    Mat DispImage(cvSize(100 + size*w, 60 + size*h), CV_8UC1);

    // Used to get the arguments passed
    va_list args;
    va_start(args, nArgs);

    // Loop for nArgs number of arguments
    for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) {
		Mat* ptr;
        // Get the Pointer to the IplImage
        ptr = va_arg(args, Mat*);

		/*
        // Check whether it is NULL or not
        // If it is NULL, release the image, and return
        if(img == 0) {
            printf("Invalid arguments");
            cvReleaseImage(&DispImage);
            return;
        }*/

        // Find the width and height of the image
        x = ptr->cols;//width;
        y = ptr->rows;//->height;

        // Find whether height or width is greater in order to resize the image
        max = (x > y)? x: y;

        // Find the scaling factor to resize the image
        scale = (float) ( (float) max / size );

        // Used to Align the images
        if( i % w == 0 && m!= 20) {
            m = 20;
            n+= 20 + size;
        }

        // Set the image ROI to display the current image
		Mat DispImageROI;
		DispImageROI = DispImage(Range(n,n+(int)( y/scale )),Range(m,m+(int)( x/scale )));

		//cvSetImageROI(DispImage, cvRect(m, n, (int)( x/scale ), (int)( y/scale )));

        // Resize the input image and copy the it to the Single Big Image
        //cvResize(img, DispImage);

		resize(*ptr, DispImageROI, DispImageROI.size() );

        // Reset the ROI in order to display the next image
        //cvResetImageROI(DispImage);
    }

    // Create a new window, and show the Single Big Image
    imshow(title, DispImage);

    // End the number of arguments
    va_end(args);
}

static Mat view;

void cvGetManyViews(char* title, int inN, Mat* outMats, unsigned int inNX, unsigned int inNY, unsigned int inType, int row_break) {
	int i;
	int m, n;

	int size;

	// w - Maximum number of images in a row 
    // h - Maximum number of images in a column 
    int w, h;

	if(inN == 1) {
		w = 1; h = 1;
	} else {
		w = 4; h = 3;
	}

	size = inNX/h;

    // scale - How much we have to resize the image
    
	view.create(100 + size*h, 100 + size*w, inType);

	for (i = 0, m = 20, n = 20; i < inN; i++, m += (20 + size)) {

        // Used to Align the images
        if( i % w == 0 && m!= 20) {
            m = 20;
            n+= 20 + size;
        }

		outMats[i] = view(Range(n,n+size),Range(m,m+size));
	}
	imshow(title, view);
}

static int updating = 0;

void cvUpdateManyViews(char* inTitle) {
	if(updating == 0) { //<=--possible concurrent execution, do cleanly
		updating = 1;
		imshow(inTitle, view);

		HWND hWnd = (HWND)cvGetWindowHandle(inTitle);
		::SendMessage(hWnd, WM_PAINT, 0, 0);
		updating = 0;
	}
}