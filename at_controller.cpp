#include "at_controller.h"

AtSettings AtController::settings(0); // Initial need to force paramter
QObject *AtController::root = NULL;

AtController::AtController()     {

}

AtController::~AtController() {

}
