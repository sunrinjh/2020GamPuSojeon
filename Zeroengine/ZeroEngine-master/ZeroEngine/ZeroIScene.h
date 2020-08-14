#pragma once

#include "ZeroRect.h"
#include "ZeroVec.h"

using namespace std;

class ZeroIScene {
protected:
	typedef vector<ZeroIScene*> NODE;
	NODE m_Node;

protected:
	// m_Mat은 위치, 회전각도, 크기등의 변수를 계산하여 위치변환한 행렬이다.
	// 직접적으로 만지는 일은 권하지 않는다.
	D3DXMATRIX m_Mat;

	// 객체의 위치를 나타내는 값이다.
	ZeroVec m_vPos;

	// 객체의 절대 위치를 나타내는 값이다.
	ZeroVec m_vGlobalPos;
	
	// 객체가 카메라 위치에 계산하여 보정되는 위치값이다.
	// 카메라 기능이 꺼져있다면 m_vPos값과 같다.
	ZeroVec m_vWorldPos;

	// 객체의 크기 비율을 나타내는 값이다.
	ZeroVec m_vScale;

	// 객체의 크기 중심을 나타내는 값이다.
	ZeroVec m_vScalingCenter;

	// 객체의 각도 회전 중심을 나타내는 값이다.
	ZeroVec m_vRotCenter;

	// 객체의 회전 각도를 나타내는 값이다.
	float m_fRot;

	// 객체의 색깔을 나타내는 값이다.
	// 기본값 : 0xffffffff
	// 변환되기 전 컬러
	DWORD m_ColorTemp;

	// 객체의 색깔을 나타내는 값이다.
	// 기본값 : 0xffffffff
	// 변환된 컬러
	DWORD m_Color;

	// 객체의 테두리의 값을 나타내는 값이다.
	// 왠만해선 건들지 않는게 좋다.
	// 기본값 : { 0, 0, m_fWidth, m_fHeight }
	ZeroRect m_Rect;

	// 객체의 가로 픽셀값을 나타내는 값이다.
	// 보통 이미지의 가로값을 나타낸다.
	float m_fWidth;

	// 객체의 스케일링된 가로 픽셀값을 나타내는 값이다.
	// Width * Scale.x 의 값을 반환하며, 직접 수정하지 않는 것이 좋다.
	float m_fScaledWidth;

	// 객체의 세로 픽셀값을 나타내는 값이다.
	// 보통 이미지의 세로값을 나타낸다.
	float m_fHeight;

	// 객체의 스케일링된 세로 픽셀값을 나타내는 값이다.
	// Height * Scale.y 의 값을 반환하며, 직접 수정하지 않는 것이 좋다.
	float m_fScaledHeight;

	// 객체를 지울것인지 진위여부를 나타내는 값이다.
	// 만일 true이면 이 객체는 다음 Update()함수가 불려질때 지워질 것이다.
	bool m_bErase;

	// 본 객체가 카메라 기능에 응할 것인지 진위여부를 나타내는 값이다.
	// 반드시 CameraMgr->CameraOn()이 불려져 있어야 작동한다.
	bool m_bCamera;

	// 본 객체의 Update함수를 자동으로 돌릴것인지 여부를 나타낸다.
	bool m_bUpdate;

	// 본 객체를 갖고있는 객체의 주소를 가지고 있다.
	ZeroIScene* m_pParent;

	// 윈도우 핸들을 나타내는 값이다.
	HWND m_hWnd;

	// 본 객체의 이름(string)입니다.
	string m_sName;

private:
	// 객체가 생성되고 현재까지 지난 시간초를 나타낸다.
	float m_fStartToCurrentTime;

public:
	// 기본 생성자이다.
	ZeroIScene();
	virtual ~ZeroIScene();

	// 렌더링할 기초작업을 한다.
	// 위치, 회전각도, 크기 변수를 이용하여 m_Mat의 값을 계산해내는 작업을 수행한다.
	virtual void Render();

	// 카메라 위치를 고려하여 m_vWorldPos값을 계산하고
	// 본 객체가 가지고있는 하위객체들의 Update()함수를 실행한다.
	// 그리고 m_bErase가 활성화되어있는 하위객체들 역시 제거한다.
	void virtual Update(float _eTime);

	// 카메라 위치를 고려하여 m_vWorldPos값을 계산한다.
	void UpdateWorldPos();

	// 본 객체에 하위객체를 등록한다.
	void PushScene(ZeroIScene* _scene, bool update = true);

	// 본 객체에 등록되어있는 하위객체를 빼낸다.
	// isErase가 참이면 메모리 제거까지 수행한다.
	// 만일 본 객체에 p가 존재하지 않는다면 아무 작업도 수행하지 않는다.
	void PopScene(ZeroIScene* _scene, bool isErase = true);

	// 본 객체의 하위객체중 p가 존재하는지 확인한다.
	// 만일 존재한다면 true를 반환한다.
	bool IsExistScene(ZeroIScene* _scene);

	// 본 객체가 p와 겹치는지 충돌검사를 수행한다.
	// 만일 겹친다면 true를 반환한다.
	bool IsOverlapped(ZeroIScene* _scene);

	// pos가 본 객체 안에 있는지 충돌검사를 수행한다.
	// 만일 안에 있다면 true를 반환한다.
	bool IsOverlapped(ZeroVec pos);

	//대상 ZeroIScene과 OBB 충돌체크를 진행한다.
	//직접 사용하기보단 IsOverlapped를 사용하기를 추천한다.
	//참고 : http://blog.naver.com/aasr4r4/130185736751
	bool CheckOBBCollision(ZeroIScene* _scene);

private:
	bool IsPosInRect(ZeroRect rect, ZeroVec pos);

	void UpdateScaledWH()
	{	
		m_fScaledWidth = m_fWidth * m_vScale.x;
		m_fScaledHeight = m_fHeight * m_vScale.y;
	}

	void UpdateTransform();

public:
	// 객체의 위치값을 반환한다.
	ZeroVec& Pos() {
		return m_vPos;
	}
	ZeroVec Pos() const {
		return m_vPos;
	}
	// 객체의 pivot에 따른 위치값을 반환한다.
	// 예) Pos(0.5f, 0.5f)는 객체의 중심위치값을 반환한다.
	ZeroVec Pos(float pivotX, float pivotY) const {
		return m_vPos + ZeroVec(m_fScaledWidth * pivotX, 
								m_fScaledHeight * pivotY);
	}

	// 객체의 위치값을 pos값으로 고정시킨다.
	void SetPos(ZeroVec pos) {
		m_vPos = pos;
		UpdateTransform();
	}
	// 객체의 위치값을 pos값으로 고정시킨다.
	template <typename T, typename U>
	void SetPos(T x, U y) {
		m_vPos.x = static_cast<float>(x);
		m_vPos.y = static_cast<float>(y);
		UpdateTransform();
	}
	// 객체의 위치값을 x값으로 고정시킨다.
	template <typename T>
	void SetPosX(T pos) {
		m_vPos.x = static_cast<float>(pos);
		UpdateTransform();
	}
	// 객체의 위치값을 y값으로 고정시킨다.
	template <typename T>
	void SetPosY(T pos) {
		m_vPos.y = static_cast<float>(pos);
		UpdateTransform();
	}

	// 객체의 위치값에 x, y만큼 각각 더한다.
	// x, y값에 음수값을 넣으면 뺄수도있다.
	template <typename T, typename U>
	void AddPos(T x, U y) {
		m_vPos.x += static_cast<float>(x);
		m_vPos.y += static_cast<float>(y);
		UpdateTransform();
	}

	// 객체의 위치값중 x값에 x만큼 더한다.
	template <typename T>
	void AddPosX(T x) {
		m_vPos.x += static_cast<float>(x);
		UpdateTransform();
	}

	// 객체의 위치값중 y값에 y만큼 더한다.
	template <typename T>
	void AddPosY(T y) {
		m_vPos.y += static_cast<float>(y);
		UpdateTransform();
	}

	// 객체의 절대 위치값을 반환한다.
	ZeroVec GlobalPos() {
		return m_vGlobalPos;
	}

	// 객체의 월드위치값을 반환한다.
	ZeroVec WorldPos() const {
		return m_vWorldPos;
	}

	// 객체의 월드위치값을 worldpos값으로 고정시킨다.
	// 왠만해선 사용하지말자.
	void SetWorldPos(ZeroVec worldpos) {
		m_vWorldPos = worldpos;
	}

	template <typename T, typename U>
	// 객체의 월드위치값을 x,y값으로 고정시킨다.
	// 왠만해선 사용하지말자.
	void SetWorldPos(T x, U y) {
		m_vWorldPos.x = static_cast<float>(x);
		m_vWorldPos.y = static_cast<float>(y);
	}

	template <typename T, typename U>
	// 객체의 월드위치값에 x,y만큼 각각 더한다.
	// x,y값에 음수값을 넣으면 뺄수도있다.
	// 왠만해선 사용하지말자.
	void AddWorldPos(T x, U y) {
		m_vWorldPos.x += static_cast<float>(x);
		m_vWorldPos.y += static_cast<float>(y);
	}

	template <typename T>
	// 객체의 월드위치값중 x값에 x만큼 더한다.
	// 왠만해선 사용하지말자.
	void AddWorldPosX(T x) {
		m_vWorldPos.x += static_cast<float>(x);
	}

	template <typename T>
	// 객체의 월드위치값중 y값에 y만큼 더한다.
	// 왠만해선 사용하지말자.
	void AddWorldPosY(T y) {
		m_vWorldPos.y += static_cast<float>(y);
	}

	// 객체의 스케일값을 반환한다.
	ZeroVec Scale() const {
		return m_vScale;
	}

	// 객체의 스케일값을 scale값으로 고정시킨다.
	void SetScale(ZeroVec scale) {
		m_vScale = scale;
		UpdateScaledWH();
	}

	template <typename T, typename U>
	// 객체의 스케일값을 x,y값으로 고정시킨다.
	void SetScale(T x, U y) {
		m_vScale.x = static_cast<float>(x);
		m_vScale.y = static_cast<float>(y);
		UpdateScaledWH();
	}

	template <typename T>
	// 객체의 스케일값을 scale값으로 고정시킨다.
	void SetScale(T scale) {
		m_vScale.x = static_cast<float>(scale);
		m_vScale.y = static_cast<float>(scale);
		UpdateScaledWH();
	}

	template <typename T, typename U>
	// 객체의 스케일값에 x,y만큼 각각 더한다.
	void AddScale(T x, U y) {
		m_vScale.x += static_cast<float>(x);
		m_vScale.y += static_cast<float>(y);
		UpdateScaledWH();
	}

	template <typename T>
	// 객체의 스케일값에 scale만큼 각각 더한다.
	void AddScale(T scale) {
		m_vScale.x += static_cast<float>(scale);
		m_vScale.y += static_cast<float>(scale);
		UpdateScaledWH();
	}

	template <typename T>
	// 객체의 스케일값중 x값에 x만큼 더한다.
	void AddScaleX(T x) {
		m_vScale.x += static_cast<float>(x);
		m_fScaledWidth = m_fWidth * m_vScale.x;
	}

	template <typename T>
	// 객체의 스케일값중 y값에 y만큼 더한다.
	void AddScaleY(T y) {
		m_vScale.y += static_cast<float>(y);
		m_fScaledHeight = m_fHeight * m_vScale.y;
	}

	// 객체의 스케일중심값을 반환한다.
	ZeroVec ScalingCenter() const {
		return m_vScalingCenter;
	}

	// 객체의 스케일중심값을 scalingcenter값으로 고정시킨다.
	void SetScalingCenter(ZeroVec scalingcenter) {
		m_vScalingCenter = scalingcenter;
	}

	template <typename T, typename U>
	// 객체의 스케일중심값을 x,y값으로 고정시킨다.
	void SetScalingCenter(T x, U y) {
		m_vScalingCenter.x = static_cast<float>(x);
		m_vScalingCenter.y = static_cast<float>(y);
	}

	template <typename T, typename U>
	// 객체의 스케일중심값에 x,y만큼 각각 더한다.
	void AddScalingCenter(T x, U y) {
		m_vScalingCenter.x += static_cast<float>(x);
		m_vScalingCenter.y += static_cast<float>(y);
	}

	template <typename T>
	// 객체의 스케일중심값중 x값에 x만큼 더한다.
	void AddScalingCenterX(T x) {
		m_vScalingCenter.x += static_cast<float>(x);
	}

	template <typename T>
	// 객체의 스케일중심값중 y값에 y만큼 더한다.
	void AddScalingCenterY(T y) {
		m_vScalingCenter.y += static_cast<float>(y);
	}

	// 객체의 회전각도중심값을 반환한다.
	ZeroVec RotCenter() const {
		return m_vRotCenter;
	}

	// 객체의 회전각도중심값을 rotcenter값으로 고정시킨다.
	void SetRotCenter(ZeroVec rotcenter) {
		m_vRotCenter = rotcenter;
	}

	template <typename T, typename U>
	// 객체의 회전각도중심값을 x,y값으로 고정시킨다.
	void SetRotCenter(T x, U y) {
		m_vRotCenter.x = static_cast<float>(x);
		m_vRotCenter.y = static_cast<float>(y);
	}

	template <typename T, typename U>
	// 객체의 회전각도중심값에 x,y만큼 각각 더한다.
	void AddRotCenter(T x, U y) {
		m_vRotCenter.x += static_cast<float>(x);
		m_vRotCenter.y += static_cast<float>(y);
	}

	template <typename T>
	// 객체의 회전각도중심값중 x값에 x만큼 더한다.
	void AddRotCenterX(T x) {
		m_vRotCenter.x += static_cast<float>(x);
	}

	template <typename T>
	// 객체의 회전각도중심값중 y값에 y만큼 더한다.
	void AddRotCenterY(T y) {
		m_vRotCenter.y += static_cast<float>(y);
	}

	// 객체의 회전각도값을 반환한다.
	float Rot() const {
		return m_fRot;
	}

	// 객체의 절대 회전각도값을 반환한다.
	float GlobalRot() const;

	template <typename T>
	// 객체의 회전각도값을 rot값으로 고정시킨다.
	void SetRot(T rot) {
		m_fRot = static_cast<float>(rot);
	}

	template <typename T>
	// 객체의 회전각도값을 rot만큼 더한다.
	void AddRot(T rot) {
		m_fRot += static_cast<float>(rot);
	}

	// 객체의 컬러값을 정수형태로 반환한다.
	DWORD Color() const {
		return m_Color;
	}
	// 객체의 컬러값을 color값으로 고정시킨다.
	void SetColor(DWORD color) {
		m_ColorTemp = color;
	}

	// Alpha 색을 바꾼다.
	void SetColorA(int color);
	// Red 색을 바꾼다.
	void SetColorR(int color);
	// Green 색을 바꾼다.
	void SetColorG(int color);
	// Blue 색을 바꾼다.
	void SetColorB(int color);

	// 객체가 지워질 것인지에 대한 진위여부를 반환한다.
	bool IsErase() const {
		return m_bErase;
	}

	// 객체를 제거 진위여부를 설정한다.
	// SetErase(true)를 하면 본 객체와 하위객체들은 제거된다.
	void SetErase(bool erase) {
		m_bErase = erase;
	}

	// 본 객체의 카메라 기능이 켜져있는지 확인한다.
	bool IsCamera() const {
		return m_bCamera;
	}

	// 본 객체의 카메라 기능을 킬것인지 끌것인지 설정한다.
	void SetCamera(bool camera) {
		m_bCamera = camera;
	}

	// 본 객체의 테두리값을 반환한다.
	ZeroRect Rect() const {
		return m_Rect;
	}

	// 본 객체의 테두리 값을 설정한다.
	void SetRect(ZeroRect rect) {
		m_Rect = rect;
	}

	template <typename T, typename U, typename V, typename W>
	// 본 객체의 테두리값을 left, top, right, bottom 순으로 설정한다.
	void SetRect(T left, U top, V right, W bottom) {
		m_Rect.left = static_cast<LONG>(left);
		m_Rect.top = static_cast<LONG>(top);
		m_Rect.right = static_cast<LONG>(right);
		m_Rect.bottom = static_cast<LONG>(bottom);
	}

	// 본 객체의 가로 픽셀 길이를 반환한다.
	float Width() const {
		return m_fWidth;
	}

	// 본 객체의 스케일링된 가로 픽셀 길이를 반환한다.
	float ScaledWidth() const {
		return m_fScaledWidth;
	}

	template <typename T>
	// 본 객체의 가로 길이를 설정한다.
	// 왠만해선 사용하지 말자.
	void SetWidth(T width) {
		m_fWidth = static_cast<float>(width);
		m_fScaledWidth = m_fWidth * m_vScale.x;
	}

	// 본 객체의 세로 픽셀 길이를 반환한다.
	float Height() const {
		return m_fHeight;
	}

	// 본 객체의 스케일링된 세로 픽셀 길이를 반환한다.
	float ScaledHeight() const {
		return m_fScaledHeight;
	}

	template <typename T>
	// 본 객체의 세로 길이를 설정한다.
	// 왠만해선 사용하지 말자.
	void SetHeight(T height) {
		m_fHeight = static_cast<float>(height);
		m_fScaledHeight = m_fHeight * m_vScale.y;
	}

	// 본 객체의 상위 객체의 주소값을 반환한다.
	ZeroIScene* Parent() const {
		return m_pParent;
	}

	// 본 객체의 상위 객체를 설정한다.
	// 이 함수를 사용하는 것보단 PushScene(ZeroIScene* _scene)함수를 사용하는 것을 권장한다.
	void SetParent(ZeroIScene* parent) {
		m_pParent = parent;
	}

	// 본 객체의 윈도우 핸들을 반환한다.
	HWND Hwnd() const {
		return m_hWnd;
	}

	// 본 객체의 윈도우 핸들을 설정한다.
	void SetHwnd(HWND hwnd) {
		m_hWnd = hwnd;
	}

	// 본 객체의 행렬을 반환한다.
	// 사용하지 않는 것을 권장한다.
	D3DXMATRIX Mat() const {
		return m_Mat;
	}

	// 본 객체의 이름을 반환합니다.
	string Name() const {
		return m_sName;
	}

	// 본 객체의 이름을 설정합니다.
	void SetName(const string _name) {
		m_sName = _name;
	}

	// 본 객체가 생성되고 난 후 지난시간을 초단위로 반환한다.
	float StartToCurrentTime() const {
		return m_fStartToCurrentTime;
	}
};
