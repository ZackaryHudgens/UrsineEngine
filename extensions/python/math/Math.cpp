#include <boost/python.hpp>

#include "Matrix.hpp"

using namespace boost::python;

using math::Matrix;

BOOST_PYTHON_MODULE(math)
{
  class_<Matrix>("Matrix", init<int, int>());
}
