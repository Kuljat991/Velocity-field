#include <QDebug>
#include <math.h>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include "pathconfig.h"
#include "velocity_functions.h"
#include "utility.h"


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


void drugitest()
{
    std::string dir_path = resultsPath + "/const_field";
    create_folder(dir_path);

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

    std::ofstream fout( dir_path + "/velocity_data.txt");
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
        
        std::ofstream fout( dir_path + "/" + std::to_string(i) + ".txt");
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
