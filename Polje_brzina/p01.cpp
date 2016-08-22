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

    vector< state_type > pocetni_uvjeti;
    pocetni_uvjeti.push_back({1.0, 0.0});
    pocetni_uvjeti.push_back({1.5, 0.0});
    pocetni_uvjeti.push_back({2.0, 0.0});

    ThreadPoint *threadpoint = new ThreadPoint(pocetni_uvjeti);
    QThreadPool::globalInstance()->start(threadpoint);

    int i =0;
    for(const auto& s : threadpoint->solutions)
    {
        std::ofstream fout( dir_path + "/" + std::to_string(i) + ".txt");
        draw ( fout, threadpoint->solutions[i].x,threadpoint->solutions[i].y,threadpoint->solutions[i].t);
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
