#ifndef VELOCITY_FUNCTIONS_H
#define VELOCITY_FUNCTIONS_H
#include <vector>
typedef std::vector< double > state_type;

/**
 * Testna f-ja 1
 * dx/dt = 1
 * dy/dt = cos(t)
 * Ocekujemo:
 * x = t + x0
 * y = sin(t) + y0
 */
void sinusoida ( const state_type  &/*state*/,  state_type &dxdt , const double t );



/**
 * Testna f-ja 1
 * Stacionarno vektorsko polje brzina - ne mijenja se u vremenu
 * \nabla \times \mathbf{v} = 0
 * gdje je \mathbf{v} = \left( -\frac{y}{x^2+y^2}, \frac{x}{x^2+y^2} \right)
 *
 * Za render copy/paste ovdje: http://arachnoid.com/latex/
 *
 * Rješenje: svugdje vektori jednake duljine (1) i kružno gibanje oko (0,0)
 */
void const_kruzno_gibanje ( const state_type  &state,  state_type &dxdt , const double /*t*/ );

/**
 * Testna f-ja 1
 * Stacionarno vektorsko polje brzina - ne mijenja se u vremenu
 * \nabla \times \mathbf{v} = 0
 * gdje je \mathbf{v} = \left( -\frac{y}{x^2+y^2}, \frac{x}{x^2+y^2} \right)
 *
 * Za render copy/paste ovdje: http://arachnoid.com/latex/
 *
 * Rješenje: svugdje vektori jednake duljine (1) i kružno gibanje oko (0,0)
 */
void kruzno_gibanje ( const state_type  &state,  state_type &dxdt , const double t );

#endif //VELOCITY_FUNCTIONS_H
