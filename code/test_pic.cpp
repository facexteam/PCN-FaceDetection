#include "PCN.h"
#include<iostream>
using namespace std;

typedef struct Img_Rect{
    cv::Mat img;
    std::vector<cv::Rect> rects;

}Img_Rect;

std::string parse_name(std::string& filename){
    int size=filename.size();
    std::string target="/";
    size_t pos=filename.rfind(target);
    std::string sub_str=filename.substr(pos+1,size-1);
    std::cout<<"filename="<<sub_str<<"\n";
    return sub_str;
}

int main(int argc, const char  *argv[])
{
    PCN detector("model/PCN.caffemodel","model/PCN-1.prototxt", "model/PCN-2.prototxt", "model/PCN-3.prototxt");
    detector.SetMinFaceSize(24);
    detector.SetScoreThresh(0.37, 0.43, 0.95);
    detector.SetImagePyramidScaleFactor(1.414);
    detector.SetVideoSmooth(false);
    Img_Rect img_rect;
    std::string filename("");
    std::cout<<"argc="<<argc<<"\n";
    if (argc>1) {
      for (int i=1;  i<argc; i+=2){
      string t_str(argv[i]);
      std::cout<<t_str<<"\n";
      if (t_str=="--image"){
        cv::Mat img=cv::imread(argv[i+1]);
        img_rect.img=img;
        string temp=argv[i+1];
        filename=parse_name(temp);
      }
      if (t_str=="--rect"){
        cv::Rect rect;
        rect.x=atoi(argv[i+1]);
        rect.y=atoi(argv[i+2]);
        rect.width=atoi(argv[i+3]);
        rect.height=atoi(argv[i+4]);
        img_rect.rects.push_back(rect);
//	std::cout<<"x="<< rect.x<<",y="<< rect.y<<",width="<< rect.width<<",height="<< rect.height<<"\n";
      }
    }
  }
    cv::Mat& img =img_rect.img;
    std::vector<cv::Rect>& rects=img_rect.rects;
	std::cout<<"img.rows="<<img.rows<<"\n";
    cv::TickMeter tm;
    tm.reset();
    tm.start();
    std::vector<Window> faces = detector.DetectFace(img,rects);
    std::cout << "Time Cost: "<<tm.getTimeMilli() << " ms" << std::endl;
    cv::Mat face_region=img(rects[0]);
    cv::Mat faceImg;
    for (int j = 0; j < faces.size(); j++){
	Window face(faces[j].x+rects[0].x,faces[j].y+rects[0].y,faces[j].width,faces[j].angle,faces[j].score);
        cv::Mat tmpFaceImg = CropFace(img, face, 200);
        // faceImg = MergeImgs(faceImg, tmpFaceImg);
        std::string file_name="result_test/"+filename+"_faces.jpg";
        cv::imwrite(file_name,tmpFaceImg);
    }
    std::string file_name="result_test/"+filename;
	std::cout<<file_name<<"\n\n**********************************\n\n";
    cv::imwrite(file_name,img);


    /*
    for (int i = 1; i <100; i++)
    {
        cv::Mat img =
            cv::imread("../faces/" + std::to_string(i) + ".jpg");
	if(!img.data){
		continue;
	}
	std::cout<<"img.rows="<<img.rows<<"\n";
        cv::TickMeter tm;
        tm.reset();
        tm.start();
        std::vector<Window> faces = detector.DetectFace(img);
	for(const auto& face:faces){
            std::cout<<"angle="<<face.angle<<"\n";
        }
        tm.stop();
        std::cout << "Image: " << i << std::endl;
        std::cout << "Time Cost: "<<
                  tm.getTimeMilli() << " ms" << std::endl;
        cv::Mat faceImg;
        for (int j = 0; j < faces.size(); j++)
        {
            cv::Mat tmpFaceImg = CropFace(img, faces[j], 200);
            faceImg = MergeImgs(faceImg, tmpFaceImg);
	    std::string file_name="result/"+std::to_string(i)+"_"+std::to_string(j)+"_faces.jpg";
	    cv::imwrite(file_name,tmpFaceImg);
        }
 //       cv::imshow("Faces", faceImg);
        for (int j = 0; j < faces.size(); j++)
        {
            DrawFace(img, faces[j]);
        }
	std::string file_name="result/"+std::to_string(i)+".jpg";
	std::cout<<file_name<<"\n\n**********************************\n\n";
    cv::imwrite(file_name,img);
 //       cv::imshow("PCN", img);
 //       cv::waitKey();
    }
*/
   // cv::destroyAllWindows();

    return 0;
}

