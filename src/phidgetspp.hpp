#pragma once
#include "sensors.hpp"
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <memory>
//#include <variant>
namespace ppp
{
//using sensor_variant = std::variant<std::monostate, interface_kit>;

struct phidget
{
  public:
    phidget(CPhidgetHandle hdl)
    {
      CPhidget_set_OnError_Handler(
            hdl,
            [] (CPhidgetHandle phid, void *userPtr, int errorCode, const char *errorString) -> int {
        std::cerr << "Error: " << errorString << std::endl;
      }, this);

      CPhidget_getDeviceClass(hdl, &m_class);
      CPhidget_getDeviceID(hdl, &m_id);
      CPhidget_getDeviceStatus(hdl, &m_status);
      CPhidget_getSerialNumber(hdl, &m_serial);

      const char* name;
      if(!CPhidget_getDeviceName(hdl, &name))
        m_name = name;

      const char* type;
      if(!CPhidget_getDeviceType(hdl, &type))
        m_type = type;

      const char* label;
      if(!CPhidget_getDeviceLabel(hdl, &label))
        m_label = label;

      switch(m_class)
      {
        case PHIDCLASS_INTERFACEKIT:
        {
          auto h = (CPhidgetInterfaceKitHandle)m_handle;
          CPhidgetInterfaceKit_create(&h);
          m_handle = (CPhidgetHandle)h;
          m_ik = std::make_unique<interface_kit>((CPhidgetInterfaceKitHandle)m_handle);
          CPhidget_open((CPhidgetHandle)m_handle, m_serial);
          m_ik->onSensorChange = [] (int a , int b) { std::cerr << "value: " << a << " : " << b << std::endl; };
          break;
        }
      }
    }

    int get_sensor_value(int sensor)
    {
      if(m_ik)
      {
        return m_ik->get_sensor_value(sensor);
      }
      return 0;
    }

    std::function<void()> onAttach;
    std::function<void()> onDetach;
    std::function<void()> onConnect;
    std::function<void()> onDisconnect;
    std::function<void(int, const char*)> onError;

    CPhidgetHandle handle() const { return m_handle; }
    const std::string& name() const { return m_name; }
    const std::string& type() const { return m_type; }
    const std::string& label() const { return m_label; }
    int serial() const { return m_serial; }
    int status() const { return m_status; }

    void set_name(const std::string& n) {
      CPhidget_setDeviceLabel(m_handle, n.data());
      m_label = n;
    }

    ~phidget()
    {
      CPhidget_close(m_handle);
      CPhidget_delete(m_handle);
    }

  private:
    CPhidgetHandle m_handle{};

    CPhidget_DeviceClass m_class{};
    CPhidget_DeviceID m_id{};

    std::string m_name;
    std::string m_type;
    std::string m_label;
    int m_serial{};
    int m_status{};

    std::unique_ptr<interface_kit> m_ik;

};
class phidgets_manager
{
  public:
    phidgets_manager()
    {
        CPhidget_enableLogging(PHIDGET_LOG_VERBOSE, NULL);

      // Tree :
      // Phidgets:/device/...

      // For each device, create the relevant keys.
      CPhidgetManager_create(&m_hdl);
      CPhidgetManager_set_OnAttach_Handler(m_hdl,
                                           [] (CPhidgetHandle phid, void *ptr) -> int {
        auto& self = *(phidgets_manager*) ptr;
        self.m_phidgets.push_back(std::make_unique<phidget>(phid));
      }, this);

      CPhidgetManager_set_OnDetach_Handler(m_hdl,
                                           [] (CPhidgetHandle phid, void *ptr) -> int {
        auto& self = *(phidgets_manager*) ptr;
        auto it = std::find_if(self.m_phidgets.begin(), self.m_phidgets.end(),
                               [=] (auto& e) { return e->handle() == phid; });
        if(it != self.m_phidgets.end())
          self.m_phidgets.erase(it);
      }, this);

      CPhidgetManager_open(m_hdl);
    }

    ~phidgets_manager()
    {
      m_phidgets.clear();
      CPhidgetManager_close(m_hdl);
      CPhidgetManager_delete(m_hdl);
    }

    CPhidgetManagerHandle m_hdl{};

    std::vector<std::unique_ptr<phidget>> m_phidgets;
};

}
