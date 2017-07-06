#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace std;
using namespace cv;
int main(int argc, char* args[])
{
    cout<<"begin"<<endl;
    string img_file = args[1];
    string outfile = args[2];
    ofstream os(outfile.c_str());
    dlib::frontal_face_detector detector = dlib::get_frontal_face_detector();
    dlib::shape_predictor sp;
    dlib::deserialize("shape_predictor_68_face_landmarks.dat") >> sp;
    // 直接用dlib的load，编译时要开启支持jpeg的选项，否则不支持load .jpg .jpeg图片
    // 所以可以用opencv的imread读取图片，然后将Mat转到dlib的格式dlib::array2d<dlib::rgb_pixel>
//    dlib::array2d<dlib::rgb_pixel> img;
//    dlib::load_image(img, img_file);
    Mat ori = cv::imread(img_file);
    dlib::cv_image<dlib::bgr_pixel> img(ori);
    std::vector<dlib::rectangle> dets = detector(img);//¼ì²âÈËÁ³
    if(dets.size() != 0){
        cout<<"detect face"<<endl;
        // get the biggest face of pic
        unsigned long maxIndex = 0;
        int maxArea = 0;
        for(unsigned long i = 0; i < dets.size(); i++){
            int area = dets[i].width()*dets[i].height();
            if(area > maxArea){
                maxIndex = i;
                maxArea = area;
            }
        }
        dlib::full_object_detection shape = sp(img, dets[maxIndex]);
        for (unsigned long i = 0; i < shape.num_parts(); i++){
            os<<shape.part(i)(0)<<" "<<shape.part(i)(1)<<endl;
            std::cout<<shape.part(i)(0)<<" "<<shape.part(i)(1)<<endl;
        }

    }else{
        cout<<"no face"<<endl;
    }
    os.close();
    cout<<"end"<<endl;
    return 0;
}
