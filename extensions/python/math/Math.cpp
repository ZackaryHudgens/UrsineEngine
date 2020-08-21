#include <boost/python.hpp>

#include "Matrix.hpp"
#include "Vector2D.hpp"
#include "Vector3D.hpp"

using namespace boost::python;

using math::Matrix;
using math::Vector2D;
using math::Vector3D;

BOOST_PYTHON_MODULE(math)
{
  class_<Matrix>("Matrix", init<int, int>())
    .def(self + other<Matrix>())
    .def(self - other<Matrix>())
    .def(self * double())
    .def(self * other<Matrix>())
    .def(self += other<Matrix>())
    .def(self -= other<Matrix>())
    .def(self *= double())
    .def(self *= other<Matrix>())
    .def("set_identity", &Matrix::SetIdentity)
    .def("set_value", &Matrix::SetValue)
    .def("get_value", &Matrix::GetValue);

  class_<Vector2D>("Vector2D", init<int, int>())
    .def(self + other<Vector2D>())
    .def(self - other<Vector2D>())
    .def(self += other<Vector2D>())
    .def(self -= other<Vector2D>())
    .def("magnitude", &Vector2D::Magnitude)
    .def("normalize", &Vector2D::Normalize)
    .def("angle_with", &Vector2D::AngleWith)
    .def("is_orthogonal_to", &Vector2D::IsOrthogonalTo)
    .def("is_parallel_to", &Vector2D::IsParallelTo);

  class_<Vector3D>("Vector3D", init<int, int, int>())
    .def(self + other<Vector3D>())
    .def(self - other<Vector3D>())
    .def(self += other<Vector3D>())
    .def(self -= other<Vector3D>())
    .def("magnitude", &Vector3D::Magnitude)
    .def("normalize", &Vector3D::Normalize)
    .def("angle_with", &Vector3D::AngleWith)
    .def("is_orthogonal_to", &Vector3D::IsOrthogonalTo)
    .def("is_parallel_to", &Vector3D::IsParallelTo)
    .def("cross_product", &Vector3D::CrossProduct);
}
