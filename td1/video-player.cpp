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

void play_vid(){
  video_playing = 1;

  for(; index_current_frame < NB_READING_FRAMES; index_current_frame++){
    Mat current_frame;
    vid_src >> current_frame;
    setTrackbarPos("current_frame_vid", NAME_WINDOW, index_current_frame);
    imshow(NAME_WINDOW, current_frame);
    waitKey(1000 / vid_src.get(CV_CAP_PROP_FPS));
  }
  video_playing = 0;
}

void on_change_trackbar(int, void*)
{
  vid_src.set(CV_CAP_PROP_POS_FRAMES, index_current_frame);
  if(index_current_frame >= NB_READING_FRAMES){
    Mat current_frame;
    vid_src >> current_frame;
    imshow(NAME_WINDOW, current_frame);
  }
  cout << "go to frame number = " << index_current_frame << std::endl;
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
      play_vid();
    }
    waitKey(10);
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
