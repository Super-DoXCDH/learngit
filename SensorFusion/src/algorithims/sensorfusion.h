#pragma once
//@ filename: /algorithims/sensorfusion.h
#pragma once

#include "../interface/measurement_package.h"
#include "kalman.h"

class SensorFusion {
public:
	SensorFusion();
	~SensorFusion();

	void Process(MeasurementPackage measurement_pack);
	KalmanFilter kf_;

private:
	bool is_initialized_;
	long last_timestamp_;
	Eigen::MatrixXd R_lidar_;
	Eigen::MatrixXd R_radar_;
	Eigen::MatrixXd H_lidar_;
};