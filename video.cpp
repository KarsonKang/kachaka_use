#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <iostream>
#include <chrono>

int main() {
    // 打开相机
    cv::VideoCapture cap(0);  // 0表示默认相机，可以根据需要更改

    // 检查相机是否成功打开
    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open camera." << std::endl;
        return -1;
    }

    // 获取相机的宽度和高度
    // int width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int width = 640;
    // int height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    int height = 480;
    // 设置视频编码器和输出文件名
    int fourcc = cv::VideoWriter::fourcc('H', '2', '6', '4');  // 使用X264编码器

    cap.set(cv::CAP_PROP_FRAME_WIDTH, width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, height);
    cap.set(cv::CAP_PROP_FOURCC, fourcc);

    cv::VideoWriter writer("output_video1.mp4", fourcc, 30.0, cv::Size(width, height));

    // 检查视频编码器是否成功打开
    if (!writer.isOpened()) {
        std::cerr << "Error: Unable to open video writer." << std::endl;
        return -1;
    }

    // 循环读取相机图像并录制视频，按 'q' 键退出
    int FPS = 0;
    cv::Mat frame;
    cv::Mat originalFrame;
    double start_time;
    double end_time;

    while (true) {
        
        start_time = cv::getTickCount();
        cap >> frame;  // 从相机读取图像
        
        // 检查图像是否成功读取
        if (frame.empty()) {
            std::cerr << "Error: Unable to read frame from camera." << std::endl;
            break;
        }

        // 将图像写入视频文件
        writer.write(frame);
        end_time = cv::getTickCount();

        std::cout << (end_time - start_time) / cv::getTickFrequency() << std::endl;

        FPS = 1 / ((end_time - start_time) / cv::getTickFrequency());
        // 在图像上绘制一些信息（可选）
        cv::putText(frame, "FPS: " + std::to_string(FPS), cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 255, 0), 2);

        std::cout << FPS << std::endl;
        // // 显示图像（可选）
        cv::imshow("Camera Feed", frame);

        // // 检查用户是否按下 'q' 键
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // 释放资源
    cap.release();
    writer.release();
    cv::destroyAllWindows();

    return 0;
}