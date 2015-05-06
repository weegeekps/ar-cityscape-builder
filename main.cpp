//
// Created by Adam Morris on 4/29/15.
//

// STL Includes
#include <iostream>

// OpenCV Includes
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <opencv2/contrib/contrib.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>

// OSG Includes
#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>

// Application Includes
#include "ARTagNode.h"
#include "CalibrationParameters.h"
#include "MarkerDetector.h"
#include "VideoRenderer.h"
#include "SkyscraperAssetLoader.h"

const unsigned int CAPTURE_DEVICE_WIDTH = 640;
const unsigned int CAPTURE_DEVICE_HEIGHT = 480;
const unsigned int MARKER_DETECTOR_THRESHOLD = 90;

osg::Group *rootNode = new osg::Group;

std::vector<Marker> detectedMarkers;

int main(int argc, const char *argv[]) {
    double openedWidth, openedHeight;
    cv::Mat videoImage, videoImageRGB;

    cv::VideoCapture captureDevice = cv::VideoCapture(0);

    captureDevice.set(CV_CAP_PROP_FRAME_WIDTH, CAPTURE_DEVICE_WIDTH);
    captureDevice.set(CV_CAP_PROP_FRAME_HEIGHT, CAPTURE_DEVICE_HEIGHT);;

    if (!captureDevice.isOpened()) {
        std::cerr << "Failed to open capture device." << std::endl;
        return 1;
    }

    captureDevice >> videoImage;
    cv::cvtColor(videoImage, videoImageRGB, CV_RGBA2RGB);

    openedWidth = captureDevice.get(CV_CAP_PROP_FRAME_WIDTH);
    openedHeight = captureDevice.get(CV_CAP_PROP_FRAME_HEIGHT);

    std::cout << std::endl << "Opened capture device." << std::endl;
    std::cout << "\tCapture Device Width: " << openedWidth << std::endl;
    std::cout << "\tCapture Device Height: " << openedHeight << std::endl;
    std::cout << std::endl;

    // Set up our canvas.
    cv::Size size = cvSize((int) openedWidth, (int) openedHeight);
    osg::Group *videoCanvas = VideoRenderer::createSzene(videoImageRGB.ptr<uchar>(0), size.width, size.height);
    rootNode->addChild(videoCanvas);

    CalibrationParameters calibrationParameters = CalibrationParameters("Camera_Parameter_File.yml");

    // Set up the marker tracker.
    MarkerDetector *detector = new MarkerDetector(CAPTURE_DEVICE_WIDTH, CAPTURE_DEVICE_HEIGHT,
                                                  calibrationParameters.intrincsicMatrix,
                                                  calibrationParameters.distCoeffs);
    detector->setThreshold(MARKER_DETECTOR_THRESHOLD);

#ifdef DEBUG_MARKER_DETECTION
    while(true) {
        cv::Mat videoFrame;

        captureDevice >> videoFrame;

        detector->findMarkers(videoFrame, detectedMarkers, true);

        for (int i = 0; i < detectedMarkers.size(); ++i) {
            cout << "Detected Marker #" << detectedMarkers[i].id << endl;
        }

        cv::imshow("video", videoFrame);

        if (cv::waitKey(30) >= 0) {
            break;
        }
    }

    return 0;
#endif

    osg::MatrixTransform* nodeTransform = new osg::MatrixTransform();
    nodeTransform->setMatrix(osg::Matrix::identity());

    osg::Matrix moveDown;
    moveDown.makeTranslate(0.0, 13.0, 0.0);

    osg::Matrix rotate90;
    rotate90.makeRotate(
            1.57, osg::Vec3(1.0, 0.0, 0.0),
            0.0, osg::Vec3(0.0, 1.0, 0.0),
            0.0, osg::Vec3(0.0, 0.0, 1.0)
    );
    rotate90 = rotate90 * moveDown;

    osg::Matrix scaleTag200;
    scaleTag200.makeScale(
            0.4, 0.4, 0.4
    );
    scaleTag200 = scaleTag200 * rotate90;

    osg::Matrix scaleTag213;
    scaleTag213.makeScale(0.3, 0.35, 0.3);
    scaleTag213 = scaleTag213 * moveDown;

    osg::Matrix translateTag260;
    translateTag260.makeTranslate(-130.0, -25.0, 0.0);
    translateTag260 = translateTag260 * rotate90;

    osg::Matrix scaleTag314;
    scaleTag314.makeScale(0.03, 0.03, 0.03);
    scaleTag314 = scaleTag314 * rotate90;

    osg::Matrix translateTag314;
    translateTag314.makeTranslate(-70.0, 0.0, 0.0);
    scaleTag314 = scaleTag314 * translateTag314;

#ifdef DEBUG_BOXES
    osg::ref_ptr<ARTagNode> arTagNode132 = new ARTagNode(132, detectedMarkers, osg::Matrix::identity());
    osg::ref_ptr<ARTagNode> arTagNode200 = new ARTagNode(200, detectedMarkers, osg::Matrix::identity());
    osg::ref_ptr<ARTagNode> arTagNode213 = new ARTagNode(213, detectedMarkers, osg::Matrix::identity());
    osg::ref_ptr<ARTagNode> arTagNode260 = new ARTagNode(260, detectedMarkers, osg::Matrix::identity());
    osg::ref_ptr<ARTagNode> arTagNode314 = new ARTagNode(314, detectedMarkers, osg::Matrix::identity());
    osg::ref_ptr<ARTagNode> arTagNode480 = new ARTagNode(480, detectedMarkers, osg::Matrix::identity());

    SkyscraperAssetLoader assetLoader(rootNode);
    assetLoader.addAsset(arTagNode132, SkyscraperAssetLoader::createBox(80, osg::Vec4(1.0, 0.0, 0.0, 1.0), osg::Vec3(0.0,-39.0,0.0)));
    assetLoader.addAsset(arTagNode200, SkyscraperAssetLoader::createBox(80, osg::Vec4(1.0, 0.0, 0.0, 1.0), osg::Vec3(0.0,-39.0,0.0)));
    assetLoader.addAsset(arTagNode213, SkyscraperAssetLoader::createBox(80, osg::Vec4(1.0, 0.0, 0.0, 1.0), osg::Vec3(0.0,-39.0,0.0)));
    assetLoader.addAsset(arTagNode260, SkyscraperAssetLoader::createBox(80, osg::Vec4(1.0, 0.0, 0.0, 1.0), osg::Vec3(0.0,-39.0,0.0)));
    assetLoader.addAsset(arTagNode314, SkyscraperAssetLoader::createBox(80, osg::Vec4(1.0, 0.0, 0.0, 1.0), osg::Vec3(0.0,-39.0,0.0)));
    assetLoader.addAsset(arTagNode480, SkyscraperAssetLoader::createBox(80, osg::Vec4(1.0, 0.0, 0.0, 1.0), osg::Vec3(0.0,-39.0,0.0)));
#else
    osg::ref_ptr<ARTagNode> arTagNode132 = new ARTagNode(132, detectedMarkers, rotate90);
    osg::ref_ptr<ARTagNode> arTagNode200 = new ARTagNode(200, detectedMarkers, scaleTag200);
    osg::ref_ptr<ARTagNode> arTagNode213 = new ARTagNode(213, detectedMarkers, scaleTag213);
    osg::ref_ptr<ARTagNode> arTagNode260 = new ARTagNode(260, detectedMarkers, translateTag260);
    osg::ref_ptr<ARTagNode> arTagNode314 = new ARTagNode(314, detectedMarkers, scaleTag314);
    osg::ref_ptr<ARTagNode> arTagNode480 = new ARTagNode(480, detectedMarkers, rotate90);

    SkyscraperAssetLoader assetLoader(rootNode);
    assetLoader.addAsset(arTagNode132, "models/Building.3DS");
    assetLoader.addAsset(arTagNode200, "models/SkyA.3ds");
    assetLoader.addAsset(arTagNode213, "models/Al Faisaliah Center.obj");
    assetLoader.addAsset(arTagNode260, "models/apartman_2.obj");
    assetLoader.addAsset(arTagNode314, "models/building_2.3ds");
    assetLoader.addAsset(arTagNode480, "models/Godzilla.obj");
#endif

    // physical size of the sensor.
    double apertureWidth = 1.0;
    double apertureHeight = 1.0;
    double fovx, fovy, focalLength, aspectRatio;
    Point2d principalPoint;
    cv::calibrationMatrixValues(calibrationParameters.intrincsicMatrix, size, apertureWidth, apertureHeight, fovx, fovy, focalLength, principalPoint, aspectRatio);

    osg::Matrixd projectionmatrix;
    projectionmatrix.makePerspective(fovy, aspectRatio, 0.1, 1000.0);

    osgViewer::Viewer* viewer = new osgViewer::Viewer();
    viewer->setSceneData(rootNode);
    viewer->setUpViewOnSingleScreen(0);
    viewer->setCameraManipulator(new osgGA::TrackballManipulator());
    viewer->getCamera()->setClearColor(osg::Vec4(0.5, 0.5, 1.0, 1.0));
    viewer->getCamera()->setProjectionMatrix(projectionmatrix);

    while(!viewer->done()) {
        detectedMarkers.clear();

        captureDevice >> videoImage;
        cv::cvtColor(videoImage, videoImageRGB, CV_RGBA2RGB);

        detector->findMarkers(videoImage, detectedMarkers, true);

        viewer->frame();
    }

    captureDevice.release();

    return 0;
}
