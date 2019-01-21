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
		// Инициализация COM либы в текущем потоке
		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);


		HRESULT hr = m_spWordApp.CreateInstance(__uuidof(Word::Application));
		if (FAILED(hr))
		{
			throw exception("Ошибка запуска MSWord");
		}
		// Делает MSWord невидимым
		m_spWordApp->Visible = VARIANT_FALSE;
	}

	WordParser::~WordParser()
	{
		closeFile();
		m_spWordApp->Quit();
		// Деинициализация COM либы в текущем потоке
		CoUninitialize();
	}

	vector<QuestionsList> WordParser::readFile(string path)
	{
		if (path.empty()) 
			throw exception("Файл не выбран");
		closeFile();
		m_questionsLists.clear();
		m_showMessage("Чтение файла: " + path);
		m_spDoc = m_spWordApp->Documents->Open(&_variant_t(path.c_str()));

		// Вычисление количества секций и вопросов в них
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
			throw exception("Файл не выбран");
		m_showMessage("Создание заголовка.");
		//Копирование списка вопросов
		m_spDoc->Content->Copy();
		m_spDoc->Content->Delete();

		//Таблица
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
		//Заголовок
		{
			m_spDoc->Paragraphs->Add();
			Word::ParagraphPtr paraHeader = m_spDoc->Paragraphs->Last;
			paraHeader->Range->Font->Reset();
			paraHeader->Range->Font->Size = 14;//g
			paraHeader->Range->Text = _bstr_t("\nЭКЗАМЕНАЦИОННЫЕ ВОПРОСЫ\n");
		}
		//По дисц и для спец
		{
			m_spDoc->Paragraphs->Add();
			Word::ParagraphPtr prDisc = m_spDoc->Paragraphs->Last;
			prDisc->Range->Text = _bstr_t(("по дисциплине «" + header.discipline + "»\n").c_str());

			m_spDoc->Paragraphs->Add();
			Word::ParagraphPtr prSpec = m_spDoc->Paragraphs->Last;
			prSpec->Range->Text = _bstr_t(("для специальности «" + header.specialty + "»\n").c_str());
		}
		//Содержат общие формулировки вопросов и тем
		{
			m_spDoc->Paragraphs->Add();
			Word::ParagraphPtr pr = m_spDoc->Paragraphs->Last;
			pr->Range->Text = _bstr_t("Содержат общие формулировки вопросов и тем\n");
		}

		//Вставка списка вопросов
		m_spDoc->Paragraphs->Add();
		m_spDoc->Paragraphs->Last->Range->Paste();
	}

	void WordParser::createTickets(TicketsOptions opt)
	{
		if (m_spDoc == nullptr)
			throw exception("Файл не выбран");
		int numOfSections = opt.questionsSections.size();	//Требуемое кол-во секций вопросов (в билетах)
		int numOfTickets = opt.ticketCount;					//Требуемое кол-во билетов
		if (numOfSections != m_questionsLists.size())
			throw exception("Внутренняя ошибка: кол-во списков не равно кол-ву секций");

		srand((unsigned int)time(0));
		//section/ticket/question
		//TODO: Переместить в кучу, т.к. может возникнуть переполнение стека.
		vector<vector<vector<int>>> allQuestions(numOfSections);

		for (int sect = 0; sect < numOfSections; sect++) {
			//Рассматриваем одну секцию
			int numOfQuestInList = m_questionsLists[sect].numOfQuestions;		//Кол-во вопросов в текущем списке
			int numOfQuestInSect = opt.questionsSections[sect].numOfQuestions;	//Требуемое кол-во вопросов в текущей секции
			if (numOfQuestInList < numOfQuestInSect)
				throw exception(((string)"Вопросов в списке №" + to_string(sect + 1) + (string)" нехватает для заполнения билетов").c_str());
			allQuestions[sect].resize(numOfTickets);
			unordered_set<int> currentQuestionsSet;						//Список с вопросами
			for (int i = 0; i < numOfQuestInList; i++)
				currentQuestionsSet.insert(i);

			int questionInList = 0;
			for (int question = 0; question < numOfQuestInSect; question++) {
				//Рассматриваем один из вопросов...
				for (int ticket = 0; ticket < numOfTickets; ticket++) {
					//...в одном из билетов
					if (questionInList < numOfQuestInList)						//Первичное заполенине оригинальными вопросами
						allQuestions[sect][ticket].push_back(questionInList++);
					else {														//Заполнение повторяющимеся вопросами
						unordered_set<int> allowQuestions(currentQuestionsSet);
						for (int q : allQuestions[sect][ticket])
							allowQuestions.erase(q);
						//Добавляет случайный вопрос, но такой, которого еще нет в данной секции
						auto it = allowQuestions.begin();
						int randQuestion = rand() % allowQuestions.size();
						for (int i = 0; i < randQuestion; i++) 
							++it;
						allQuestions[sect][ticket].push_back(*it);
					}
					if (question == numOfQuestInSect - 1) //Последняя итерация внешнего цикла
						random_shuffle(allQuestions[sect][ticket].begin(), allQuestions[sect][ticket].end()); //Рандомно перемешивает вопросы в билетах
				}
			}
			random_shuffle(allQuestions[sect].begin(), allQuestions[sect].end()); //Рандомно перемешивает билеты
		}

		m_spDoc->Tables->Item(1)->Range->Copy(); //Копирование таблицы из заголовка
		

		for (int i = 0; i < numOfTickets; i++) {
			m_showMessage("Создание билета " + to_string(i + 1) + "/" + to_string(numOfTickets));
			//Заголовок билета
			{
				m_spDoc->Paragraphs->Add();
				Word::ParagraphPtr prTable = m_spDoc->Paragraphs->Last;
				prTable->Range->Paste(); //Вставка таблицы из заголовка
				//prTable->KeepWithNext = -1; //true
			}
			//Номер билета
			{
				m_spDoc->Paragraphs->Add();
				Word::ParagraphPtr prTitle = m_spDoc->Paragraphs->Last;
				prTitle->Alignment = Word::WdParagraphAlignment::wdAlignParagraphCenter;//g
				prTitle->Range->Font->Reset();
				prTitle->Range->Text = _bstr_t(("ЭКЗАМЕНАЦИОННЫЙ БИЛЕТ №" + to_string(i + 1)).c_str());
				prTitle->Range->Font->Bold = 1;
				prTitle->Range->Font->Size = 18;//g
				prTitle->KeepWithNext = -1; //true
			}
			//Назв дисц и спец + вопросы
			{
				m_spDoc->Paragraphs->Add();
				Word::ParagraphPtr prQuestions = m_spDoc->Paragraphs->Last;
				prQuestions->Range->Font->Reset();
				prQuestions->Range->Font->Size = 14;//g
				prQuestions->Range->Paragraphs->Add()->Range->Text = _bstr_t(("\nпо дисциплине «" + opt.disciplineTitle + "»\n").c_str());
				prQuestions->Range->Paragraphs->Add()->Range->Text = _bstr_t(("\nдля специальности «" + opt.specialtyName + "»\n").c_str());
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
			//ФИО препода
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
				prTeacherL->Range->Text = "Преподаватель _________ ";
				prTeacherL->Range->Font->Size = 14;//g
				prTeacherL->KeepWithNext = -1; //true

				m_spDoc->Paragraphs->Add()->LineSpacing = 60;
				m_spDoc->Paragraphs->Add()->KeepWithNext = 0; //false
			}
		}
		m_showMessage("Создание билетов завершено.");
	}

	void WordParser::saveAs(string path)
	{
		if (path.empty())
			throw exception("Файл не выбран");
		m_showMessage("Сохранение файла: " + path);
		m_spDoc->SaveAs(&_variant_t(path.c_str()));
	}

	void WordParser::closeFile()
	{
		if (m_spDoc != nullptr) {
			m_showMessage("Закрытие файла: " + (string)m_spDoc->Name);
			m_spDoc->Close();
			m_spDoc = nullptr;
		}
	}

}