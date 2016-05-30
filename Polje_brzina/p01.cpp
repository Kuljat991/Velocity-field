#include <QDebug>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include "pathconfig.h"

using namespace boost::math::double_constants;
using std::vector;
using std::ostream;
typedef std::vector< double > state_type;

/**
 * Testna f-ja 1
 * dx/dt = 1
 * dy/dt = cos(t)
 * Ocekujemo:
 * x = t + x0
 * y = sin(t) + y0
 */
void sinusoida ( const state_type  &/*state*/,  state_type &dxdt , const double t )
{
    dxdt[0] = 1;
    dxdt[1] = cos ( t );
}

/**
 * Testna f-ja 1
 * Stacionarno vektorsko polje brzina - ne mijenja se u vremenu
 * \nabla \times \mathbf{v} = 0
 * gdje je \mathbf{v} = \left( -\frac{y}{x^2+y^2}, \frac{x}{x^2+y^2} \right)
 *
 * Za render copy/paste ovdje: http://arachnoid.com/latex/
 *
 * Rješenje: svugdje vektori jednake duljine (1) i kružno gibanje oko (0,0)
 */
void kruzno_gibanje ( const state_type  &state,  state_type &dxdt , const double /*t*/ )
{

    dxdt[0] = -state[1]/ ( state[0]*state[0]+state[1]*state[1] );
    dxdt[1] =  state[0]/ ( state[0]*state[0]+state[1]*state[1] );
}

struct push_back_state_and_time
{
    std::vector< double >& m_states_x;
    std::vector< double >& m_states_y;
    std::vector< double >& m_times;

    push_back_state_and_time ( std::vector< double > &states_x , std::vector< double > &states_y, std::vector< double > &times )
        : m_states_x ( states_x ) ,m_states_y ( states_y ), m_times ( times ) { }

    void operator() ( const state_type &x , double t )
    {
        m_states_x.push_back ( x[0] );
        m_states_y.push_back ( x[1] );
        m_times.push_back ( t );
    }
};

void draw ( std::ostream &os,const vector<double> &x, const vector<double> &y, const vector<double> &t )
{
    std::stringstream stream;

    for ( size_t i=0; i< t.size(); ++i )
    {
        stream << t[i]<<"\t"<<x[i]<<"\t"<<y[i]<<"\n";
    }

    os<<stream.str() <<"\n";
}


void prvitest()
{
    using namespace boost::numeric::odeint;
    vector<double> x;
    vector<double> y;
    vector<double> t;

    const double start_time = 0.;
    const double end_time = 2*pi;
    const double integration_step = pi/16;
    runge_kutta4< state_type > stepper;
    state_type pocetni_uvjeti = { 0.0 , 0.0 };
    integrate_const ( stepper , sinusoida ,
                      pocetni_uvjeti ,
                      start_time , end_time , integration_step,
                      push_back_state_and_time ( x,y,t ) );
    
    draw ( std::cout, x,y,t );
}

void drugitest()
{
    using namespace boost::numeric::odeint;
    vector<double> x;
    vector<double> y;
    vector<double> t;

    const double start_time = 0.;
    const double end_time = 2*pi;
    const double integration_step = pi/100;
    runge_kutta4< state_type > stepper;
    state_type pocetni_uvjeti = { 1.0 , 0.0 };

    integrate_adaptive ( stepper , kruzno_gibanje ,
                         pocetni_uvjeti ,
                         start_time , end_time , integration_step,
                         push_back_state_and_time ( x,y,t ) );
    draw ( std::cout, x,y,t );
    std::ofstream fout( resultsPath + "/VectorField_const.txt");
    draw ( fout, x,y,t );
    fout.close();
    
}

int main()
{

    prvitest();
    std::cout<<"**************\n";
    drugitest();
    std::cout<<"**************\n";

    return 0;
}
