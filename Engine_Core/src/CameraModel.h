#ifndef CAMERA_MODEL_H
#define CAMERA_MODEL_H

#include "Model.h"

class CameraModel : public Model
{
public:
	CameraModel( const char * const modelFileName );
	~CameraModel();

	void update();


	// tells the compiler do not create or allow it to be used, c++11
	CameraModel(const CameraModel &) = delete;
	CameraModel& operator=(const CameraModel & other) = delete;
private:
	void privCreateVAO( const char * const modelFileName  ) override;



};

#endif