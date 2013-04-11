//RESPONSIBILITY: Ben was responsible for designing, implementing, and testing this class.

#ifndef AB__STATUSLOG_H
#define AB__STATUSLOG_H
//DESCRIPTION
/*
This class displays messages to the user showing which drones were killed by which. 
*/
//CLASSES
class StatusLog;

//INCLUDES
#include <memory>
#include <vector>
#include "HUDElement.h"

//ENUMERATIONS


//DEFINITIONS
#define AB_STATUSLOG_NUM_HUDS 3
#define AB_STATUSLOG_HUD_TEXT_SIZE 12

//BEGIN
class StatusLog {
private:
	std::vector<std::shared_ptr<HUDElement>> hudList;

	//moves the string elements down the list
	void propagate();
public:
	StatusLog(float, float);

	void setWarningString(const std::string&);
	void setSuccessString(const std::string&);
	void setInfoString(const std::string&);
	void setString(const std::string&, int rColor, int gColor, int bColor);

	void clear();
};


#endif //AB__STATUSLOG_H