#pragma once
class CHW_CollisionMgr
{
private:
	CHW_CollisionMgr();
	CHW_CollisionMgr(const CHW_CollisionMgr& rhs) = delete;
	CHW_CollisionMgr& operator=(CHW_CollisionMgr& rCollision) = delete;
	~CHW_CollisionMgr();




public:
	static CHW_CollisionMgr* Get_Instance()
	{
		if (!m_pInstance)
		{
			m_pInstance = new CHW_CollisionMgr;
		}

		return m_pInstance;
	}
	static void		Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:

	static CHW_CollisionMgr* m_pInstance;
};

