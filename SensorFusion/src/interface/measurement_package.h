#ifndef _MEASUREMENT_PACKAGE_H_//#ifndef�𵽵�Ч���Ƿ�ֹһ��Դ�ļ����ΰ���ͬһ��ͷ�ļ��������Ƿ�ֹ����Դ�ļ�����ͬһ��ͷ�ļ�
#define _MEASUREMENT_PACKAGE_H_//<��ʶ>����������˵���������������ģ���ÿ��ͷ�ļ����������ʶ����Ӧ����Ψһ�ġ�
//��ʶ����������һ����ͷ�ļ���ȫ��д��ǰ����»��ߣ������ļ����еġ�.��Ҳ����»���_

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
