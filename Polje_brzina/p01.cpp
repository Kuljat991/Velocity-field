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
    create_folder(dir_path);

    using namespace boost::numeric::odeint;

    vector <particle_solution> solutions_1;
    vector <particle_solution> solutions_2;

    vector< state_type > pocetni_uvjeti;
    pocetni_uvjeti.push_back({1.0, 0.0});
    pocetni_uvjeti.push_back({1.5, 0.0});
    pocetni_uvjeti.push_back({2.0, 0.0});

    //! broj threda
    int n_thread = 3;
    //! broj tocka
    int n_tocka = 15;
    //! puni threadovi
    int tocke_po_threadu = n_tocka/n_thread;
    //! zadnji thread
    int ostatak = n_tocka%n_thread;
//    cout << tocke_po_threadu << endl << ostatak << endl;
    //!raspon tocka. Tocke su pozicionirane po y-osi i razmaknute su za delta_y
    double x = 0.0;
    double y_min = 1.0;
    double y_max = 2.0;
    double delta_y = (y_max - y_min)/n_tocka;
    vector <vector <state_type>> *spremnik_tocka = new vector <vector <state_type>>(n_thread);
    if (ostatak == 0)
    {
        int i = 0;
        int n = -1;
        for (const auto& v : *spremnik_tocka)
        {
            vector <state_type> puni_thredovi (tocke_po_threadu);
            generate (puni_thredovi.begin(), puni_thredovi.end(), [&] () {++n ;return state_type {x,y_min+n*delta_y};});
//            cout << nesto[i][0] << ' ' << nesto[i][1] << endl;
            spremnik_tocka->at(i) = puni_thredovi;
            i++;
        }
    }
    else
    {
        int i = 0;
        int n = -1;
        for (const auto& v : *spremnik_tocka)
        {
            vector <state_type> Puni_threadovi (tocke_po_threadu);
            generate (Puni_threadovi.begin(), Puni_threadovi.end(), [&] () {++n ;return state_type {x,y_min+n*delta_y};});
            spremnik_tocka->at(i) = Puni_threadovi;
            i++;
        }
        vector <state_type> zadnji_thread (ostatak);
        generate (zadnji_thread.begin(), zadnji_thread.end(), [&] () {++n ;return state_type {x,y_min+n*delta_y};});
        spremnik_tocka->resize(spremnik_tocka->size()+1);
        spremnik_tocka->at(spremnik_tocka->size()-1) = zadnji_thread;
    }
//    std::cout << spremnik_tocka->at(0)[0] [1] << ' ' << spremnik_tocka->at(0)[1] [1] << ' ' << spremnik_tocka->at(0)[3][1] << endl ;

    QThreadPool::globalInstance()->setMaxThreadCount(n_thread);

    ThreadPoint *threadpoint_1 = new ThreadPoint(spremnik_tocka->at(0), solutions_1);
    QThreadPool::globalInstance()->start(threadpoint_1);

    ThreadPoint *threadpoint_2 = new ThreadPoint(spremnik_tocka->at(1), solutions_2);
    QThreadPool::globalInstance()->start(threadpoint_2);

    QThreadPool::globalInstance()->waitForDone();
    int i =0;
    for(const auto& s : solutions_1)
    {
        std::ofstream fout( dir_path + "/" + std::to_string(i) + ".txt");
        draw ( fout, solutions_1[i].x,solutions_1[i].y,solutions_1[i].t);
        fout.close();
        ++i;
    }
    int j =0;
    for(const auto& s : solutions_2)
    {
        std::ofstream fout( dir_path + "/" + std::to_string(j+solutions_1.size()) + ".txt");
        draw ( fout, solutions_2[j].x,solutions_2[j].y,solutions_2[j].t);
        fout.close();
        ++j;
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
