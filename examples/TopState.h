
/**
 * 	############# Example of use: ######################3
 *
 *
 *	TopState *top = new TopState();
 *	top->init();
 *	top->dispatchEvents();
 *	top->raiseEvent(new Event(TopState::ev1));
 *	top->dispatchEvents();
 *	top->raiseEvent(new Event(TopState::ev2));
 *	top->dispatchEvents();
 *	top->raiseEvent(new Event(TopState::ev3));
 *	top->dispatchEvents();
 *	top->raiseEvent(new Event(TopState::ev4));
 *	top->dispatchEvents();
 *	top->raiseEvent(new Event(TopState::ev5));
 *	top->dispatchEvents();
 *	top->raiseEvent(new Event(TopState::ev1));
 *	top->dispatchEvents();
 *	top->raiseEvent(new Event(TopState::ev5));
 *	top->dispatchEvents();
 *	top->raiseEvent(new Event(TopState::ev4));
 *	top->dispatchEvents();
 *
 */
#ifndef TEMPLATEHSM_H_
#define TEMPLATEHSM_H_

#include "State.h"
using namespace hsm;

/*! \file Header of the state machine 'SysManagerHSM'.
*/
class TopState : public Hsm {	
public:	
	class S0 : public State{
	public:
		S0(State * parent = (State*)0, void * xif = 0) : State(parent, xif){
			// inserto manejadores de evento
			attach(TopState::ev1, this, (State* (State::*)(Event*))&S0::onEv1);
		}
		// Implementaciones entry/exit
		virtual State* entry(){
			((TopState*)_xif)->_data = 0;
			DONE();
		}
		virtual void exit(){
		}	
		// Manejadores de eventos
		State* onEv1(Event* e){
			((TopState*)_xif)->_data=1;
			TRAN(((TopState*)_parent)->s2);
		}
	}; friend class S0;

	class S1 : public State{
	public:
		S1(State * parent = (State*)0, void * xif = 0) : State(parent, xif){
			// inserto manejadores de evento
			attach(TopState::ev2, this, (State* (State::*)(Event*))&S1::onEv2);
			attach(TopState::ev4, this, (State* (State::*)(Event*))&S1::onEv4);
		}
		// Implementaciones entry/exit
		virtual State* entry(){
			DONE();
		}
		virtual void exit(){
		}	
		// Manejadores de eventos
		State* onEv2(Event* e){
			((TopState*)_xif)->_data=2;
			DONE();
		}
		State* onEv4(Event* e){
			((TopState*)_xif)->_data=4;
			TRAN(((TopState*)_parent)->s0);
		}
	}; friend class S1;

	class S2 : public State{
	public:
		S2(State * parent = (State*)0, void * xif = 0) : State(parent, xif){
			// inserto manejadores de evento
			attach(TopState::ev3, this, (State* (State::*)(Event*))&S2::onEv3);
		}
		// Implementaciones entry/exit
		virtual State* entry(){
			DONE();
		}
		virtual void exit(){
		}	
		// Manejadores de eventos
		State* onEv3(Event* e){
			((TopState*)_xif)->_data=3;
			TRAN(((TopState*)_xif)->s0);
		}
	}; friend class S2;



	// Estados
	S0 *s0;
	S1 *s1;
	S2 *s2;
	// Eventos
	static const uint32_t ev1 = (USER_SIG << 0);
	static const uint32_t ev2 = (USER_SIG << 1);
	static const uint32_t ev3 = (USER_SIG << 2);
	static const uint32_t ev4 = (USER_SIG << 3);
	static const uint32_t ev5 = (USER_SIG << 4);
	// Variables
	int _data;
	
	TopState() : Hsm(){
		// creo estados
		s0 = new S0(this, this);
		s1 = new S1(this, this);
		s2 = new S2(s1, this);
		// Inserto estados
		attachState(s0);
		attachState(s1);
		attachState(s2);
		// Inserto manejadores de evento
		attach(ev2, this, (State* (State::*)(Event*))&TopState::onEv2);		
		attach(ev5, this, (State* (State::*)(Event*))&TopState::onEv5);		
	}
		
	/** Interface for inheritance */
	virtual State* entry(){
		_data=0;
		TRAN(s0);
	}
	virtual void exit(){
	}

	// Manejadores de eventos
	State* onEv2(Event* e){
		_data =2;
		DONE();
	}
	State* onEv5(Event* e){
		_data =5;
		DONE();
	}

			
};

#endif /* TEMPLATEHSM_H_ */
