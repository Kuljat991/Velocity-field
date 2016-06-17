#include "velocity_functions.h"

void const_kruzno_gibanje ( const state_type  &state,  state_type &dxdt , const double /*t*/ )
{

    dxdt[0] = -state[1]/ ( state[0]*state[0]+state[1]*state[1] );
    dxdt[1] =  state[0]/ ( state[0]*state[0]+state[1]*state[1] );
}