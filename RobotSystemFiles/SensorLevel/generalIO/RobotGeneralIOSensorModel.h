/*
 * RobotGeneralIOSensorModel.h
 *
 *  Created on: 2017年4月7日
 *      Author: xin
 */

#ifndef USERFILES_MODEL_SENSORS_GENERALIO_ROBOTGENERALIOSENSORMODEL_H_
#define USERFILES_MODEL_SENSORS_GENERALIO_ROBOTGENERALIOSENSORMODEL_H_

#include "../../../RobotSystemFiles/SensorLevel/generalIO/GeneralIOSensorModel.h"

struct RobotGeneralIOSensorModel {

	struct GeneralIOSensorModel leftSideSitButton;
	struct GeneralIOSensorModel leftSideStandButton;
	struct GeneralIOSensorModel leftSideWalkButton;
	struct GeneralIOSensorModel leftSideStopButton;

	struct GeneralIOSensorModel rightSideSitButton;
	struct GeneralIOSensorModel rightSideStandButton;
	struct GeneralIOSensorModel rightSideWalkButton;
	struct GeneralIOSensorModel rightSideStopButton;

};

void RobotGeneralIOSensorModel_init(
		struct RobotGeneralIOSensorModel * robotGeneralIOSensorModel);

void RobotGeneralIOSensorModel_updateValue(
		struct RobotGeneralIOSensorModel * robotGeneralIOSensorModel);



#endif /* USERFILES_MODEL_SENSORS_GENERALIO_ROBOTGENERALIOSENSORMODEL_H_ */
