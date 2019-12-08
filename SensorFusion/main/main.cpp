#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>
#include "../algorithims/sensorfusion.h"
#include "../algorithims/kalman.h"

#include "../interface/ground_truth_package.h"
#include "../interface/measurement_package.h"
#include <Eigen/Dense>

int main(int argc, char* argv[]) {

    // 设置毫米波雷达/激光雷达输入数据的路径
    // Set radar & lidar data file path
    // 请写自己文件的绝对路径!!!!
    std::string input_file_name = "/home/superdo/Documents/SensorFusion/data/sample-laser-radar-measurement-data-2.txt";

    // 打开数据，若失败则输出失败信息，返回-1，并终止程序
    // Open file. if failed return -1 & end program
    std::ifstream input_file;
    input_file.open(input_file_name);
    if (input_file.fail()) {
        std::cout << "Failed to open file + named : " << input_file_name << std::endl;
        std::cout << "请填写自己电脑data数据的绝对路径" << std::endl;
       	return -1;
    }

    // 分配内存
    // measurement_pack_list：毫米波雷达/激光雷达实际测得的数据。数据包含测量值和时间戳，即融合算法的输入。
    // groundtruth_pack_list：每次测量时，障碍物位置的真值。对比融合算法输出和真值的差别，用于评估融合算法结果的好坏。
    std::vector<MeasurementPackage> measurement_pack_list;
    std::vector<GroundTruthPackage> groundtruth_pack_list;

    // 通过while循环将雷达测量值和真值全部读入内存，存入measurement_pack_list和groundtruth_pack_list中
    // Store radar & lidar data into memory
    std::string line;
    while (std::getline(input_file, line)) {
		std::cout << line << std::endl;
        std::string sensor_type;
        MeasurementPackage meas_package;
        GroundTruthPackage gt_package;
        std::istringstream iss(line);
        long long timestamp;

        // 读取当前行的第一个元素，L代表Lidar数据，R代表Radar数据
        // Reads first element from the current line. L stands for Lidar. R stands for Radar.
        iss >> sensor_type;
        if (sensor_type.compare("L") == 0) {
            // 激光雷达数据 Lidar data
            // 该行第二个元素为测量值x，第三个元素为测量值y，第四个元素为时间戳(纳秒）
            // 2nd element is x; 3rd element is y; 4th element is timestamp(nano second)
            meas_package.sensor_type_ = MeasurementPackage::LASER;
            meas_package.raw_measurements_ = Eigen::VectorXd(2);
            float x;
            float y;
            iss >> x;
            iss >> y;
            meas_package.raw_measurements_ << x, y;
            iss >> timestamp;
            meas_package.timestamp_ = timestamp;
            measurement_pack_list.push_back(meas_package);
        } else if (sensor_type.compare("R") == 0) {
            // 毫米波雷达数据 Radar data
            // 该行第二个元素为距离pho，第三个元素为角度phi，第四个元素为径向速度pho_dot，第五个元素为时间戳(纳秒）
            // 2nd element is pho; 3rd element is phi; 4th element is pho_dot; 5th element is timestamp(nano second)
            meas_package.sensor_type_ = MeasurementPackage::RADAR;
            meas_package.raw_measurements_ = Eigen::VectorXd(3);
            float rho;
            float phi;
            float rho_dot;
            iss >> rho;
            iss >> phi;
            iss >> rho_dot;
            meas_package.raw_measurements_ << rho, phi, rho_dot;
            iss >> timestamp;
            meas_package.timestamp_ = timestamp;
            measurement_pack_list.push_back(meas_package);
        }

        // 当前行的最后四个元素分别是x方向上的距离真值，y方向上的距离真值，x方向上的速度真值，y方向上的速度真值
        // read ground truth data to compare later
        float x_gt;
        float y_gt;
        float vx_gt;
        float vy_gt;
        iss >> x_gt;
        iss >> y_gt;
        iss >> vx_gt;
        iss >> vy_gt;
        gt_package.gt_values_ = Eigen::VectorXd(4);
        gt_package.gt_values_ << x_gt, y_gt, vx_gt, vy_gt;
        groundtruth_pack_list.push_back(gt_package);
    }

    std::cout << "Success to load data." << std::endl;
    input_file.close();
    // 开始部署跟踪算法
	SensorFusion fuser;
	for (size_t i = 0; i < measurement_pack_list.size(); ++i) {
		fuser.Process(measurement_pack_list[i]);
		Eigen::Vector4d x_out = fuser.kf_.GetX();
		// 输出跟踪后的位置
		std::cout << "x " << x_out(0)
			<< " y " << x_out(1)
			<< " vx " << x_out(2)
			<< " vy " << x_out(3)
			<< std::endl;
	}

}
