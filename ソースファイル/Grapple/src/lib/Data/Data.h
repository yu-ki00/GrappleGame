#pragma once
class Data
{
public:
	Data() {
		m_stage = 0;
	}
	~Data() {}
	static Data* GetInstance();
	static void DeleteInstance();
	int GetStage() { return m_stage; }
	void SetStage(int stage) { m_stage = stage; }

private:
	static Data* m_instance;

	int m_stage;
};
