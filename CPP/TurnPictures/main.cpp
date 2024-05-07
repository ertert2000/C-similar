#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

int main()
{
    for (const auto& emp : std::filesystem::directory_iterator("inputImage"))
    {

        std::string filePatch = emp.path().string();


        cv::Mat image = cv::imread(filePatch);
	

        if (image.empty()) {
            std::cerr << "Error: Unable to load image" << std::endl;
            return -1;
        }
        if (image.cols > image.rows)
        {
            cv::Mat rotatedImage;
            cv::transpose(image, rotatedImage);
            cv::flip(rotatedImage, rotatedImage, 0);

            cv::imwrite(filePatch, rotatedImage);

            std::cout << filePatch<< " rotated and saved successfully" << std::endl;
        }

    }

    
	return 0;
}