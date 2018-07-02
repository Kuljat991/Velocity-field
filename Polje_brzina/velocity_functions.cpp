#include "velocity_functions.h"
#include <math.h>

void sinusoida ( const state_type  &/*state*/,  state_type &dxdt , const double t )
{
    dxdt[0] = 1;
    dxdt[1] = cos ( t );
}

void const_kruzno_gibanje ( const state_type  &state,  state_type &dxdt , const double /*t*/ )
{

    dxdt[0] = -state[1]/ ( state[0]*state[0]+state[1]*state[1] );
    dxdt[1] =  state[0]/ ( state[0]*state[0]+state[1]*state[1] );
}

void kruzno_gibanje ( const state_type  &state,  state_type &dxdt , const double t )
{

    dxdt[0] = -state[1]/ ( state[0]*state[0]+state[1]*state[1] ) + sin(t);
    dxdt[1] =  state[0]/ ( state[0]*state[0]+state[1]*state[1] ) + cos(t);
}
