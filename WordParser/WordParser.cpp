#pragma region Includes
#include "WordParser.h"
#include <ctime>
#include <exception>
#include <unordered_set>
#include <algorithm>

#pragma endregion

namespace WP {

	WordParser::WordParser(function<void(string)> showMessage)
		: m_showMessage(showMessage)
	{
		// ������������� COM ���� � ������� ������
		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);


		HRESULT hr = m_spWordApp.CreateInstance(__uuidof(Word::Application));
		if (FAILED(hr))
		{
			throw exception("������ ������� MSWord");
		}
		// ������ MSWord ���������
		m_spWordApp->Visible = VARIANT_FALSE;
	}

	WordParser::~WordParser()
	{
		closeFile();
		m_spWordApp->Quit();
		// ��������������� COM ���� � ������� ������
		CoUninitialize();
	}

	vector<QuestionsList> WordParser::readFile(string path)
	{
		if (path.empty()) 
			throw exception("���� �� ������");
		closeFile();
		m_questionsLists.clear();
		m_showMessage("������ �����: " + path);
		m_spDoc = m_spWordApp->Documents->Open(&_variant_t(path.c_str()));

		// ���������� ���������� ������ � �������� � ���
		int listCount = m_spDoc->Lists->GetCount();
		for (int i = 0; i < listCount; i++) {
			Word::ListPtr spList = m_spDoc->Lists->Item(i + 1);

			QuestionsList qs;
			qs.numOfQuestions = spList->CountNumberedItems();

			m_questionsLists.push_back(qs);
		}
		return m_questionsLists;
	}

	void WordParser::createHeader(Header header)
	{
		if (m_spDoc == nullptr)
			throw exception("���� �� ������");
		m_showMessage("�������� ���������.");
		//����������� ������ ��������
		m_spDoc->Content->Copy();
		m_spDoc->Content->Delete();

		//�������
		{
			m_spDoc->Paragraphs->Add();
			Word::ParagraphPtr pr = m_spDoc->Paragraphs->Last;
			pr->Range->Font->Reset();
			pr->Range->Font->Size = 14;//g
			pr->Alignment = Word::WdParagraphAlignment::wdAlignParagraphCenter;//g

			Word::TablePtr table = m_spDoc->Tables->Add(pr->Range, 2, 2);
			table->Cell(1, 1)->Merge(table->Cell(1, 2));
			table->Cell(1, 1)->Range->Font->Bold = 1;
			table->Cell(1, 1)->Range->Text = _bstr_t((header.name_teh_school+'\n').c_str());

			table->Cell(2, 1)->Range->Text = _bstr_t((header.examined + '\n' + header.review_date + '\n' + header.protocol + '\n' + header.chairperson).c_str());
			table->Cell(2, 1)->Range->ParagraphFormat->LineSpacing = 16;

			table->Cell(2, 2)->Range->Text = _bstr_t((header.affirm + '\n' + header.date_apporval + '\n' + header.deputy_director).c_str());
			table->Cell(2, 2)->Range->ParagraphFormat->LineSpacing = 16;
			table->Range->Paragraphs->KeepWithNext = -1; //true
		}
		//���������
		{
			m_spDoc->Paragraphs->Add();
			Word::ParagraphPtr paraHeader = m_spDoc->Paragraphs->Last;
			paraHeader->Range->Font->Reset();
			paraHeader->Range->Font->Size = 14;//g
			paraHeader->Range->Text = _bstr_t("\n��������������� �������\n");
		}
		//�� ���� � ��� ����
		{
			m_spDoc->Paragraphs->Add();
			Word::ParagraphPtr prDisc = m_spDoc->Paragraphs->Last;
			prDisc->Range->Text = _bstr_t(("�� ���������� �" + header.discipline + "�\n").c_str());

			m_spDoc->Paragraphs->Add();
			Word::ParagraphPtr prSpec = m_spDoc->Paragraphs->Last;
			prSpec->Range->Text = _bstr_t(("��� ������������� �" + header.specialty + "�\n").c_str());
		}
		//�������� ����� ������������ �������� � ���
		{
			m_spDoc->Paragraphs->Add();
			Word::ParagraphPtr pr = m_spDoc->Paragraphs->Last;
			pr->Range->Text = _bstr_t("�������� ����� ������������ �������� � ���\n");
		}

		//������� ������ ��������
		m_spDoc->Paragraphs->Add();
		m_spDoc->Paragraphs->Last->Range->Paste();
	}

	void WordParser::createTickets(TicketsOptions opt)
	{
		if (m_spDoc == nullptr)
			throw exception("���� �� ������");
		int numOfSections = opt.questionsSections.size();	//��������� ���-�� ������ �������� (� �������)
		int numOfTickets = opt.ticketCount;					//��������� ���-�� �������
		if (numOfSections != m_questionsLists.size())
			throw exception("���������� ������: ���-�� ������� �� ����� ���-�� ������");

		srand((unsigned int)time(0));
		//section/ticket/question
		//TODO: ����������� � ����, �.�. ����� ���������� ������������ �����.
		vector<vector<vector<int>>> allQuestions(numOfSections);

		for (int sect = 0; sect < numOfSections; sect++) {
			//������������� ���� ������
			int numOfQuestInList = m_questionsLists[sect].numOfQuestions;		//���-�� �������� � ������� ������
			int numOfQuestInSect = opt.questionsSections[sect].numOfQuestions;	//��������� ���-�� �������� � ������� ������
			if (numOfQuestInList < numOfQuestInSect)
				throw exception(((string)"�������� � ������ �" + to_string(sect + 1) + (string)" ��������� ��� ���������� �������").c_str());
			allQuestions[sect].resize(numOfTickets);
			unordered_set<int> currentQuestionsSet;						//������ � ���������
			for (int i = 0; i < numOfQuestInList; i++)
				currentQuestionsSet.insert(i);

			int questionInList = 0;
			for (int question = 0; question < numOfQuestInSect; question++) {
				//������������� ���� �� ��������...
				for (int ticket = 0; ticket < numOfTickets; ticket++) {
					//...� ����� �� �������
					if (questionInList < numOfQuestInList)						//��������� ���������� ������������� ���������
						allQuestions[sect][ticket].push_back(questionInList++);
					else {														//���������� �������������� ���������
						unordered_set<int> allowQuestions(currentQuestionsSet);
						for (int q : allQuestions[sect][ticket])
							allowQuestions.erase(q);
						//��������� ��������� ������, �� �����, �������� ��� ��� � ������ ������
						auto it = allowQuestions.begin();
						int randQuestion = rand() % allowQuestions.size();
						for (int i = 0; i < randQuestion; i++) 
							++it;
						allQuestions[sect][ticket].push_back(*it);
					}
					if (question == numOfQuestInSect - 1) //��������� �������� �������� �����
						random_shuffle(allQuestions[sect][ticket].begin(), allQuestions[sect][ticket].end()); //�������� ������������ ������� � �������
				}
			}
			random_shuffle(allQuestions[sect].begin(), allQuestions[sect].end()); //�������� ������������ ������
		}

		m_spDoc->Tables->Item(1)->Range->Copy(); //����������� ������� �� ���������
		

		for (int i = 0; i < numOfTickets; i++) {
			m_showMessage("�������� ������ " + to_string(i + 1) + "/" + to_string(numOfTickets));
			//��������� ������
			{
				m_spDoc->Paragraphs->Add();
				Word::ParagraphPtr prTable = m_spDoc->Paragraphs->Last;
				prTable->Range->Paste(); //������� ������� �� ���������
				//prTable->KeepWithNext = -1; //true
			}
			//����� ������
			{
				m_spDoc->Paragraphs->Add();
				Word::ParagraphPtr prTitle = m_spDoc->Paragraphs->Last;
				prTitle->Alignment = Word::WdParagraphAlignment::wdAlignParagraphCenter;//g
				prTitle->Range->Font->Reset();
				prTitle->Range->Text = _bstr_t(("��������������� ����� �" + to_string(i + 1)).c_str());
				prTitle->Range->Font->Bold = 1;
				prTitle->Range->Font->Size = 18;//g
				prTitle->KeepWithNext = -1; //true
			}
			//���� ���� � ���� + �������
			{
				m_spDoc->Paragraphs->Add();
				Word::ParagraphPtr prQuestions = m_spDoc->Paragraphs->Last;
				prQuestions->Range->Font->Reset();
				prQuestions->Range->Font->Size = 14;//g
				prQuestions->Range->Paragraphs->Add()->Range->Text = _bstr_t(("\n�� ���������� �" + opt.disciplineTitle + "�\n").c_str());
				prQuestions->Range->Paragraphs->Add()->Range->Text = _bstr_t(("\n��� ������������� �" + opt.specialtyName + "�\n").c_str());
				prQuestions->Range->Font->Size = 12;//g
				prQuestions->Alignment = Word::WdParagraphAlignment::wdAlignParagraphLeft;//g

				for (int sect = 0; sect < numOfSections; sect++) {
					if (!opt.questionsSections[sect].name.empty())
						prQuestions->Range->Paragraphs->Add()->Range->Text = _bstr_t(("\n" + opt.questionsSections[sect].name + ":\n").c_str());
					else
						prQuestions->Range->Paragraphs->Add();
					//prQuestions->Range->ListFormat->ApplyNumberDefault();
					for (int question = 0; question < opt.questionsSections[sect].numOfQuestions; question++) {
						int qestInsertId = allQuestions[sect][i][question];
						prQuestions->Range->Paragraphs->Add()->Range->Text = (to_string(question + 1) + ".  ").c_str() + m_spDoc->Lists->Item(sect + 1)->ListParagraphs->Item(qestInsertId + 1)->Range->Text;
					}
					//prQuestions->Range->ListFormat->RemoveNumbers();
				}

				prQuestions->KeepWithNext = -1; //true
			}
			//��� �������
			{
				m_spDoc->Paragraphs->Last->Alignment = Word::WdParagraphAlignment::wdAlignParagraphRight;//g

				Word::ParagraphPtr prTeacher = m_spDoc->Paragraphs->Add();;
				prTeacher->Range->Font->Reset();

				Word::ParagraphPtr prTeacherR = prTeacher->Range->Paragraphs->Add();
				prTeacherR->Range->Font->Reset();
				prTeacherR->Range->Font->Bold = 0;
				prTeacherR->Range->Text = _bstr_t(opt.teacherName.c_str());
				prTeacherR->Range->Font->Size = 14;//g

				Word::ParagraphPtr prTeacherL = prTeacher->Range->Paragraphs->Add();
				prTeacherL->Range->Font->Reset();
				prTeacherL->Range->Font->Bold = 1;
				prTeacherL->Range->Text = "������������� _________ ";
				prTeacherL->Range->Font->Size = 14;//g
				prTeacherL->KeepWithNext = -1; //true

				m_spDoc->Paragraphs->Add()->LineSpacing = 60;
				m_spDoc->Paragraphs->Add()->KeepWithNext = 0; //false
			}
		}
		m_showMessage("�������� ������� ���������.");
	}

	void WordParser::saveAs(string path)
	{
		if (path.empty())
			throw exception("���� �� ������");
		m_showMessage("���������� �����: " + path);
		m_spDoc->SaveAs(&_variant_t(path.c_str()));
	}

	void WordParser::closeFile()
	{
		if (m_spDoc != nullptr) {
			m_showMessage("�������� �����: " + (string)m_spDoc->Name);
			m_spDoc->Close();
			m_spDoc = nullptr;
		}
	}

}