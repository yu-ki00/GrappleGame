#include"Data.h"
Data* Data::m_instance = nullptr;
Data* Data::GetInstance() {
	if (m_instance == nullptr)m_instance = new Data;
	return m_instance;
}
void Data::DeleteInstance() {
	if (m_instance != nullptr) {
		delete m_instance;
		m_instance = nullptr;
	}
}