#pragma once

#include "ZeroVec.h"

class ZeroMat {
private:
	struct Matrix {
		float _11, _12, _13;
		float _21, _22, _23;
		float _31, _32, _33;
		Matrix() {
			_11 = 0.0;
			_12 = 0.0;
			_13 = 0.0;
			_21 = 0.0;
			_22 = 0.0;
			_23 = 0.0;
			_31 = 0.0;
			_32 = 0.0;
			_33 = 0.0;
		}
	};

	Matrix matrix;
	// 행렬끼리 곱
	inline void MatrixMultiply(Matrix& _matrix);

public:
	ZeroMat() {
		// 행렬을 초기화한다.
		Identity();
	}

	// 행렬을 초기화한다.
	void Identity();

	// 이동 행렬 생성
	void Translate(float _x, float _y);

	// 크기 행렬 생성
	void Scale(float _xScale, float _yScale);

	// 회전 행렬 생성
	void Rotate(float _rotation);

	// heading으로부터 side각도로 회전 행렬 생성
	void Rotate(const ZeroVec& _fwd, const ZeroVec& _side);

	// 주어진 ZeroVec들을 해당 행렬로 변환시킨다.
	void TransformZeroVec(std::vector<ZeroVec>& _vPoint);

	// 주어진 ZeroVec을 해당 행렬로 변환시킨다.
	void TransformZeroVec(ZeroVec& _vPoint);

	// 행렬 요소에 수치를 적용한다.
	void _11(float val) {
		matrix._11 = val;
	}
	void _12(float val) {
		matrix._12 = val;
	}
	void _13(float val) {
		matrix._13 = val;
	}

	void _21(float val) {
		matrix._21 = val;
	}
	void _22(float val) {
		matrix._22 = val;
	}
	void _23(float val) {
		matrix._23 = val;
	}

	void _31(float val) {
		matrix._31 = val;
	}
	void _32(float val) {
		matrix._32 = val;
	}
	void _33(float val) {
		matrix._33 = val;
	}
};

// Transforms a point from the agent's local space into world space
inline ZeroVec PointToWorldSpace(const ZeroVec& point,
                                 const ZeroVec& AgentHeading,
                                 const ZeroVec& AgentSide,
                                 const ZeroVec& AgentPosition) {
	// Point의 복사 벡터를 만든다.
	ZeroVec TransPoint = point;

	// 행렬 생성
	ZeroMat matTransform;

	// 회전
	matTransform.Rotate(AgentHeading, AgentSide);

	// 이동
	matTransform.Translate(AgentPosition.x, AgentPosition.y);

	// 적용
	matTransform.TransformZeroVec(TransPoint);

	return TransPoint;
}
