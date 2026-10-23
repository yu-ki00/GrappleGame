#pragma once

static const char RESULT_PATH[] = { "" };
class CResultScene {
private:
	enum tagResultScene {
		INIT,
		LOAD,
		MAIN,
		END
	};
	tagResultScene m_state;

	int m_hndl;

	int m_time;

public:
	CResultScene();

	~CResultScene();

	int Loop();

	void Draw(int clearTime);

	int GetTime() { return m_time; }

private:
	void Init();

	void Load();

	void Step();

	void Exit();
};