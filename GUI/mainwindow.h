#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QDateEdit>

#include "../WordParser/MultiThreadWP.h"

namespace Ui {
class MainWindow;
}
class GUI : public QMainWindow
{
    Q_OBJECT

public:
    // получение шапки
    void getNameTechnicalSchool(QString &name);
    // получение председателя
    void getChairperson(QString &name);
    // получение даты рассмотрения
    void getReviewDate(QString &name);
    // получение даты утверждения
    void getApporvalDate(QString &name);
    // получение зам.директора
    void getDeputyDirector(QString &name);
    // получение дисциплины
    void getDiscipline(QString &name);
    // получение специальности
    void getSpecialty(QString &name);
    // получение препода
    void getLecturer(QString &name);
    // получение цикловой комиссий
    void getExamined(QString &buffer);
    // получение кем утвержденно
    void getAffirm(QString &buf);
    // получение ид протокола
    void getProtocolId(QString &buffer);
    // вывод секции в scroll area.
	void addSection(vector<WP::QuestionsList> qs);
    // получение значения для добавления вопроса в каждый билет (возвращает значение: одного spinbox_id)
    void getValueDynamicSpinBox(int &value, const int spin_box_id);
    // получение заголовка секции (возвращает значение: одного qtext_browser_id)
    void getTextDynamicTextBox(QString &str, const int qtext_browser_id);
    // получение всех значении, для добавления вопросов в каждый билет (возвращает по ссылке  unordered_map | int (spin_box_id) | int (value)
    //void getAllValueDynamicSpinBox(std::unordered_map <int, int> &map,
    //                                     const int count_section);
    //// получение всех заголовков секции (возвращает по ссылке  unordered_map | int (box_text_id) | string (text)
    //void getAllTextDynamicTextBox(std::unordered_map <int, QString> &map,
    //                                     const int count_section);
    // установка системенного времени в боксах для времени
    void setCurrentDateTimeBox(QDateEdit * widget);
    // получние количество билетов
    void getValueTicketSpinBox(int &value);
    // вызов диалога для сохранение .doc/.doc
    void showSaveDialog();
    explicit GUI(QWidget *parent = 0);
    ~GUI();
	
	vector<WP::QuestionsSection> GUI::getQuestionSections(int sectCount);

	//Говнокод данилки
	void destroyDynamicSpinBox();
	void destroyMainLabel();
	void destroyAnswerLabel();
	void destroyLabelSection();
	void destroyTextBox();
	void destroyAllScrollArea();
	void clearLayout();

private slots:

    void on_button_open_file_clicked();

    void on_button_ready_clicked();

    //void on_review_date_dateChanged(const QDate &date);

    //void on_date_apporval_dateChanged(const QDate &date);
	
	// Вывод exception
	void showDialogException(QString message);
	void setProgressBar(QString message);

    void on_action_4_triggered();

signals: void sendException(QString message);
signals: void sendMessage(QString message);

private:
    Ui::MainWindow *ui;

    //std::unordered_map <int, int> all_value_spin_box; // spin_id | value
    //std::unordered_map <int, QString> all_text_box; // spin_id | text

    QString path_to_word = ""; // путь до билетов
    QString review_date = ""; // дата рассмотрения
    QString date_apporval = ""; // дата утверждения
    QString name_teh_school = ""; // шапка (название организации)
    QString chairperson = ""; // председатель
    QString deputy_director = ""; // зам. директор
    QString discipline = ""; // дисциплина
    QString specialty = ""; // специальность
    QString lecturer = ""; // препод
    QString examined = ""; // цикловая коммисия
    QString protocol_id = ""; // протокол ид
    QString path_to_save = ""; // путь для сохранение
    QString affirm = ""; // кем утверждено

	bool status_show_scroll_area = false;

	int count_section = 0;
    int count_ticket = 0;
	
	//WP
	WP::MultiThreadWP* m_pMTWP;
	shared_ptr<vector<WP::QuestionsList>> m_pQS;
};

#endif // MAINWINDOW_H
