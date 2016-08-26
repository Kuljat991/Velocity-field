#ifndef ThreadPoint_H
#define ThreadPoint_H
#include <QThreadPool>
#include <cmath>
#include <QVector>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/integrate/integrate_adaptive.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/odeint/integrate/integrate_const.hpp>
#include <boost/numeric/odeint/stepper/runge_kutta4.hpp>


using namespace boost::math::double_constants;
using std::vector;
using std::ostream;
typedef std::vector< double > state_type;
using namespace boost::numeric::odeint;

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

struct particle_solution
{
    particle_solution(const std::string& n): name(n) {}
    std::string name;
    vector<double> x;
    vector<double> y;
    vector<double> t;
};

class ThreadPoint : public QRunnable
{
public:
    ThreadPoint(const vector <state_type> &pocetni_uvjeti, vector <particle_solution> &solutions);
private:
    //! m_x - vektor x koordinata, m_y - vektor y koordinata
    vector <state_type> m_pocetni_uvjeti;
    void run();
    vector <particle_solution> & m_solutions;
public:

};

#endif // ThreadPoint_H
