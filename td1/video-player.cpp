#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdio>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define NB_READING_FRAMES 1000
#define NAME_WINDOW "caption"

VideoCapture vid_src;
int index_current_frame = 0;
int video_playing = 0;
int has_to_print_goto = 0;

int play_vid(){
  video_playing = 1;

  for(; index_current_frame < NB_READING_FRAMES && cvGetWindowHandle(NAME_WINDOW) != NULL; index_current_frame++){
    Mat current_frame;
    vid_src >> current_frame;
    imshow(NAME_WINDOW, current_frame);

    if(cvGetTrackbarPos("current_frame_vid", NAME_WINDOW) >= 0){
      setTrackbarPos("current_frame_vid", NAME_WINDOW, index_current_frame);
      has_to_print_goto = 0;
    }

    if((char)27 == (char)waitKey(1000 / vid_src.get(CV_CAP_PROP_FPS))){
      return 0;
    }
  }
  video_playing = 0;

  return 1;
}

void on_change_trackbar(int, void*)
{
  if(index_current_frame >= vid_src.get(CV_CAP_PROP_FRAME_COUNT)){
    return;
  }

  vid_src.set(CV_CAP_PROP_POS_FRAMES, index_current_frame);

  if(index_current_frame >= NB_READING_FRAMES){
    Mat current_frame;
    vid_src >> current_frame;
    imshow(NAME_WINDOW, current_frame);
  }
  if(has_to_print_goto)
    cout << "go to frame number = " << index_current_frame << std::endl;
  else
    has_to_print_goto = 1;
}

void
process(const char* vidname)
{
  vid_src.open(string(vidname));

  if(!vid_src.isOpened()){
    cout << "Error: cannot find file: " << vidname << std::endl;
    return;
  }

  namedWindow(NAME_WINDOW, WINDOW_AUTOSIZE);
  createTrackbar("current_frame_vid", NAME_WINDOW, &index_current_frame, vid_src.get(CV_CAP_PROP_FRAME_COUNT), on_change_trackbar);

  cout << vidname << " infos:" << std::endl;
  cout << "fps: " << vid_src.get(CV_CAP_PROP_FPS) << std::endl;
  cout << "width: " << vid_src.get(CV_CAP_PROP_FRAME_WIDTH) << std::endl;
  cout << "height: " << vid_src.get(CV_CAP_PROP_FRAME_HEIGHT) << std::endl;
  cout << "frame count: " << vid_src.get(CV_CAP_PROP_FRAME_COUNT) << std::endl;

  while(1){
    if (!video_playing && index_current_frame < NB_READING_FRAMES){
      if(!play_vid())//exit if user presses escape
        return;
    }

    if(cvGetWindowHandle(NAME_WINDOW) == NULL){//exit if window has been closed
      return;
    }

    if((char)27 == (char)waitKey(10)){//exit if user presses exit
      return;
    }
  }
}

void
usage (const char *s)
{
  fprintf(stderr, "Usage: %s imsname\n", s);
  exit(EXIT_FAILURE);
}

#define param 1
int
main( int argc, char* argv[] )
{
  if(argc != (param+1))
    usage(argv[0]);
  process(argv[1]);
  return EXIT_SUCCESS;
}
