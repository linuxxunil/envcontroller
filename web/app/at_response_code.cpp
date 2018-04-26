#include "at_response_code.h"


QString AtResponseCode::MSG_BASE = "{\"message\":\"%1\",\"code\": %2,\"data\": [%3]}";

// OK
const QString AtResponseCode::MSG_OK =
    AtResponseCode::MSG_BASE.arg("OK").arg("0").arg("");

// Error
const QString AtResponseCode::MSG_UNKOWN_ERR =
    AtResponseCode::MSG_BASE.arg("Unkown error.").arg("-999").arg("");
const QString AtResponseCode::MSG_UNSUPPORT_RESOURCE =
    AtResponseCode::MSG_BASE.arg("This resource don't support.").arg("-1").arg("");
const QString AtResponseCode::MSG_UNLOGIN =
    AtResponseCode::MSG_BASE.arg("This session don't login.").arg("-2").arg("");

// User
const QString AtResponseCode::MSG_USER_LOGIN_ERR =
    AtResponseCode::MSG_BASE.arg("Username or Password is error.").arg("-101").arg("");

