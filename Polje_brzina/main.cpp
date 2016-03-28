#include <QCoreApplication>
#include "qdebug.h"

#include <boost/numeric/odeint.hpp>

using namespace boost::numeric::odeint;

typedef std::vector< double > state_type;

void ubrzanje ( const state_type &x , state_type &dxdt , const double )
{
    dxdt[0] = x[1];
    dxdt[1] = x[2];
    dxdt[2] = 5.0;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    state_type x = { 1.0 , 1.0 , 1.0 };
    runge_kutta4< state_type > stepper;
    integrate_const( stepper , ubrzanje , x , 0.0 , 10.0 , 0.01 );

    return a.exec();
}

