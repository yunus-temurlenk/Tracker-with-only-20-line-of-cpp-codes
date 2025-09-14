#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <iostream>

int main() {

    cv::VideoCapture cap(0);
    cv::Mat frame;
    cap >> frame;
    cv::Rect roi = cv::selectROI("Select", frame);
    cv::Ptr<cv::Tracker> tracker = cv::TrackerCSRT::create();
    tracker->init(frame, roi);
    while (true)
    {
        cap >> frame;
        bool ok = tracker->update(frame, roi);
        if(ok)
        {
            cv::rectangle(frame, roi, cv::Scalar(0,255,255), 2);
            cv::putText(frame, "Tracking", roi.tl(), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(255,0,0),2);
        }
        else
        {
            cv::putText(frame, "Tracking", cv::Point(50,50), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(255,0,0),2);
        }
        cv::imshow("Result", frame);
        cv::waitKey(30);
    }
    return 0;
}
