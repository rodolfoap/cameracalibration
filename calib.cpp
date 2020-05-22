#include <opencv2/opencv.hpp>
#include <filesystem>

int main(int argc, char** argv) {
	if(argc<5) { std::cerr<<"Usage: "<<argv[0]<<"[IMAGES_PATH BOARD_SIZE NUMBER_OF_CORNERS_X NUMBER_OF_CORNERS_Y]"<<std::endl; return -1; }

	// Configuration goes here
	cv::Size board_pattern(std::stoi(argv[3]), std::stoi(argv[4]));
	float board_cellsize=std::stof(argv[2]);
	std::string path=argv[1];
	std::cerr<<"Path: "<<argv[1]<<std::endl<<"Cell size: "<<argv[2]<<std::endl<<"Dimensions: "<<argv[3]<<"x"<<argv[4]<<std::endl;

	// Read files
	cv::Mat image;
	std::vector<cv::Mat> images;
	for (const auto& entry: std::filesystem::directory_iterator(path)) {
		std::cerr<<"Reading file: "<<entry.path()<<std::endl;
		image=cv::imread(entry.path());
		images.push_back(image);
	}
	if (images.empty()) { std::cerr<<"No files found."<<std::endl; return -1; }

	// Find 2D corner points from the given images
	std::cerr<<"Finding 2D corner points: ";
	std::vector<std::vector<cv::Point2f>> img_points;
	for (size_t i = 0; i < images.size(); i++) {
		std::cerr<<'.';
		std::vector<cv::Point2f> pts;
		if (cv::findChessboardCorners(images[i], board_pattern, pts)) img_points.push_back(pts);
	} std::cerr<<" done."<<std::endl;
	if (img_points.empty()) { std::cerr<<"No points detected. Check the board pattern size."<<std::endl; return -1; }

	// Prepare 3D points of the chess board
	std::cerr<<"Building 3D points matrix: ";
	std::vector<std::vector<cv::Point3f>> obj_points(1);
	for (int r = 0; r < board_pattern.height; r++)
		for (int c = 0; c < board_pattern.width; c++) {
			std::cerr<<'.';
			obj_points[0].push_back(cv::Point3f(board_cellsize * c, board_cellsize * r, 0));
		} std::cerr<<" done."<<std::endl;
	obj_points.resize(img_points.size(), obj_points[0]); // Copy

	// Calibrate the camera
	cv::Mat K = cv::Mat::eye(3, 3, CV_64F);
	cv::Mat dist_coeff = cv::Mat::zeros(4, 1, CV_64F);
	std::vector<cv::Mat> rvecs, tvecs;
	double rms = cv::calibrateCamera(obj_points, img_points, images[0].size(), K, dist_coeff, rvecs, tvecs);

	// Generate results
	std::cerr<<"Results:"<<std::endl;
	std::cerr<<"Number of applied images: "<<img_points.size()<<std::endl;
	std::cerr<<"RMS error: "<<rms<<std::endl;
	std::cerr<<"Camera matrix (K): "<<std::endl<<K<<std::endl;
	std::cerr<<"Distortion coefficients (k1, k2, p1, p2, k3, ...): "<<std::endl<<dist_coeff.t()<<std::endl;

	// Generate yaml file
	cv::FileStorage fs("camera_matrix.yaml", cv::FileStorage::WRITE);
	fs << "camera_matrix" << K << "distortion_coefficients" << dist_coeff;
	fs.release();

	return 0;
}
