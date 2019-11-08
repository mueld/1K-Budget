#ifndef FirstRound_h
#define FirstRound_h

enum FirstRound_State
{
    FirstRound_Start,
    FirstRound_Drive,
    FirstRound_Idle,
    FirstRound_Finish
}

class FirstRound
{
private:
    FirstRound_State State;

public:
    void ExecuteStateMachine();
};

#endif