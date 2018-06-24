#ifndef LOG_MODEL_H
#define LOG_MODEL_H
#include "Model.h"
class LogModel : public Model
{
public:

	LogModel(const char * const pModelFileName);

	LogModel() = delete;
	LogModel(const LogModel &) = delete;
	LogModel &operator=(const LogModel &) = delete;
	virtual ~LogModel();
private:
	virtual void privCreateVAO(const char * const modelfileNAME);

};
#endif // !CUBE_MLOG_MODEL_HODEL_H

