#include <boost/python.hpp>

#include "wrappers/PyVectorWrapper.hpp"

namespace bp = boost::python;

using py::VectorWrapper;

BOOST_PYTHON_MODULE(math)
{
  // Expose the VectorWrapper class.
  bp::class_<VectorWrapper>("Vector")
    .def(bp::init<double, double, double>())
    .def(bp::self + bp::self)
    .def(bp::self - bp::self)
    .def("normalize", &VectorWrapper::Normalize)
    .def("cross_product", &VectorWrapper::CrossProduct)
    .def("angle_with", &VectorWrapper::AngleWith)
    .def("x", &VectorWrapper::x)
    .def("y", &VectorWrapper::y)
    .def("z", &VectorWrapper::z);
}
