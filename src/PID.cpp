#include "PID.h"
#include <limits>
#include <iostream>
#include <cfloat>
#include <math.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, int twiddle_mode)
{
  this->Kp = Kp;
  this->Ki = Ki;
  this->Kd = Kd;

  this->Dp = 1.0;
  this->Di = 1.0;
  this->Dd = 1.0;

  this->best_error = DBL_MAX;
  this->tol = 0.2;

  this->state = 0;
  this->iter = 0;
  this->error = 0;
  this->twiddle_mode = twiddle_mode;
}

void PID::UpdateError(double cte)
{
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;
}

double PID::TotalError()
{
  error += p_error * p_error;
  error /= ++iter;
  return -Kp * p_error - Kd * d_error - Ki * i_error;
}

void PID::Twiddle()
{
  if ((Dp + Di + Dd) > tol)
  {
    std::cout << "Twiddle=> error: " << error << std::endl;

    if (error < best_error)
    {
      state = 0;
      best_error = error;
      std::cout << "Twiddle=> best PID Co-effecients \tP:" << Kp << "\tI:" << Ki << "\tD:" << Kd << std::endl;

      Dp *= 1.1;
      Di *= 1.1;
      Dd *= 1.1;

      Kp += Dp;
      Ki += Di;
      Kd += Dd;
    }
    else
    {
      if (state == 0)
      {
        Kp -= 2 * Dp;
        Ki -= 2 * Di;
        Kd -= 2 * Dd;
        state = 1;
        std::cout << "Twiddle=> reducing PID Co-effecients \tP:" << Kp << "\tI:" << Ki << "\tD:" << Kd << std::endl;
      }
      else
      {
        Kp += Dp;
        Ki += Di;
        Kd += Dd;

        Dp *= 0.9;
        Di *= 0.9;
        Dd *= 0.9;

        std::cout << "Twiddle=> reducing Twiddle Co-effecients \tP:" << Dp << "\tI:" << Di << "\tD:" << Dd << std::endl;
        state = 0;
      }
    }

    if (fabs(p_error) > 3) {
      error = 0;
    }

    if (Kp < 0) {
      Kp = 0;
    }
    if (Ki < 0) {
      Ki = 0;
    }
    if (Kd < 0) {
      Kd = 0;
    }

    std::cout << "Twiddle=> trying with PID Co-effecients \tP:" << Kp << "\tI:" << Ki << "\tD:" << Kd << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
  }
}
