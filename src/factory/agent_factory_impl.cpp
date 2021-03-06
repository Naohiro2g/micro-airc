#include "../include/agent_factory_impl.h"

namespace airc{


    Agent* AgentFactory::create(const char* agent_name){
        MotorDriver* motorDriver = new DRV8835Impl();
        motorDriver->init();

        RangeSensor* rangeSensor = new airc::RangeSensorImpl();
        rangeSensor->setAddress((uint8_t)21,(uint8_t)22,(uint8_t)20);
        
        Agent* agent = nullptr;

        if(!strcmp(agent_name, "pidagent")){
            agent = new PidAgentImpl(); 
            agent->initialize(motorDriver, rangeSensor);
        }

        if(!strcmp(agent_name, "ragent")){
            agent = new RemoteAgentImpl();
            agent->initialize(motorDriver, rangeSensor);
        }
        
        if(!strcmp(agent_name, "nnagent")){
            agent = new NNAgentImpl(); 
            TfMicroWrapper* tfMicroWrapper = new TfMicroWrapper();
            tfMicroWrapper->initialize();
            ((NNAgentImpl*)agent)->initialize(motorDriver, rangeSensor, tfMicroWrapper);
        }


        return agent;

    };
}


