#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream> 

using namespace cv; 
using namespace std; 

#define WIDTH 640
#define HEIGHT 480

void findFace(Mat image, char* path){
  CascadeClassifier faceCascade;
  vector<Rect> faces;
  Point center;
  int radius;
  
  faceCascade.load(path);

  faceCascade.detectMultiScale(image, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30));
  for (int i = 0; i < faces.size(); i++)
    {
      Rect r = faces[i];
      center.x = cvRound(r.x + r.width * 0.5);
      center.y = cvRound(r.y + r.height * 0.5);
      radius = cvRound((r.width + r.height) * 0.25);
      circle(image, center, radius, (0, 0, 255), 3, 8, 0);
    }
  return;
}
      

// Driver code 
int main(int argc, char** argv)
{
VideoCapture capture;
Mat image;
Mat gray;
capture.open(0);
if (capture.isOpened()){
capture.set(3, WIDTH);
capture.set(4, HEIGHT);
while(1){
capture >> image;
if (image.empty())
break;
cvtColor(image, gray, COLOR_BGR2GRAY);
if (argc < 2){
findFace(gray, "haarcascade_frontalface_default.xml");
}
else{
findFace(gray, argv[1]);
}
// Wait for any keystroke
imshow("Result", gray);
if (waitKey(30) > 0)
break;
}
}
else
cout << "Could Not Open Camera\n";
return 0;
}
