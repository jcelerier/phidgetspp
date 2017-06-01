#pragma once
#include <phidget21.h>
#include <functional>
namespace ppp
{

struct interface_kit
{
public:
    interface_kit(CPhidgetInterfaceKitHandle h):
        m_handle{h}
    {
        CPhidgetInterfaceKit_set_OnInputChange_Handler(
                    m_handle,
                    [] (CPhidgetInterfaceKitHandle, void *userPtr, int index, int st) -> int {
            auto& self = *(interface_kit*)(userPtr);
            if(self.onInputChange)
                self.onInputChange(index, st);

        }, this);
        CPhidgetInterfaceKit_set_OnOutputChange_Handler(
                    m_handle,
                    [] (CPhidgetInterfaceKitHandle, void *userPtr, int index, int st) -> int {
            auto& self = *(interface_kit*)(userPtr);
            if(self.onOutputChange)
                self.onOutputChange(index, st);

        }, this);
        CPhidgetInterfaceKit_set_OnSensorChange_Handler(
                    m_handle,
                    [] (CPhidgetInterfaceKitHandle, void *userPtr, int index, int sensorValue) -> int {
            auto& self = *(interface_kit*)(userPtr);
            if(self.onSensorChange)
                self.onSensorChange(index, sensorValue);
        }, this);
    }

    int get_sensor_count() const
    {
        int c;
        CPhidgetInterfaceKit_getSensorCount(m_handle, c);
        return c;
    }

    int get_sensor_value(int idx) const
    {
        int c;
        CPhidgetInterfaceKit_getSensorValue(m_handle, idx, c);
        return c;
    }

    int get_sensor_raw_value(int idx) const
    {
        int c;
        CPhidgetInterfaceKit_getSensorRawValue(m_handle, idx, c);
        return c;
    }

    int get_data_rate(int idx)
    {
        int ms;
        CPhidgetInterfaceKit_getDataRate(m_handle, idx, &ms);
        return ms;
    }

    void set_data_rate(int idx, int ms)
    {
        CPhidgetInterfaceKit_setDataRate(m_handle, idx, ms);
    }

    int inputs() const
    {
        int m;
        CPhidgetInterfaceKit_getInputCount(m_handle, &m);
        return m;
    }

    int outputs() const
    {
        int m;
        CPhidgetInterfaceKit_getOutputCount(m_handle, &m);
        return m;
    }

    std::function<void(int, int)> onInputChange;
    std::function<void(int, int)> onOutputChange;
    std::function<void(int, int)> onSensorChange;

private:
    CPhidgetInterfaceKitHandle m_handle;
};

struct accelerometer
{
public:
    accelerometer(CPhidgetAccelerometerHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetAccelerometerHandle m_handle;
};

struct advanced_servo
{
public:
    advanced_servo(CPhidgetAdvancedServoHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetAdvancedServoHandle m_handle;
};

struct bridge
{
public:
    bridge(CPhidgetBridgeHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetBridgeHandle m_handle;
};

struct frequency_counter
{
public:
    frequency_counter(CPhidgetFrequencyCounterHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetFrequencyCounterHandle m_handle;
};

struct gps
{
public:
    gps(CPhidgetGPSHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetGPSHandle m_handle;
};

struct ir
{
public:
    ir(CPhidgetIRHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetIRHandle m_handle;

};

struct led
{
public:
    led(CPhidgetLEDHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetLEDHandle m_handle;

};

struct motor_control
{
public:
    motor_control(CPhidgetMotorControlHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetMotorControlHandle m_handle;
};

struct ph_sensor
{
public:
    ph_sensor(CPhidgetPHSensorHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetPHSensorHandle m_handle;

};

struct rfid
{
public:
    rfid(CPhidgetRFIDHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetRFIDHandle m_handle;
};


struct servo
{
public:
    servo(CPhidgetServoHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetServoHandle m_handle;
};


struct spatial
{
public:
    spatial(CPhidgetSpatialHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetSpatialHandle m_handle;
};

struct stepper
{
public:
    stepper(CPhidgetStepperHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetStepperHandle m_handle;
};


struct temperature_sensor
{
public:
    temperature_sensor(CPhidgetTemperatureSensorHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetTemperatureSensorHandle m_handle;
};

struct text_lcd
{
public:
    text_lcd(CPhidgetTextLCDHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetTextLCDHandle m_handle;
};

struct text_led
{
public:
    text_led(CPhidgetTextLEDHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetTextLEDHandle m_handle;
};


struct weight_sensor
{
public:
    weight_sensor(CPhidgetWeightSensorHandle h):
        m_handle{h}
    {

    }
private:
    CPhidgetWeightSensorHandle m_handle;
};

}
