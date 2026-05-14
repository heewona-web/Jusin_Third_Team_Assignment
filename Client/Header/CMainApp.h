#pragma once
class CMainApp{
public:
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT Ready_MainApp();
	int		Update_MainApp(const float& fTimeDelta);
	void	LateUpdate_MainApp(const float& fTimeDelta);
	void	Render_MainApp();

public:
	static CMainApp* Create(); //생성함수
	virtual void Free(); //소멸함수

};

