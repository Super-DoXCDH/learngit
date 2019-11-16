#ifndef _MEASUREMENT_PACKAGE_H_//#ifndef起到的效果是防止一个源文件两次包含同一个头文件，而不是防止两个源文件包含同一个头文件
#define _MEASUREMENT_PACKAGE_H_//<标识>在理论上来说可以是自由命名的，但每个头文件的这个“标识”都应该是唯一的。
//标识的命名规则一般是头文件名全大写，前后加下划线，并把文件名中的“.”也变成下划线_

#include "Eigen/Dense"

class MeasurementPackage {
public:
  long long timestamp_;

  enum SensorType{
    LASER,
    RADAR
  } sensor_type_;

  Eigen::VectorXd raw_measurements_;
};

#endif /* MEASUREMENT_PACKAGE_H_ */
