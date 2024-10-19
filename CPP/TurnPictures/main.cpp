#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <filesystem>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <curl/curl.h>

//const char* smtp_server = "smtp://smtp.gmail.com:587";
//const char* from_email = "alekseipoliakoff@gmail.com";
//const char* to_email = "schahov.kirill2017@yandex.ru";
//const char* to_email = "ertert2000@yandex.ru";
//const char* to_mail2 = "artem.pavlenko.05@mail.ru";
//const char* subject = "а это не я";
//const char* email_body = "В кадре появился человек";
//const char* password = "kcnw bsbb eyvt aspu";

    
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

void cropImage()
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
}

void changePixels()
{
    cv::Mat image = cv::imread("230406142003.jpg");

    for (int i = 0; i < image.rows; i++)
        for (int j = 0; j < image.cols; j++)
        {
            cv::Vec3b temp = image.at<cv::Vec3b>(i, j);
            if (std::abs(temp[0] - 218) < 25 && std::abs(temp[1] - 186) < 50 && std::abs(temp[2] - 115) < 25)
            {
                image.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 255);
                std::cout << "pixel Change" << std::endl;
            }

        }

    cv::imshow("window", image);

    cv::waitKey(0);
    cv::destroyAllWindows();
}

void webCum()
{
    cv::VideoCapture cap(0);


    if (cap.isOpened() == false)
    {
        std::cout << "Cannot open the video camera" << std::endl;
        std::cin.get();
        return;
    }

    double dWidth = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

    std::cout << "Resolution of the video : " << dWidth << " x " << dHeight << std::endl;

    std::string window_name = "My Camera Feed";
    cv::namedWindow(window_name);

    while (true)
    {
        cv::Mat frame;
        bool bSuccess = cap.read(frame);

        if (bSuccess == false)
        {
            std::cout << "Video camera is disconnected" << std::endl;
            std::cin.get();
            break;
        }

        cv::imshow(window_name, frame);

        if (cv::waitKey(10) == 27)
        {
            std::cout << "Esc key is pressed by user. Stoppig the video" << std::endl;
            break;
        }
    }
}

void faceDetector()
{
    for (const auto& pictures : std::filesystem::directory_iterator("dataFace"))
    {
        std::cout << "load" << std::endl;
        std::string filePath = pictures.path().string();

        cv::Mat image = cv::imread(filePath);
        if (image.empty())
        {
            std::cerr << "Error: Couldn't read the image. Check the path and try again." << std::endl;
            return;
        }

        cv::CascadeClassifier face_cascade, eye_cascade, profilCascade;
        face_cascade.load("haarcascade_frontalface_default.xml");
        eye_cascade.load("haarcascade_eye.xml");
        profilCascade.load("haarcascade_profileface.xml");

        cv::Mat gray;
        cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.1, 4);

        std::vector<cv::Rect> profilFace;
        profilCascade.detectMultiScale(gray, profilFace, 1.1, 4);

        for (const auto& face : faces)
        {
            for (const auto& profil : profilFace)
            {
                cv::rectangle(image, profil, cv::Scalar(0, 0, 255), 2);

            }

            cv::rectangle(image, face, cv::Scalar(255, 0, 0), 2);

            cv::Mat faceROI = gray(face);
            std::vector<cv::Rect> eyes;
            eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 4);

            for (const auto& eye : eyes)
            {
                cv::Point eye_center(face.x + eye.x + eye.width / 2, face.y + eye.y + eye.height / 2);
                int radius = cvRound((eye.width + eye.height) * 0.25);
                cv::circle(image, eye_center, radius, cv::Scalar(0, 255, 0), 2);
            }
        }

        cv::imshow("Face and Eye Detection", image);
        cv::waitKey(0);
        system("cls");
    }

    cv::destroyAllWindows;
}

size_t payload_source(void* ptr, size_t size, size_t nmemb, void* userp) 
{
    const char** payload = (const char**)userp;

    if (*payload == nullptr)
        return 0;

    size_t len = strlen(*payload);
    size_t total_size = size * nmemb;

    if (len > total_size)
        len = total_size;

    memcpy(ptr, *payload, len);
    *payload += len;

    return len;
}

//void letterSender()
//{
//    CURL* curl;
//    CURLcode res = CURLE_OK;
//    struct curl_slist* recipients = nullptr;
//    const char* payload = email_body;
//
//    curl = curl_easy_init();
//    if (curl) {
//        curl_easy_setopt(curl, CURLOPT_URL, smtp_server);
//        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
//
//        curl_easy_setopt(curl, CURLOPT_USERNAME, from_email);
//        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
//
//        recipients = curl_slist_append(recipients, to_email);
//        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
//
//        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, to_email);
//        //curl_easy_setopt(curl, CURLOPT_MAIL_FROM, to_mail2);
//
//        std::string full_email = "To: " + std::string(to_email) + "\r\n" +
//            "From: " + std::string(from_email) + "\r\n" +
//            "Subject: " + subject + "\r\n\r\n" + email_body;
//        const char* payload_ptr = full_email.c_str();
//
//        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
//        curl_easy_setopt(curl, CURLOPT_READDATA, &payload_ptr);
//        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
//
//        res = curl_easy_perform(curl);
//
//        if (res != CURLE_OK)
//            std::cerr << "Error sending email:" << curl_easy_strerror(res) << std::endl;
//        else
//            std::cout << "The letter has been sent successfully!" << std::endl;
//
//
//        curl_slist_free_all(recipients);
//        curl_easy_cleanup(curl);
//    }
//}

size_t wdata(void* ptr, size_t size, size_t nmemb, FILE* stream)
{
    size_t writ = fwrite(ptr, size, nmemb, stream);
    return writ;
}

void dowloadEye()
{
    CURL* curl = curl_easy_init();
    FILE* file = fopen("haarcascade_eye.xml", "wb");

    curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/opencv/opencv/4.x/data/haarcascades/haarcascade_eye.xml");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wdata);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK)
    {
        std::cout << "Error download haarcascade_eye.xml" << std::endl;
        return;
    }
    else
        std::cout << "download successfull haarcascade_eye.xml" << std::endl;
    fclose(file);
}

void dowloadFrontFace()
{
    CURL* curl = curl_easy_init();
    FILE* file = fopen("haarcascade_frontalface_default.xml", "wb");

    curl_easy_setopt(curl, CURLOPT_URL, "https://raw.githubusercontent.com/opencv/opencv/4.x/data/haarcascades/haarcascade_frontalface_default.xml");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wdata);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK)
    {
        std::cout << "Error download haarcascade_frontalface_default.xml" << std::endl;
        return;
    }
    else
        std::cout << "download successfull haarcascade_frontalface_default.xml" << std::endl;
    fclose(file);
}

void cameraDetected()
{
    //int cadr = 0;
    bool flag = false;

    cv::CascadeClassifier face_cascade, eye_cascade, profilCascade;
    if (!face_cascade.load("haarcascade_frontalface_default.xml"))
    {
        std::cout << "Downloading haarcascade_frontalface_default.xml from https://raw.githubusercontent.com/opencv/opencv/4.x/data/haarcascades/haarcascade_frontalface_default.xml" << std::endl;
        dowloadFrontFace();
        face_cascade.load("haarcascade_frontalface_default.xml");
    }

    if (!eye_cascade.load("haarcascade_eye.xml"))
    {
        std::cout << "Downloading haarcascade_eye.xml from https://raw.githubusercontent.com/opencv/opencv/4.x/data/haarcascades/haarcascade_eye.xml" << std::endl;
        dowloadEye();
        eye_cascade.load("haarcascade_eye.xml");
    }

    /*if (!profilCascade.load("haarcascade_profileface.xml"))
    {
        std::cerr << "Error: Couldn't load the face cascade file." << std::endl;
        return;
    }*/


    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        std::cerr << "Error: Couldn't open the video file." << std::endl;
        return;
    }

    cv::Mat oldFrame, oldGray;
    cap >> oldFrame;
    cv::cvtColor(oldFrame, oldGray, cv::COLOR_BGR2GRAY);

    std::vector<cv::Rect> oldFaces;
    face_cascade.detectMultiScale(oldGray, oldFaces, 1.2, 5);

    cv::Scalar color(0, 255, 0);

    while (true)
    {
        cv::Mat frame, gray;
        cap >> frame;

        //std::cout << cadr << std::endl;

        if (frame.empty())
            break;

        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        std::vector<cv::Rect> newFaces;
        face_cascade.detectMultiScale(gray, newFaces, 1.2, 5);

        if (!oldFaces.empty() && !newFaces.empty())
        {
            if (flag == false)
            {
                //letterSender();
                flag = true;
            }

            std::vector<cv::Point2f> oldPoints, newPoints;
            for (const auto& face : oldFaces)
            {
                oldPoints.push_back(cv::Point2f(face.x + face.width / 2, face.y + face.height / 2));

                cv::Mat faceROI = gray(face);
                std::vector<cv::Rect> eyes;
                eye_cascade.detectMultiScale(faceROI, eyes, 1.1, 4);

                for (const auto& eye : eyes)
                {
                    cv::Point eye_center(face.x + eye.x + eye.width / 2, face.y + eye.y + eye.height / 2);
                    int radius = cvRound((eye.width + eye.height) * 0.25);
                    cv::circle(frame, eye_center, radius, cv::Scalar(0, 255, 0), 2);
                }
            }

            std::vector<uchar> status;
            std::vector<float> err;
            cv::calcOpticalFlowPyrLK(oldGray, gray, oldPoints, newPoints, status, err);


            oldFaces = newFaces;
            for (size_t i = 0; i < newFaces.size(); i++)
                cv::rectangle(frame, newFaces[i], cv::Scalar(255, 0, 0), 2);

        }
        else if (!newFaces.empty())
        {
            oldFaces = newFaces;
            for (const auto& face : newFaces)
                cv::rectangle(frame, face, cv::Scalar(255, 0, 0), 2);
            flag = false;
        }

        cv::imshow("Face Tracking", frame);

        if (cv::waitKey(30) == 27) {
            break;
        }

        oldGray = gray.clone();
        oldFaces = newFaces;
        //cadr++;
    }

    cap.release();
    cv::destroyAllWindows();
}


int main()
{
    cameraDetected();


    getchar();
    return 0;
}

