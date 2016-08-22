#include <QDebug>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>
#include <boost/math/constants/constants.hpp>
#include "pathconfig.h"
#include "velocity_functions.h"
#include "utility.h"
#include "ThreadPoint.h"

using namespace boost::math::double_constants;
using std::vector;
using std::ostream;
typedef std::vector< double > state_type;


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
    std::ofstream fout( resultsPath + "/VectorField.txt");
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
