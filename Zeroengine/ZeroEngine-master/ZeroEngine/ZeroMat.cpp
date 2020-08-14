#include "stdafx.h"
#include "ZeroMat.h"

// 행렬끼리 곱
void ZeroMat::MatrixMultiply(Matrix& _matrix) {
	ZeroMat::Matrix mat_temp;

	// 첫째 줄
	mat_temp._11 =
	    (matrix._11 * _matrix._11) + (matrix._12 * _matrix._21) + (matrix._13 * _matrix._31);
	mat_temp._12 =
	    (matrix._11 * _matrix._12) + (matrix._12 * _matrix._22) + (matrix._13 * _matrix._32);
	mat_temp._13 =
	    (matrix._11 * _matrix._13) + (matrix._12 * _matrix._23) + (matrix._13 * _matrix._33);

	// 둘째 줄
	mat_temp._21 =
	    (matrix._21 * _matrix._11) + (matrix._22 * _matrix._21) + (matrix._23 * _matrix._31);
	mat_temp._22 =
	    (matrix._21 * _matrix._12) + (matrix._22 * _matrix._22) + (matrix._23 * _matrix._32);
	mat_temp._23 =
	    (matrix._21 * _matrix._13) + (matrix._22 * _matrix._23) + (matrix._23 * _matrix._33);

	// 셋째 줄
	mat_temp._31 =
	    (matrix._31 * _matrix._11) + (matrix._32 * _matrix._21) + (matrix._33 * _matrix._31);
	mat_temp._32 =
	    (matrix._31 * _matrix._12) + (matrix._32 * _matrix._22) + (matrix._33 * _matrix._32);
	mat_temp._33 =
	    (matrix._31 * _matrix._13) + (matrix._32 * _matrix._23) + (matrix._33 * _matrix._33);

	matrix = mat_temp;
}

// 주어진 ZeroVec들을 해당 행렬로 변환시킨다.
void ZeroMat::TransformZeroVec(std::vector<ZeroVec>& _vPoint) {
	for (unsigned int i = 0; i < _vPoint.size(); ++i) {
		float tempX = (matrix._11 * _vPoint[i].x) + (matrix._21 * _vPoint[i].y) + (matrix._31);
		float tempY = (matrix._12 * _vPoint[i].x) + (matrix._22 * _vPoint[i].y) + (matrix._32);
		_vPoint[i].x = tempX;
		_vPoint[i].y = tempY;
	}
}

// 주어진 ZeroVec을 해당 행렬로 변환시킨다.
void ZeroMat::TransformZeroVec(ZeroVec& _vPoint) {
	float tempX = (matrix._11 * _vPoint.x) + (matrix._21 * _vPoint.y) + (matrix._31);
	float tempY = (matrix._12 * _vPoint.x) + (matrix._22 * _vPoint.y) + (matrix._32);
	_vPoint.x = tempX;
	_vPoint.y = tempY;
}

// 행렬을 초기화한다.
void ZeroMat::Identity() {
	matrix._11 = 1;
	matrix._12 = 0;
	matrix._13 = 0;
	matrix._21 = 0;
	matrix._22 = 1;
	matrix._23 = 0;
	matrix._31 = 0;
	matrix._32 = 0;
	matrix._33 = 1;
}

// 이동 행렬 생성
void ZeroMat::Translate(float _x, float _y) {
	Matrix mat;
	mat._11 = 1;
	mat._12 = 0;
	mat._13 = 0;
	mat._21 = 0;
	mat._22 = 1;
	mat._23 = 0;
	mat._31 = _x;
	mat._32 = _y;
	mat._33 = 1;

	// 행렬을 곱한다.
	MatrixMultiply(mat);
}

// 크기 행렬 생성
void ZeroMat::Scale(float _xScale, float _yScale) {
	ZeroMat::Matrix mat;

	mat._11 = _xScale;
	mat._12 = 0;
	mat._13 = 0;
	mat._21 = 0;
	mat._22 = _yScale;
	mat._23 = 0;
	mat._31 = 0;
	mat._32 = 0;
	mat._33 = 1;

	// 행렬을 곱한다.
	MatrixMultiply(mat);
}

// 회전 행렬 생성
void ZeroMat::Rotate(float _rotation) {
	ZeroMat::Matrix mat;

	float sin = ZeroMathMgr->Sin(_rotation);
	float cos = ZeroMathMgr->Cos(_rotation);

	mat._11 = cos;
	mat._12 = sin;
	mat._13 = 0;
	mat._21 = -sin;
	mat._22 = cos;
	mat._23 = 0;
	mat._31 = 0;
	mat._32 = 0;
	mat._33 = 1;

	// 행렬을 곱한다.
	MatrixMultiply(mat);
}

// heading으로부터 side각도로 회전 행렬 생성
void ZeroMat::Rotate(const ZeroVec& _fwd, const ZeroVec& _side) {
	ZeroMat::Matrix mat;

	mat._11 = _fwd.x;
	mat._12 = _fwd.y;
	mat._13 = 0;
	mat._21 = _side.x;
	mat._22 = _side.y;
	mat._23 = 0;
	mat._31 = 0;
	mat._32 = 0;
	mat._33 = 1;

	// 행렬을 곱한다.
	MatrixMultiply(mat);
}
