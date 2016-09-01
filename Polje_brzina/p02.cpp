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
    std::string dir_path = resultsPath + "/not_const_field";
    create_folder(dir_path);

    using namespace boost::numeric::odeint;

    //! broj threda
    int const n_thread = 4;
    //! broj tocka
    int const n_tocka = 500;
    //! puni threadovi
    int const puni_thredovi = n_tocka/n_thread;
    //! zadnji thread
    int  const ostatak = n_tocka%n_thread;
    double const x = 0.0;
    double const y_min = 1.0;
    double const y_max = 2.0;
    double const delta_y = (y_max - y_min)/n_tocka;
    //! vektor pocetnih uvjeta
    vector <state_type> sve_tocke (n_tocka);
    int i_tocke = -1;
    generate (sve_tocke.begin(), sve_tocke.end(), [&] () {i_tocke++;return state_type {x,y_min+i_tocke*delta_y};});
    vector <int> vektor_tocka_po_threadu (n_thread);
    for ( int i=0; i<n_thread; i++)
    {
        vektor_tocka_po_threadu[i] = puni_thredovi;
    }
    if( ostatak > 0)
    {
        for ( int i=0; i<ostatak; i++)
        {
            vektor_tocka_po_threadu[i] = vektor_tocka_po_threadu[i]+1;
        }
    }
    vector <vector <particle_solution>> *solutions = new vector <vector <particle_solution>> (n_thread);
    vector <vector <state_type>> *spremnik_tocka = new vector <vector <state_type>>(n_thread);
    int i = 0;
    int n = -1;
    for (const auto& v : *spremnik_tocka)
    {
        vector <state_type> trenutni_thread (vektor_tocka_po_threadu[i]);
        generate (trenutni_thread.begin(), trenutni_thread.end(), [&] () {++n ;return sve_tocke[n];});
        qDebug () << trenutni_thread[i][0] << ' ' << trenutni_thread[i][1];
        spremnik_tocka->at(i) = trenutni_thread;
        i++;
    }
    QThreadPool::globalInstance()->setMaxThreadCount(n_thread);

    for(int i=0; i<n_thread; i++)
    {
        ThreadPoint* ob = new ThreadPoint (spremnik_tocka->at(i), solutions->at(i),std::string("not_const_field"));
        QThreadPool::globalInstance()->start(ob);
    }
    QThreadPool::globalInstance()->waitForDone();
    int broj_tocke = 0;
    for (int i =0; i< solutions->size(); i++)
    {
        int j = 0;
        for ( auto& s : solutions->at(i))
        {
            std::ofstream fout( dir_path + "/" + std::to_string(broj_tocke) + ".txt");
            draw ( fout, solutions->at(i)[j].x,solutions->at(i)[j].y,solutions->at(i)[j].t);
            fout.close();
            ++j;
            ++broj_tocke;
        }
    }

delete spremnik_tocka;
delete solutions;

}

int main()
{

    //prvitest();
    std::cout<<"**************\n";
    drugitest();
    std::cout<<"**************\n";

    return 0;
}
