#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

void turnImage()
{
    for (const auto& emp : std::filesystem::directory_iterator("inputImage"))
    {

        std::string filePatch = emp.path().string();


        cv::Mat image = cv::imread(filePatch);


        if (image.empty()) {
            std::cerr << "Error: Unable to load image" << std::endl;
            return;
        }
        if (image.cols > image.rows)
        {
            cv::Mat rotatedImage;
            cv::transpose(image, rotatedImage);
            cv::flip(rotatedImage, rotatedImage, 0);

            cv::imwrite(filePatch, rotatedImage);

            std::cout << filePatch << " rotated and saved successfully" << std::endl;
        }

    }
}

void showImage()
{
    for (const auto& element : std::filesystem::directory_iterator("inputImage"))
    {
        std::string fileName = element.path().string();

        cv::Mat image = cv::imread(fileName);

        cv::String window = "window";

        cv::namedWindow(window);

        cv::imshow(window, image);

        cv::waitKey(100);
    }

    cv::destroyWindow;
}

void resizeImage()
{
    cv::Mat image = cv::imread("230406142003.jpg");
    cv::Mat resizeImage;

    cv::resize(image, resizeImage, cv::Size(1000, 1000));

    cv::String window = "window";
    cv::String window2 = "window2";

    cv::namedWindow(window);
    cv::namedWindow(window2);

    cv::imshow(window, resizeImage);
    cv::imshow(window2, image);

    cv::waitKey(0);

    cv::destroyAllWindows;
}

int main()
{
    cv::Mat image = cv::imread("230406142003.jpg");

    std::cout << image.rows << std::endl;
    std::cout << image.cols << std::endl;

    cv::waitKey(0);

    cv::Mat cropedImage = image(cv::Range(500, image.rows), cv::Range(1355, 1800));

    //cv::imshow("origWindow", image);
    cv::imshow("cropedWindow", cropedImage);

    cv::waitKey(0);
    cv::destroyAllWindows;

	return 0;
}