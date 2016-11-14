#include <nan.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include "math.h"
using namespace cv;
using namespace std;

FlatWorker::Execute () {
    int thresh1 = 240;
    int thresh2 = 240;
    int contourSizeMinFirst = 20000;
    int contourSizeMinSecond = 2000;
    int contourSizeMaxFirst = 130000;
    int contourSizeMaxSecond = 130000;
    int matchAnyWayLimit = 40;
    float matchAnyWayLimitReal = 40.0;
    int minRooms = 2;
    int minDistance = 100;
    float minDistanceReal = 100.0;
    int rectMargin = 20;

    vector<vector<Point> > contours;
    vector<vector<Point> > contours2;

    matchAnyWayLimitReal = (float)matchAnyWayLimit/1000;
    Mat src;
    Mat src2;
    src = imread(this.croppedPath, CV_LOAD_IMAGE_COLOR);
    src2 = imread(this.sourcePath, CV_LOAD_IMAGE_COLOR);
    Mat gray;
    Mat gray2;
    cvtColor(src, gray, CV_BGR2GRAY);
    cvtColor(src2, gray2, CV_BGR2GRAY);
    threshold(gray, gray, thresh1, 255,THRESH_BINARY);
    threshold(gray2, gray2, thresh2, 255, THRESH_BINARY);
    vector<Vec4i> hierarchy;
    vector<Vec4i> hierarchy2;
    findContours( gray, contours, hierarchy, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );
    findContours( gray2, contours2, hierarchy2, CV_RETR_LIST, CV_CHAIN_APPROX_NONE );
    vector<vector<Point> >::iterator it = contours.begin();
    vector<vector<Point> >::iterator it2 = contours2.begin();
    for( ; it != contours.end(); )
    {
        if(contourArea(*it) < contourSizeMinFirst || contourArea(*it) > contourSizeMaxFirst) {
            it = contours.erase(it);
        } else {
            it++;
        }
    }
    for( ; it2 != contours2.end(); )
    {
        if(contourArea(*it2) < contourSizeMinSecond || contourArea(*it2) > contourSizeMaxSecond) {
            it2 = contours2.erase(it2);
        }
        else
        {
            it2++;
        }
    }
    RNG rng(12345);
    Mat drawing = Mat::zeros( gray.size(), CV_8UC3 );
    Mat drawing2 = Mat::zeros( gray2.size(), CV_8UC3 );
    map<int, int> matchContours;
    map<int, double> matchWeights;
    for(int i = 0; i < contours.size(); i++)
    {
        for(int j=0; j < contours2.size(); j++)
        {
            double match = cv::matchShapes(contours[i], contours2[j], CV_CONTOURS_MATCH_I1, 0);
            if(matchWeights.count(i) == 0 || match <= matchWeights.at(i))
            {
                matchContours[i] = j;
                matchWeights[i] = match;
            }
        }
    }
    for(int i = 0; i < contours.size(); i++)
    {
        for(int j=0; j < contours2.size(); j++)
        {
            double match = cv::matchShapes(contours[i], contours2[j], CV_CONTOURS_MATCH_I3, 0);
            if(match <= matchAnyWayLimitReal) {
                int idx = matchContours.rbegin()->first + 1;
                matchContours[idx] = j;
            }
        }
    }
    map<int, vector<int> > contourGroups;
    vector<int> contoursGroupped;
    for(map<int, int>::iterator it = matchContours.begin(); it != matchContours.end(); ++it)
    {
        if(find(contoursGroupped.begin(), contoursGroupped.end(), it->second) == contoursGroupped.end())
        {
            contourGroups[it->second].push_back(it->second);
            contoursGroupped.push_back(it->second);
        }
        for(map<int, int>::iterator it2 = matchContours.begin(); it2 != matchContours.end(); ++it2)
        {
            int currentMinDistance = -1;
            for(vector<Point>::iterator it3 = contours2[it2->second].begin(); it3 != contours2[it2->second].end(); ++it3)
            {
                for(vector<Point>::iterator it4 = contours2[it->second].begin(); it4 != contours2[it->second].end(); ++it4)
                {
                    int X_Diff = it4->x - it3->x;
                    int Y_Diff = it4->y - it3->y;
                    int distance = sqrt((X_Diff * X_Diff) + (Y_Diff * Y_Diff));
                    if(currentMinDistance == -1 || distance < currentMinDistance) currentMinDistance = distance;
                }
            }
            if(currentMinDistance <= minDistance)
            {
                if(find(contoursGroupped.begin(), contoursGroupped.end(), it2->second) == contoursGroupped.end())
                {
                    contourGroups[it->second].push_back(it2->second);
                    contoursGroupped.push_back(it2->second);
                }
            }
        }
    }
    for(map<int, vector<int> >::iterator it = contourGroups.begin(); it != contourGroups.end(); ++it)
    {

        vector<Point> merged_contour_points;
        for(vector<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            for(vector<Point>::iterator it3 = contours2[*it2].begin(); it3 != contours2[*it2].end(); ++it3)
            {
                merged_contour_points.push_back(*it3);
            }
        }
        if(it->second.size() >= minRooms)
        {
            vector<Point> hull;
            convexHull(Mat(merged_contour_points), hull);
            Mat hull_points(hull);
            RotatedRect minRect = minAreaRect(hull_points);
            Point2f rect_points[4];
            minRect.points(rect_points);
            rect_points[0].x -= rectMargin;
            rect_points[0].y += rectMargin;
            rect_points[1].x -= rectMargin;
            rect_points[1].y -= rectMargin;
            rect_points[2].x += rectMargin;
            rect_points[2].y -= rectMargin;
            rect_points[3].x += rectMargin;
            rect_points[3].y += rectMargin;
            for( int j = 0; j < 4; j++ )
            {
                Scalar color = Scalar(0,246,255);
                line(src2, rect_points[j], rect_points[(j+1)%4], color, 6, 8 );
            }
        }
    }

    imwrite(this.resultPath, src2);
}
