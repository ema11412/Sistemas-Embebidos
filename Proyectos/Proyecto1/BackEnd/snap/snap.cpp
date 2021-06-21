#include <snap.h>

#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

enum
{
  FALSE = 0,
  TRUE = 1
};

int
snap( void )
{
  // open the first webcam plugged in the computer
  cv::VideoCapture camera(0);
  if (!camera.isOpened()) {
      std::cerr << "ERROR: Could not open camera" << std::endl;
      return FALSE;
  }
  // this will contain the image from the webcam
  cv::Mat frame;

  // capture the next frame from the webcam
  for( int i = 0; i < 25; ++i )
  {
    camera >> frame;
  }

  if (frame.empty())
  {
    std::cerr << "something went wrong!" << std::endl;
    return FALSE;
  }

  imwrite(snap_frame_path, frame);

  return TRUE;
}
