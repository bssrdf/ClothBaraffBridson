#ifndef BASIC_OPERATIONS_H
#define BASIC_OPERATIONS_H

#include "OpenGLContext.h"

#include <Eigen\Core>
#include <Eigen\Sparse>
#include <unsupported/Eigen/CXX11/Tensor>

#ifdef OPENMESH_BASED

#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

#endif

#include <CGAL\Simple_cartesian.h>

#include "SurfaceMeshObject.h"

#ifdef OPENMESH_BASED

inline void copy_v3f(Eigen::Vector3f & dest, const OpenMesh::Vec3f & src)
{
	dest(0) = src[0];
	dest(1) = src[1];
	dest(2) = src[2];
}

inline void copy_v3f(OpenMesh::Vec3f & dest, const Eigen::Vector3f & src)
{
	dest[0] = src(0);
	dest[1] = src(1);
	dest[2] = src(2);
}

void shiftVertices(PolyArrayMesh::VertexHandle& vhd0, PolyArrayMesh::VertexHandle& vhd1, PolyArrayMesh::VertexHandle& vhd2);


#endif

#ifdef CGAL_BASED

inline Eigen::Vector3f & displacement(Point3f const & dest, Point3f const & src)
{
	return Eigen::Vector3f(
		dest.x() - src.x(),
		dest.y() - src.y(),
		dest.z() - src.z());
}

inline Point3f const & interpolate(Point3f const & a, Point3f const & b, float t)
{
	return Point3f(
		a.x() * t + b.x() * (1.0f - t),
		a.y() * t + b.y() * (1.0f - t),
		a.z() * t + b.z() * (1.0f - t));
}

inline void copy_v3f(Eigen::Vector3f & dest, const Vec3f & src)
{
	dest(0) = src.x();
	dest(1) = src.y();
	dest(2) = src.z();
}

// TODO to be tested
inline void copy_v3f(Vec3f & dest, const Eigen::Vector3f & src)
{
	dest = Vec3f(src(0), src(1), src(2));
}

inline void copy_v3f(Eigen::Vector3f & dest, const Point3f & src)
{
	dest(0) = src.x();
	dest(1) = src.y();
	dest(2) = src.z();
}

// TODO to be tested
inline void copy_v3f(Point3f & dest, const Eigen::Vector3f & src)
{
	dest = Point3f(src(0), src(1), src(2));
}

void shiftVertices(Veridx & vhd0, Veridx & vhd1, Veridx & vhd2);

#endif

void convert_diag2sparse_mnf(Eigen::SparseMatrix<float> & dest, const Eigen::Diagonal<const Eigen::SparseMatrix<float>> & src);

void addBlock33(Eigen::SparseMatrix<float> & augend, GLuint block_i, GLuint block_j, const Eigen::Matrix3f & addend);

void setBlock33(Eigen::SparseMatrix<float> & augend, GLuint block_i, GLuint block_j, const Eigen::Matrix3f & addend);

//Eigen::Vector3f get_vector(Eigen::Tensor<float, 3> & tensor, GLuint block_i, GLuint block_j);

void get_diag_mnf(Eigen::SparseMatrix<float> & dest, size_t size);

//inline float max(float a, float b)
//{
//	return (a > b) ? a : b;
//}
//
//inline float min(float a, float b)
//{
//	return (a < b) ? a : b;
//}

GLboolean checkIdentical(const Eigen::Matrix3f mat1, const Eigen::Matrix3f mat2, float tolerance = 1e-20f);

GLboolean checkSymmetrical(const Eigen::Matrix3f mat, const float tolerance = 1e-20f);

GLboolean checkSymmetrical(const Eigen::SparseMatrix<float> mat, float tolerance = 1e-20f);

/* S(v) = [ 0  -vx  vy
			vz  0  -vx
			-vy  vx  0]
*/
inline Eigen::Matrix3f get_S_m3f(Eigen::Vector3f & v)
{
	Eigen::Matrix3f S;
	S << 0.0f, -v[2], v[1],
		v[2], 0.0f, -v[0],
		-v[1], v[0], 0.0f;
	return S;
}

Eigen::Vector3f get_vector3f_block(Eigen::Tensor<float, 3> & tensor, unsigned int block_i, unsigned int block_j);

inline bool Equals(const float v0, const float v1, const float epsilon)
{
	return (std::abs(v0 - v1) < epsilon);
}

inline bool EqualsZero(const float v, const float epsilon = 1e-10f)
{
	return Equals(v, 0.f, epsilon);
}

#endif

