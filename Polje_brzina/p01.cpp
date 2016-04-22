#include <QCoreApplication>
#include "qdebug.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include <boost/math/constants/constants.hpp>

using namespace boost::math::double_constants;

typedef std::vector< double > state_type;

/**
 * Testna f-ja 1
 * dx/dt = 1
 * dy/dt = cos(t)
 * Ocekujemo: 
 * x = t + x0
 * y = sin(t) + y0 
 */
void testfun_01 ( const state_type  &/*state*/,  state_type &dxdt , const double t)
{
    dxdt[0] = 1;
    dxdt[1] = cos (t);
}

// 
struct push_back_state_and_time
{
    std::vector< double >& m_states_x;
    std::vector< double >& m_states_y;
    std::vector< double >& m_times;

    push_back_state_and_time( std::vector< double > &states_x , std::vector< double > &states_y, std::vector< double > &times )
    : m_states_x( states_x ) ,m_states_y( states_y ), m_times( times ) { }

    void operator()( const state_type &x , double t )
    {
        m_states_x.push_back( x[0] );
        m_states_y.push_back( x[1] );
        m_times.push_back( t );
    }
};


int main()
{

    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> t;

    state_type pocetni_uvjeti = { 0.0 , 0.0 };

    const double start_time = 0.;
    const double end_time = 2*pi;
    const double integration_step = pi/16;
    boost::numeric::odeint::runge_kutta4< state_type > stepper;
    boost::numeric::odeint::integrate_const( stepper , testfun_01 , 
                                             pocetni_uvjeti , 
                                             start_time , end_time , integration_step, 
                                             push_back_state_and_time(x,y,t) );

    std::stringstream stream;
    for(size_t i=0; i< t.size(); ++i)
    {
        stream<< t[i]<<"\t"<<x[i]<<"\t"<<y[i]<<"\n";
    }
    std::cout<<stream.str();
    
    return 0;
}

