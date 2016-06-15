#include "../include/nautonomous_output_operator_lowlevel/OperatorPublisher.hpp"

void check_publishing(){
    if(propulsionMessage){
        publish_propulsion();
        delete propulsionMessage;
        propulsionMessage = nullptr;
    }
    if(conveyorMessage){
        publish_conveyor();
        delete conveyorMessage;
        conveyorMessage = nullptr;
    }
    if(lightingMessage){
        publish_lighting();
        delete lightingMessage;
        lightingMessage = nullptr;
    }
}

void publish_propulsion() {
    if(propulsionMessage){
        propulsionPub.publish(*propulsionMessage);
        delete propulsionMessage;
        propulsionMessage = nullptr;
    }
}
void publish_conveyor() {
    if(conveyorMessage){
        conveyorPub.publish(*conveyorMessage);
        delete conveyorMessage;
        conveyorMessage = nullptr;
    }
}
void publish_lighting() {
    if(lightingMessage){
        lightingPub.publish(*lightingMessage);
        delete lightingMessage;
        lightingMessage = nullptr;
    }
}
