#ifndef UTILITY_H
#define UTILITY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <QDir>

using std::vector;
using std::ostream;
typedef std::vector< double > state_type;

void delete_folder_content (const std::string &dir_path)
{
    QDir dir( QString::fromStdString(dir_path));
    if (dir.exists())
    {
        dir.setNameFilters(QStringList() << "*.*");
        dir.setFilter(QDir::Files);
        foreach(QString dirFile, dir.entryList())
        {
            dir.remove(dirFile);
        }
    }
}

void create_folder (const std::string &dir_path)

{
    QDir mydir(QString::fromStdString(dir_path));
    mydir.mkpath(QString::fromStdString(dir_path));
}

//struct push_back_state_and_time
//{
//    vector< double >& m_states_x;
//    vector< double >& m_states_y;
//    vector< double >& m_times;

//    push_back_state_and_time ( vector< double > &states_x , vector< double > &states_y, vector< double > &times )
//        : m_states_x ( states_x ) ,m_states_y ( states_y ), m_times ( times ) { }

//    void operator() ( const state_type &x , double t )
//    {
//        m_states_x.push_back ( x[0] );
//        m_states_y.push_back ( x[1] );
//        m_times.push_back ( t );
//    }
//};

void draw ( std::ostream &os,const vector<double> &x, const vector<double> &y, const vector<double> &t )
{
    std::stringstream stream;

    for ( size_t i=0; i< t.size(); ++i )
    {
        stream << t[i]<<"\t"<<x[i]<<"\t"<<y[i]<<"\n";
    }

    os<<stream.str() <<"\n";
}

//struct particle_solution
//{
//    particle_solution(const std::string& n): name(n) {}
//    std::string name;
//    vector<double> x;
//    vector<double> y;
//    vector<double> t;
//};

#endif // UTILITY_H
