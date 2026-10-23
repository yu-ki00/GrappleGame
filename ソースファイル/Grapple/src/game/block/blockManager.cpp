#include"blockManager.h"

void CBlockManager::Init() {
	m_stage = Data::GetInstance()->GetStage();

	LoadCSV("Data/StageData/Blockpos.csv", m_stage);

}

void CBlockManager::LoadCSV(const char* filenamme, int stage_num) {

	m_block.clear();
	m_ancBlock.clear();
	m_damaBlock.clear();

	ifstream file(filenamme);
	string line;

	getline(file, line);

	while (getline(file, line))
	{
		stringstream ss(line);

		string stage;
		string type;
		string x;
		string y;
		string z;

		getline(ss, stage, ',');
		getline(ss, type, ',');
		getline(ss, x, ',');
		getline(ss, y, ',');
		getline(ss, z, ',');

		BLOCK_DATA data;
		data.stage = atoi(stage.c_str());

		if (data.stage != stage_num)
			continue;

		VECTOR pos = VGet((float)atof(x.c_str()), (float)atof(y.c_str()), (float)atof(z.c_str()));

		if (type == "BLUE")
		{
			CBlock block;

			block.Init();
			block.SetPos(pos);
			block.SetActive(true);

			m_block.push_back(block);
		}
		else if (type == "WHITE")
		{
			CAnchorBlock block;

			block.Init();
			block.SetPos(pos);
			block.SetActive(true);

			m_ancBlock.push_back(block);
		}
		else if (type == "RED")
		{
			CDamageBlock block;

			block.Init();
			block.SetPos(pos);
			block.SetActive(true);

			m_damaBlock.push_back(block);
		}
	}

}
void CBlockManager::Load(int stagehndl) {

	int hndl = MV1LoadModel(BLUE_BLOCK_PATH);

	for (auto& block : m_block)
	{
		block.Load(hndl);
	}
	MV1DeleteModel(hndl);

	hndl = MV1LoadModel(RED_BLOCK_PATH);

	for (auto& block : m_damaBlock)
	{
		block.Load(hndl);
	}

	MV1DeleteModel(hndl);

	hndl = MV1LoadModel(WHITE_BLOCK_PATH);

	for (auto& block : m_ancBlock)
	{
		block.Load(hndl);
	}
	MV1DeleteModel(hndl);


}
void CBlockManager::Step() {
	for (auto& block : m_block){
		block.Step();
	}
	for (auto& block : m_damaBlock){
		block.Step();
	}
	for (auto& block : m_ancBlock){
		block.Step();
	}
}
void CBlockManager::Update() {
	for (auto& block : m_block) {
		block.Update();
	}
	for (auto& block : m_damaBlock) {
		block.Update();
	}
	for (auto& block : m_ancBlock) {
		block.Update();
	}
}
void CBlockManager::Draw() {
	for (auto& block : m_block) {
		block.Draw();
	}
	for (auto& block : m_damaBlock) {
		block.Draw();
	}
	for (auto& block : m_ancBlock) {
		block.Draw();
	}
}
void CBlockManager::Exit() {
	for (auto& block : m_block) {
		block.Exit();
	}
	for (auto& block : m_damaBlock) {
		block.Exit();
	}
	for (auto& block : m_ancBlock) {
		block.Exit();
	}
}

