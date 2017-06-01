#pragma once
#include "sensors.hpp"
#include <string>
#include <functional>
namespace ppp
{

struct phidget
{
public:
    phidget(CPhidgetHandle hdl):
        m_handle{hdl}
    {
        CPhidget_set_OnDetach_Handler(m_handle, [] (CPhidgetHandle phid, void *userPtr) -> int { }, this);
        CPhidget_set_OnAttach_Handler(m_handle, [] (CPhidgetHandle phid, void *userPtr) -> int{ }, this);
        CPhidget_set_OnServerConnect_Handler(m_handle, [] (CPhidgetHandle phid, void *userPtr) -> int{ }, this);
        CPhidget_set_OnServerDisconnect_Handler(m_handle,  [] (CPhidgetHandle phid, void *userPtr) -> int{ }, this);
        CPhidget_set_OnError_Handler(m_handle, [] (CPhidgetHandle phid, void *userPtr, int errorCode, const char *errorString) -> int { }, this);


        CPhidget_open((CPhidgetHandle)IFK, -1);

        CPhidget_getDeviceClass(m_handle, &m_class);
        CPhidget_getDeviceID(m_handle, &m_id);
        CPhidget_getDeviceStatus(m_handle, &m_status);
        CPhidget_getSerialNumber(m_handle, &m_serial);

        const char* name;
        if(auto r = CPhidget_getDeviceName(m_handle, &name))
            m_name = name;

        const char* type;
        if(auto r = CPhidget_getDeviceType(m_handle, &type))
            m_type = type;

        const char* label;
        if(auto r = CPhidget_getDeviceLabel(m_handle, &label))
            m_label = label;

    }

    std::function<void()> onAttach;
    std::function<void()> onDetach;
    std::function<void()> onConnect;
    std::function<void()> onDisconnect;
    std::function<void(int, const char*)> onError;

    const std::string& name() const { return m_name; }
    const std::string& type() const { return m_type; }
    const std::string& label() const { return m_label; }
    int serial() const { return m_serial; }
    int status() const { return m_status; }

    void set_name(const std::string& n) {
        CPhidget_setDeviceLabel(m_handle, n.data());
        m_label = n;
    }


private:
  CPhidgetHandle m_handle;

  CPhidget_DeviceClass m_class;
  CPhidget_DeviceID m_id;

  std::string m_name;
  std::string m_type;
  std::string m_label;
  int m_serial;
  int m_status;
};
class phidgets_manager
{

    phidgets_manager()
    {

        // Tree :
        // Phidgets:/device/...

        // For each device, create the relevant keys.


        CPhidgetManager_create(&m_hdl);
        CPhidgetManager_set_OnAttach_Handler(m_hdl,
        [] (CPhidgetHandle phid, void *ptr) -> int {
            auto self = (phidgets_manager*) ptr;


        }, this);

        CPhidgetManager_set_OnDetach_Handler(m_hdl,
        [] (CPhidgetHandle phid, void *ptr) -> int {
            auto self = (phidgets_manager*) ptr;
        }, this);

        CPhidgetManager_open(m_hdl);
    }
    ~phidgets_manager()
    {
        CPhidgetManager_close(m_hdl);
        CPhidgetManager_delete(m_hdl);
    }

    CPhidgetManagerHandle m_hdl{};
};

}
