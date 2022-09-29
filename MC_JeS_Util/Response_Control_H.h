#ifndef  Response_Control_H
#define  Response_Control_H 

#include <iostream>
class Response_vs_E_true {
public:
    unsigned N_Jets;
    Response_vs_E_true();
    void Response_Control();
};
Response_vs_E_true::Response_vs_E_true(){
    N_Jets =0;
}
#endif