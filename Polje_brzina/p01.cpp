#include <QDebug>
#include "pathconfig.h"
#include "velocity_functions.h"
#include "ThreadPoint.h"
#include "utility.h"

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

    delete_folder_content(dir_path);
    create_folder(dir_path);

    using namespace boost::numeric::odeint;

    //! broj threda
    int const n_thread = 4;
    //! broj tocka
    int const n_tocka = 9;
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
        spremnik_tocka->at(i) = trenutni_thread;
        i++;
    }
    QThreadPool::globalInstance()->setMaxThreadCount(n_thread);
    int svasta = 0;
    for(int i=0; i<n_thread; i++)
    {
        ThreadPoint* ob = new ThreadPoint (spremnik_tocka->at(i), solutions->at(i),svasta);
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
