#include <QCoreApplication>
#include "qdebug.h"
#include <math.h>

#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>

typedef std::vector< double > state_type;

void funkcija ( const state_type  &x,  state_type &dxdt , const double)
{

    dxdt[0] = cos (x[0]);
    dxdt[1] = 1;

}

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


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::vector<double> x;
    std::vector<double> y;
    std::vector<double> t;

    state_type pocetni_uvijeti = { 0.0 , 0.0 };

    boost::numeric::odeint::runge_kutta4< state_type > stepper;
    boost::numeric::odeint::integrate_const( stepper , funkcija , pocetni_uvijeti , 0.0 , 5.0 , 0.1, push_back_state_and_time(x,y,t) );

    /* PROVIJERA
    QVector<double> qVec_x = QVector<double>::fromStdVector(x);
    QVector<double> qVec_y = QVector<double>::fromStdVector(y);
    QVector<double> qVec_t = QVector<double>::fromStdVector(t);
    qDebug()<< qVec_x.size() <<qVec_y <<qVec_t;
    */
    return a.exec();
}

