#include "speechmanage.h"
SpeechManager::SpeechManager() {
	this->initspeech();
	this->createSpeaker();
	
	
}
SpeechManager::~SpeechManager() {

}
void  SpeechManager::show_Menu(){
	cout << "************��ӭ�μ��ݽ�����**************" << endl;
	cout << "************1.��ʼ�ݽ�����****************" << endl;
	cout << "************2.�鿴�����¼****************" << endl;
	cout << "************3.��ձ�����¼****************" << endl;
	cout << "************0.�˳���������****************" << endl;
	cout << "******************************************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	exit(0);
}
void  SpeechManager::initspeech() {
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_Speaker.clear();
	this->m_Index = 1;
}
void SpeechManager::createSpeaker() {
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i <nameseed.size(); i++) {
		string name = "ѡ��";
		name += nameseed[i];

		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] =0;
		}
		this->v1.push_back(i + 10001);
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::startSpeech() {
	for (this->m_Index = 1; this->m_Index < 3; this->m_Index++) {
		this->speechDraw();
		this->speechContest();
		this->showScore();
	}
	this->saveRecord();
	cout << "~~~~~~~~~~~~~~~����������˽���~~~~~~~~~~~~~~" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::speechDraw() {
	cout << "��" << this->m_Index << "�ֱ������ڽ���" << endl;
	cout << "��ǩ����ݽ�˳������:" << endl;
	if (this->m_Index == 1) {
		random_shuffle(v1.begin(), v1.end());
		for_each(v1.begin(), v1.end(), print);
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for_each(v2.begin(), v2.end(),print);
	}
	cout << endl;
	system("pause");
}
void print(int val){
	cout << val << " ";
}
void SpeechManager::speechContest() {
    cout << "��" << this->m_Index << "�ֱ������ڽ���" << endl;
	multimap<double, int, greater<double> > groupScore;
	int num = 0;
	vector<int>src;
	if (this->m_Index == 1) {
		src = v1;
	}
	else
	{
		src = v2;
	}
	for (vector<int>::iterator it = src.begin(); it != src.end(); it++) {
		num++;
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end(),greater<double>());
		d.pop_front();
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.f);
		double avg = sum / (double) d.size();
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		groupScore.insert(make_pair(avg, *it));
		/*cout << "ѡ�ֱ��Ϊ:  " << *it << "  ����:  " << this->m_Speaker[*it].m_Name << "  �÷�:  " << setprecision(4)<<avg;
		cout << endl;*/
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С���������:" << endl;
			for (multimap<double, int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				cout << "ѡ�ֱ��Ϊ:  " << it->second << "  ����:  " << this->m_Speaker[it->second].m_Name << "  �÷�:  " << setprecision(4) << this->m_Speaker[it->second].m_Score[this->m_Index - 1];
				cout << endl;
			}
			int count = 0;
			for (multimap<double, int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end()&&count<3; it++,count++) {
				if (this->m_Index == 1) {
					this->v2.push_back(it->second);
				}
				if (this->m_Index == 2) {
					this->victory.push_back(it->second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "~~~~~~~~~~~~~~��" << this->m_Index << "�ֱ�������~~~~~~~~~~~~~~~" << endl;
	system("pause");
	cout << endl;
}
void SpeechManager::showScore() {
	cout << "~~~~~~~~~~~~��" << this->m_Index << "�ֽ���ѡ����Ϣ:~~~~~~~~~~~" << endl;
	vector<int>src;
	if (this->m_Index == 1) {
		src = v2;
	}
	else
	{
		src = victory;
	}
	for (vector<int>::iterator it = src.begin(); it != src.end(); it++) {
		cout << "ѡ�ֱ��Ϊ:  " << *it << "  ����:  " << this->m_Speaker[*it].m_Name << "  �÷�:  " << setprecision(4) << this->m_Speaker[*it].m_Score[this->m_Index-1];
		cout << endl;
	}
	system("pause");
	system("cls");
	this->show_Menu();
}
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = this->victory.begin(); it != victory.end(); it++) {
		ofs<<*it<<","<< this->m_Speaker[*it].m_Score[1]<<",";
	}
	ofs << endl;
	ofs.close();
	cout << "~~~~~~~~~~~~~~~~��¼�Ѿ�����~~~~~~~~~~~~~~~~~" << endl;
}
void SpeechManager::loadRecord() {
	ifstream ifs("speech.csv",ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		this->fileIsEmpty = true;
		cout << "�ļ�Ϊ��" << endl;
		ifs.close();
		return;
	}
	this->fileIsEmpty = false;
	ifs.putback(ch);
	string data;
	int index = 1;
	while (ifs >> data) {
		//cout << data << endl;
		vector<string>v;
		int pos = -1;
		int start = 0;
		while (true) {
			pos = data.find(',', start);
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);
			start = pos + 1;
			v.push_back(temp);
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++) {
		cout << "��" << it->first << "��ھ���ţ�" << it->second[0] << "�÷֣�" << it->second[1] << endl;
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearRecord() {
	cout << "�Ƿ�ȷ������ļ�" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;
	int select;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);
		ofs.close();
		this->initspeech();
		this->createSpeaker();
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}