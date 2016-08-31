#include "ThreadPoint.h"
#include <QDebug>
#include "velocity_functions.h"

using namespace std;

ThreadPoint::ThreadPoint(const vector <state_type> &pocetni_uvjeti, vector <particle_solution> &solutions) :
    m_pocetni_uvjeti(pocetni_uvjeti), m_solutions(solutions)
{
}

void ThreadPoint::run()
{
    qDebug () << m_pocetni_uvjeti.size();
    for (int i = 0 ; i< m_pocetni_uvjeti.size(); i++)
    {
        m_solutions.emplace_back(std::to_string(i));
        qDebug () << i;
    }
    const double start_time = 0.;
    const double end_time = 2*pi;
    const double integration_step = pi/100;
    runge_kutta4 < state_type > stepper;
    for (size_t i= 0; i< m_pocetni_uvjeti.size(); i++ )
    {
        integrate_adaptive ( stepper , const_kruzno_gibanje ,
                             m_pocetni_uvjeti[i] ,
                             start_time , end_time , integration_step,
                             push_back_state_and_time ( m_solutions[i].x ,m_solutions[i].y, m_solutions[i].t ) );
    }
}

