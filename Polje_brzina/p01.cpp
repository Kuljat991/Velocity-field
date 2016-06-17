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
#include "velocity_functions.h"

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


struct push_back_state_and_time
{
    vector< double >& m_states_x;
    vector< double >& m_states_y;
    vector< double >& m_times;

    push_back_state_and_time ( vector< double > &states_x , vector< double > &states_y, vector< double > &times )
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
    vector< state_type > pocetni_uvjeti;
    pocetni_uvjeti.push_back({1.0, 0.0});
    pocetni_uvjeti.push_back({1.5, 0.0});
    pocetni_uvjeti.push_back({2.0, 0.0});

    const double start_time = 0.;
    const double end_time = 2*pi;
    const double integration_step = pi/16;
    runge_kutta4< state_type > stepper;

    for (size_t i= 0; i< pocetni_uvjeti.size(); i++ ){
        integrate_const ( stepper , sinusoida ,
                          pocetni_uvjeti[i] ,
                          start_time , end_time , integration_step,
                          push_back_state_and_time ( x,y,t ) );
    }
    draw ( std::cout, x,y,t );

}

struct particle_solution
{
    particle_solution(const std::string& n): name(n) {}
    std::string name;
    vector<double> x;
    vector<double> y;
    vector<double> t;
};
void drugitest()
{
    using namespace boost::numeric::odeint;
    vector<particle_solution> solutions;
    solutions.emplace_back("1");
    solutions.emplace_back("2");
    solutions.emplace_back("3");
    
    std::cout<<solutions.size()<<std::endl;

    vector< state_type > pocetni_uvjeti;
    pocetni_uvjeti.push_back({1.0, 0.0});
    pocetni_uvjeti.push_back({1.5, 0.0});
    pocetni_uvjeti.push_back({2.0, 0.0});

    const double start_time = 0.;
    const double end_time = 2*pi;
    const double integration_step = pi/100;
    runge_kutta4< state_type > stepper;
    //state_type pocetni_uvjeti = { 1.0 , 0.0 };

    std::ofstream fout( resultsPath + "/velocity_data.txt");
    fout<<"const_kruzno_gibanje\n";
    fout.close();
    for (size_t i= 0; i< pocetni_uvjeti.size(); i++ )
    {
        integrate_adaptive ( stepper , const_kruzno_gibanje ,
                             pocetni_uvjeti[i] ,
                             start_time , end_time , integration_step,
                             push_back_state_and_time ( solutions[i].x,solutions[i].y,solutions[i].t ) );
        //draw ( std::cout, x[i],y[i],t[i] );
    }
    int i=0;
    for(const auto& s : solutions)
    {
        
        std::ofstream fout( resultsPath + "/" + std::to_string(i) + ".txt");
        draw ( fout, s.x,s.y,s.t );
        fout.close();
        ++i;
    }
    
}

int main()
{

    //prvitest();
    std::cout<<"**************\n";
    drugitest();
    std::cout<<"**************\n";

    return 0;
}
