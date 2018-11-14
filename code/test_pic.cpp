#include "PCN.h"

int main()
{
    PCN detector("model/PCN.caffemodel",
                 "model/PCN-1.prototxt", "model/PCN-2.prototxt", "model/PCN-3.prototxt");
    detector.SetMinFaceSize(24)
    detector.SetScoreThresh(0.37, 0.43, 0.95);
    detector.SetImagePyramidScaleFactor(1.414);
    detector.SetVideoSmooth(false);

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

   // cv::destroyAllWindows();

    return 0;
}

