#ifndef  _VoidHandler_H_
#define  _VoidHandler_H_

class VoidHandler{
public:
    
    virtual void execute(void * data = nullptr) = 0;
    
    ~VoidHandler(){}
};

#endif // _VoidHandler_H_