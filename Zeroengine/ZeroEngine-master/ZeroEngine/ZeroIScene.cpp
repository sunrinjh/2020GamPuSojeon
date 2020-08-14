#include "stdafx.h"
#include "ZeroIScene.h"
#include "ZeroApplication.h"
#include "ZeroCameraManager.h"
#include "ZeroEffectManager.h"
#include "ZeroMathManager.h"

#define GETA(c) (((c) &0xff000000) >> 24)
#define GETR(c) (((c) &0x00ff0000) >> 16)
#define GETG(c) (((c) &0x0000ff00) >> 8)
#define GETB(c) ((c) &0x000000ff)

ZeroIScene::ZeroIScene()
	: m_vPos(0.0f, 0.0f),
	m_vGlobalPos(0.0f, 0.0f),
	m_vScale(1.0f, 1.0f),
	m_vScalingCenter(0.0f, 0.0f),
	m_vRotCenter(0.0f, 0.0f),
	m_fRot(0.0f),
	m_Color(D3DCOLOR_ARGB(255, 255, 255, 255)),
	m_bCamera(true),
	m_ColorTemp(D3DCOLOR_ARGB(255, 255, 255, 255)),
	m_fStartToCurrentTime(0.0f),
	m_bUpdate(true)
	{
	SetRect(0, 0, 0, 0);
	SetErase(false);
	SetParent(NULL);
	D3DXMatrixIdentity(&m_Mat);
	SetWorldPos(0, 0);

	SetWidth(0);
	SetHeight(0);
	SetName("");

	SetHwnd(GetForegroundWindow());
}

ZeroIScene::~ZeroIScene() {
	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		SAFE_DELETE(*iter);
	}
	m_Node.clear();
}

void ZeroIScene::Update(float _eTime) {
	m_fStartToCurrentTime += _eTime;

	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		if ((*iter)->m_bUpdate == true) (*iter)->Update(_eTime);

		if ((*iter)->IsErase()) {
			SAFE_DELETE(*iter);
			iter = m_Node.erase(iter);
			if (iter == m_Node.end()) break;
		}
	}

	UpdateWorldPos();
}

void ZeroIScene::UpdateWorldPos() {
	if (ZeroCameraMgr->IsCamera()) {
		// 부모 객체를 모두 돌려 m_bCamera 가 false인 객체가 있는지 없는지 확인한다.
		bool isCamera = true;
		ZeroIScene* parent = m_pParent;
		while (parent) {
			if (!parent->m_bCamera) {
				isCamera = false;
				break;
			}
			parent = parent->m_pParent;
		}

		if (m_pParent == NULL) {
			// 만약 최상위 객체가 카메라 설정이 안되있으면 카메라 매니저의 카메라기능을 해제
			if (!m_bCamera) {
				ZeroCameraMgr->SetCameraOff();
			}
			SetWorldPos(Pos() - ZeroCameraMgr->Pos());
		}
		else {  // 최상위 객체가 아니라면?
			// 카메라 기능이 설정되어 있으면 그냥 Pos를 넣어준다.
			if (m_bCamera) {
				SetWorldPos(Pos());
			}
			else {
				// 객체의 카메라기능이 꺼져있고 부모객체가 모두 켜져있을때
				if (isCamera) {
					// 카메라매니저가 돌려놨던 Pos만큼 되돌려서 빌보드 출력을 한다.
					SetWorldPos(Pos() + ZeroCameraMgr->Pos());
				}
				else {
					// 부모객체중 하나라도 꺼져 있을 때 그냥 Pos를 넣어준다.
					SetWorldPos(Pos());
				}
			}
		}
	}
	else {
		// 카메라매니저의 카메라기능이 꺼져있으므로 정상 빌보드 출력.
		SetWorldPos(Pos());
	}
	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		if ((*iter)->m_bUpdate == true) (*iter)->UpdateWorldPos();
	}
}

void ZeroIScene::Render() {
	UpdateWorldPos();
	D3DXMatrixTransformation2D(&m_Mat, &m_vScalingCenter, 0.0f, &m_vScale, &m_vRotCenter,
		D3DXToRadian(m_fRot), &m_vWorldPos);

	if (m_pParent != NULL) m_Mat *= m_pParent->m_Mat;

	// 컬러 상속
	if (m_pParent != NULL) {
		m_Color = D3DCOLOR_ARGB((int) (GETA(m_ColorTemp) * GETA(m_pParent->m_Color) / 255.0f),
		                        (int) (GETR(m_ColorTemp) * GETR(m_pParent->m_Color) / 255.0f),
		                        (int) (GETG(m_ColorTemp) * GETG(m_pParent->m_Color) / 255.0f),
		                        (int) (GETB(m_ColorTemp) * GETB(m_pParent->m_Color) / 255.0f));
	}
	else {
		m_Color = m_ColorTemp;
	}
}

void ZeroIScene::PushScene(ZeroIScene* _scene, bool update /*=true*/) {
	if (_scene == this) {
		assert(!"자기 자신을 Push할 수 없습니다");
		return;
	}
	_scene->m_bUpdate = update;
	_scene->m_pParent = this;
	m_Node.push_back(_scene);
}

void ZeroIScene::PopScene(ZeroIScene* _scene, bool isErase) {
	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		if ((*iter) == _scene) {
			if (isErase) {
				SAFE_DELETE(*iter);
			}
			else {
				(*iter)->m_pParent = NULL;
			}
			m_Node.erase(iter);
			break;
		}
	}
}

bool ZeroIScene::IsExistScene(ZeroIScene* _scene) {
	for (NODE::iterator iter = m_Node.begin(); iter != m_Node.end(); ++iter) {
		if ((*iter) == _scene) {
			return true;
		}
	}
	return false;
}

bool ZeroIScene::IsOverlapped(ZeroIScene* _scene)
{
	// 각 객체의 World 좌표 기준 중심점을 계산해낸다.
	ZeroVec cpos1 = ZeroVec(m_fWidth * 0.5f, m_fHeight * 0.5f);
	ZeroVec cpos2 = ZeroVec(_scene->Width() * 0.5f, _scene->Height() * 0.5f);

	D3DXMATRIX mat1 = m_Mat;
	D3DXMATRIX mat2 = _scene->Mat();

	D3DXVec2TransformCoord(&cpos1, &cpos1, &mat1);
	D3DXVec2TransformCoord(&cpos2, &cpos2, &mat2);

	// 우선 원 충돌을 실시하여 거리가 충분히(?) 멀 경우 false를 반환한다.
	float len1 = ZeroVec(m_fScaledWidth, m_fScaledHeight).Length() * 0.5f;
	float len2 = ZeroVec(_scene->ScaledWidth(), _scene->ScaledHeight()).Length() * 0.5f;
	float len3 = cpos1.Distance(cpos2);

	if (len3 > len1 + len2)
		return false;

	// 그 후 OBB 충돌을 검사한다.
	return CheckOBBCollision(_scene);
}

bool ZeroIScene::CheckOBBCollision(ZeroIScene* _scene)
{
	ZeroVec a1, a2, b1, b2, l, t;
    double t1, t2, t3;

	// 각 객체의 World 좌표 기준 중심점을 계산해낸다.
	// IsOverlapped에서 이미 계산했는데 저 값을 가져와볼까...
	ZeroVec cpos1 = ZeroVec(m_fWidth * 0.5f, m_fHeight * 0.5f);
	ZeroVec cpos2 = ZeroVec(_scene->Width() * 0.5f, _scene->Height() * 0.5f);
	
	D3DXMATRIX mat1 = m_Mat;
	D3DXMATRIX mat2 = _scene->Mat();

	D3DXVec2TransformCoord(&cpos1, &cpos1, &mat1);
	D3DXVec2TransformCoord(&cpos2, &cpos2, &mat2);

	// 각 객체의 World 회전 각도를 구하고, sin과 cos값을 구한다.
	float angle1 = GlobalRot();
	float angle2 = _scene->GlobalRot();
	
	float sin1 = sinf(D3DXToRadian(angle1));
	float sin2 = sinf(D3DXToRadian(angle2));
	float cos1 = cosf(D3DXToRadian(angle1));
	float cos2 = cosf(D3DXToRadian(angle2));

	// OBB 충돌검사.
	a1 = ZeroVec(m_fScaledWidth * 0.5f * cos1, m_fScaledWidth * 0.5f * sin1);
    a2 = ZeroVec(m_fScaledHeight * 0.5f * -sin1, m_fScaledHeight * 0.5f * cos1);
	b1 = ZeroVec(_scene->ScaledWidth() * 0.5f * cos2, _scene->ScaledWidth() * 0.5f * sin2);
    b2 = ZeroVec(_scene->ScaledHeight() * 0.5f * -sin2, _scene->ScaledHeight() * 0.5f * cos2);
	t = cpos1 - cpos2;
	
    l = b1;
    l.Normalize();
    t1 = b1.Length();
    t2 = fabs(a1.Dot(l)) + fabs(a2.Dot(l));
    t3 = fabs(l.Dot(t));
    if (t3 >= t1 + t2)
		return false;

    l = b2;
    l.Normalize();
    t1 = b2.Length();
    t2 = fabs(a1.Dot(l)) + fabs(a2.Dot(l));
    t3 = fabs(l.Dot(t));
    if (t3 >= t1 + t2)
		return false;

    l = a1;
    l.Normalize();
    t1 = a1.Length();
    t2 = fabs(b1.Dot(l)) + fabs(b2.Dot(l));
    t3 = fabs(l.Dot(t));
    if (t3 >= t1 + t2)
		return false;

    l = a2;
    l.Normalize();
    t1 = a2.Length();
    t2 = fabs(b1.Dot(l)) + fabs(b2.Dot(l));
    t3 = fabs(l.Dot(t));
    if (t3 >= t1 + t2)
		return false;

    return true;
}

bool ZeroIScene::IsOverlapped(ZeroVec pos) {
	D3DXMATRIX mat1 = m_Mat;
	D3DXMATRIX mat1Inv;	D3DXMatrixInverse(&mat1Inv, NULL, &mat1);

	D3DXVec2TransformCoord(&pos, &pos, &mat1Inv);

	return (IsPosInRect(m_Rect, pos));
}

bool ZeroIScene::IsPosInRect(ZeroRect rect, ZeroVec pos) {
	return (pos.x > rect.left && pos.x < rect.right && pos.y > rect.top && pos.y < rect.bottom);
}

void ZeroIScene::SetColorA(int color) {
	ZeroMathMgr->Clamp(color, 0, 255);
	m_ColorTemp = D3DCOLOR_ARGB(color, GETR(m_ColorTemp), GETG(m_ColorTemp), GETB(m_ColorTemp));
}

void ZeroIScene::SetColorR(int color) {
	ZeroMathMgr->Clamp(color, 0, 255);
	m_ColorTemp = D3DCOLOR_ARGB(GETA(m_ColorTemp), color, GETG(m_ColorTemp), GETB(m_ColorTemp));
}

void ZeroIScene::SetColorG(int color) {
	ZeroMathMgr->Clamp(color, 0, 255);
	m_ColorTemp = D3DCOLOR_ARGB(GETA(m_ColorTemp), GETR(m_ColorTemp), color, GETB(m_ColorTemp));
}

void ZeroIScene::SetColorB(int color) {
	ZeroMathMgr->Clamp(color, 0, 255);
	m_ColorTemp = D3DCOLOR_ARGB(GETA(m_ColorTemp), GETR(m_ColorTemp), GETG(m_ColorTemp), color);
}

float ZeroIScene::GlobalRot() const
{
	float r = m_fRot;
	ZeroIScene* parent = m_pParent;
	while (parent)
	{
		r += parent->Rot();
		parent = parent->Parent();
	}
	return r;
}

void ZeroIScene::UpdateTransform()
{
	// WorldPos를 갱신한다.
	UpdateWorldPos();

	// Matrix를 갱신한다.
	D3DXMatrixTransformation2D(&m_Mat, &m_vScalingCenter, 0.0f, &m_vScale, &m_vRotCenter,
		D3DXToRadian(m_fRot), &m_vWorldPos);
	if (m_pParent != NULL) m_Mat *= m_pParent->m_Mat;

	// 절대 위치를 갱신한다.
	D3DXVec2TransformCoord(&m_vGlobalPos, &m_vPos, &m_Mat);
}

#undef GETA
#undef GETR
#undef GETG
#undef GETB
