#include "handler.h"
#include "handler_manager.h"

RegisterHandler::RegisterHandler(const std::string &name, Handler handler, HandlerPermission permissions) {
    HandlerManager::instance().addHandler(name, handler, permissions);
}
