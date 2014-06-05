//ROS typedefs
#include "ros/ros.h"
#include <cob_relayboard/EmergencyStopState.h>
#include <std_msgs/Float64.h>

//#include <libphidgets/phidget21.h>


class cob_voltage_control_config
{
public:
    double min_voltage;
    double max_voltage;
    double max_voltage_res;
    int num_voltage_port;
    int num_em_stop_port;
    int num_scanner_em_port;
};

class cob_voltage_control_data
{
// autogenerated: don't touch this class
public:
    //configuration data

    //input data
    int in_phidget_voltage;

    //output data
    cob_relayboard::EmergencyStopState out_pub_relayboard_state;
    std_msgs::Float64 out_pub_voltage;    
};

//document how this class has to look
//never change after first generation
class cob_voltage_control_impl
{

public:

    //CPhidgetInterfaceKitHandle IFK;
    cob_voltage_control_impl()
    {
        //user specific code
    }
    void configure() 
    {
    }
    void update(cob_voltage_control_data &data, cob_voltage_control_config config)
    {
        //user specific code
        //Get Battery Voltage
        int voltageState = -1;
//      CPhidgetInterfaceKit_getSensorValue((CPhidgetInterfaceKitHandle)IFK, config.num_voltage_port, &voltageState);
        voltageState = data.in_phidget_voltage;
        ROS_DEBUG("Sensor: %d", voltageState);

        //Calculation of real voltage 
        //max_voltage = 70V ; max_counts = 999
        double max_counts = 725.0; // 3v => max
        double voltage = voltageState * config.max_voltage_res/max_counts;
        data.out_pub_voltage.data = voltage;
        ROS_DEBUG("Current voltage %f", voltage);

        //Linear calculation for percentage
        double percentage =  (voltage - config.min_voltage) * 100/(config.max_voltage - config.min_voltage);




    }
    
    void exit()
    {
    }

};
